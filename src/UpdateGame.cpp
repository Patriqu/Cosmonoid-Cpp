#include "UpdateGame.h"
#include "SDL_rect.h"

bool UpdateGame::slow_down = false;
bool UpdateGame::set_paddle_default_look = false;
MMRESULT UpdateGame::timer_id;

UpdateGame::UpdateGame(GameState* game_state, const Uint8* key_state, const int level)
    : done(false),
      game_state(game_state),
      screen(),

      MAX_LEVEL(4),
      keystate(key_state),
      level(level),
      current_state(""),
      is_ball_motion(false),

      MOTION_RATE_BALL_Y(4),
      MOTION_RATE_BALL_X(9),

      MOTION_RATE_BALL_X_SLOW(3),
      MOTION_RATE_BALL_Y_SLOW(2),

      MOTION_RATE_PADDLE(6),

      main_menu(new MainMenu()),
      paddle(new Paddle()),
      ball(new Ball()),
      bricks_level(nullptr),
      collisions(new Collisions()),
      game_points(new GamePoints()),
      bonus(new Bonus()),

      detected_collision_brick(""),
      detected_collision_paddle(""),
      detected_collision_bonus(""),
      detected_collision_shoot(""),

      is_gun(false),

      MAX_BALLS(4),

      start_menu_music(true),

      allow_to_shot_start_clock(time_point_cast<std::chrono::seconds>(std::chrono::steady_clock::now()))
{
    y_motion_rates.push_back(MOTION_RATE_BALL_Y);
    x_motion_rates.push_back(0);

    // Sound
    sound_system = std::make_unique<SoundSystem>();
    sound_system->setVolumeMusic(main_menu->getVolume("music"));
    sound_system->setVolumeSound(main_menu->getVolume("sound"));

    // Load data of images in menu
    screen = SDL_GetWindowSurface(SDL_GetWindowFromID(1));

    const auto str = std::to_string(screen->h);
    ResManager::getInstance().loadImageMenu(str);
    ResManager::getInstance().loadImageSelection();

    // Load images of game objects:
    ResManager::getInstance().loadImageBall();
    ResManager::getInstance().loadImagePaddle();
    ResManager::getInstance().loadImagePaddleWar();
    ResManager::getInstance().loadImageBullet();
    ResManager::getInstance().loadImageBlocks();

    ResManager::getInstance().loadImageLivePack();
    ResManager::getInstance().loadImageSlowPack();
    ResManager::getInstance().loadImageDupPack();
    ResManager::getInstance().loadImageGunPack();
}

UpdateGame::~UpdateGame()
{
    delete paddle;
    delete ball;
    delete bricks_level;

    delete keystate;
    delete game_state;
}

void UpdateGame::mainMenuHandle()
{
    if (SDL_GetRelativeMouseMode() == SDL_TRUE)
        SDL_SetRelativeMouseMode(SDL_FALSE);

    // Handle keyboard in menu
    menuKeyHandle();
    menuMouseHandle();

    // CHECK IF IS CHANGED OPTIONS TO EXECUTE AND DO IT
    if (main_menu->isOptionToChange())
    {
        const auto option = main_menu->getChangedText();

        if (option == "volume_sound")
        {
            sound_system->setVolumeSound(main_menu->getVolume("sound"));
        }
        else if (option == "volume_music")
        {
            sound_system->setVolumeMusic(main_menu->getVolume("music"));
        }
        else if (option == "background")
        {
            const auto background = main_menu->getBackground();
        }
    }

    if (start_menu_music)
    {
        sound_system->playMusic("menu_music");

        start_menu_music = false;
    }
}

void UpdateGame::onStartGame()
{
    SDL_SetRelativeMouseMode(SDL_TRUE);

    if (is_ball_motion) is_ball_motion = false;

    // Set coordinates to place objects on the screen after start a level
    paddle->positionPaddleAtStart();
    ball->createBall();

    // Finally load bricks from current level at start
    if (level != 1) level = 1;

    loadLevelAtStart();

    // Initiate generator of random numbers for random a bonus
    bonus->initiateGenerator();
}

void UpdateGame::wallCollisionHandle()
{
    /* *** BALL WALL COLLISIONS HANDLE *** */

    std::vector<int> ball_x;
    std::vector<int> ball_y;
    std::vector<int> ball_w;
    std::vector<int> ball_h;

    for (auto i = 0; i < ball->getBallNumbers(); i++)
    {
        ball_x.push_back(ball->getBallPosition(i, "x"));
        ball_y.push_back(ball->getBallPosition(i, "y"));
        ball_w.push_back(ball->getBallPosition(i, "w"));
        ball_h.push_back(ball->getBallPosition(i, "h"));

        // TOP WALL:
        if (ball_y[i] < 0)
        {
            ball->setBallPosition(i, "y", 0);
            y_motion_rates[i] *= -1;
        }
            // LEFT WALL:
        else if (ball_x[i] < 0)
        {
            ball->setBallPosition(i, "x", 0);
            x_motion_rates[i] *= -1;
        }
            // RIGHT WALL:
        else if (ball_x[i] + ball_w[i] > screen->w)
        {
            ball->setBallPosition(i, "x", screen->w - ball_w[i]);
            x_motion_rates[i] *= -1;
        }
            // BOTTOM AND LOSE HANDLE:
        else if (ball_y[i] + ball_h[i] > screen->h)
        {
            if (ball->getBallNumbers() > 1)
            {
                x_motion_rates.erase(x_motion_rates.begin() + i);
                y_motion_rates.erase(y_motion_rates.begin() + i);

                ball->deleteBall(i);
            }
            else if (ball->getBallNumbers() == 1)
            {
                game_points->updateLives(-1);

                // Back to starting positions
                paddle->positionPaddleAtStart();
                ball->positionBallAtStart(i);

                // Set default values of ball motion
                for (auto j = 0; j < ball->getBallNumbers(); j++)
                {
                    y_motion_rates[j] = MOTION_RATE_BALL_Y;
                    x_motion_rates[j] = 0;
                }

                is_ball_motion = false;

                const auto actual_lives = game_points->getLives();
                if (actual_lives == 0)
                {
                    game_points->endGame("lose");
                    game_state->changeGameState("LOSE_GAME");
                }
            }
        }
    }

    /* *** LASER OFF SCREEN *** */
    paddle->destroyOffscreenBullets();

    ball_x.clear();
    ball_y.clear();
    ball_w.clear();
    ball_h.clear();

    ball_x.shrink_to_fit();
    ball_y.shrink_to_fit();
    ball_w.shrink_to_fit();
    ball_h.shrink_to_fit();
}

void UpdateGame::objectsCollisionHandle()
{
    SDL_Rect& paddle_rect = paddle->getPaddle();
    std::map<const int, SDL_Rect*> bricks = bricks_level->getAllBricks();

    checkLasersCollisions(bricks);
    checkBallsCollisions(paddle_rect, bricks);

    if (detected_collision_shoot == "Vertical")
    {
        removeBrick();
        paddle->destroyBulletsFromDestroyList();
    }
}

void UpdateGame::checkLasersCollisions(std::map<const int, SDL_Rect *> &bricks) {
    auto& dst_bullets = this->paddle->getBullets();
    for (auto bullet : dst_bullets) {
        this->detected_collision_shoot = this->collisions->detectCollision(*bullet, bricks);
        if (this->detected_collision_shoot != "None") {
            this->paddle->addLaserToDestroyLater(*bullet);
        }
    }
}

void UpdateGame::checkBallsCollisions(SDL_Rect &paddle_rect, std::map<const int, SDL_Rect *> &bricks) {
    for (int i = 0; i < this->ball->getBallNumbers(); i++)
    {
        SDL_Rect& temp_dst_ball = this->ball->getBall(i);

        this->detected_collision_brick = this->collisions->detectCollision(temp_dst_ball, bricks);
        this->detected_collision_paddle = this->collisions->detectCollision(temp_dst_ball, paddle_rect);

        // Change direction of ball if collision was detected:
        if (this->detected_collision_brick == "Vertical" || this->detected_collision_paddle == "Vertical")
        {
            this->ballVerticalCollision(i);
        }
        else if (this->detected_collision_brick == "Horizontal" || this->detected_collision_paddle == "Horizontal")
        {
            this->ballHorizontalCollision(i);
        }

        if (this->detected_collision_brick != "None")
        {
            this->removeBrick();
        }

        this->bonusHandle();
    }
}

void UpdateGame::ballHorizontalCollision(int ballNr) {
    // Change move x-axis
    if (this->x_motion_rates[ballNr] != -this->MOTION_RATE_BALL_X)
        this->x_motion_rates[ballNr] = this->MOTION_RATE_BALL_X;

    this->x_motion_rates[ballNr] *= -1;

    // Change move y-axis
    if (this->y_motion_rates[ballNr] == this->MOTION_RATE_BALL_Y || this->y_motion_rates[ballNr] == -this->MOTION_RATE_BALL_Y)
        this->y_motion_rates[ballNr] /= -this->MOTION_RATE_BALL_Y;
    else
        this->y_motion_rates[ballNr] /= -this->MOTION_RATE_BALL_Y_SLOW;

    this->y_motion_rates[ballNr] *= this->MOTION_RATE_BALL_Y_SLOW;

    this->ball->setBallMotion(ballNr, "y", this->y_motion_rates[ballNr]);

    // play bounce sound
    this->sound_system->playSoundSample("ball_collision");

    // If ball is hanging at paddle, fix this:
    const bool is_bottleneck = this->collisions->isBottleneck();
    if (is_bottleneck)
    {
        const int paddle_position = this->paddle->getPaddlePosition("x");
        const int paddle_width = this->paddle->getPaddlePosition("w");
        const int paddle_length = paddle_position + paddle_width;

        const int ball_position = this->ball->getBallPosition(ballNr, "x");
        const int ball_width = this->ball->getBallPosition(ballNr, "w");
        const int ball_length = ball_position + ball_width;

        const int dist_x = std::abs(paddle_position - ball_position);
        const int dist_w = std::abs(paddle_length - ball_position);

        if (ball_length < this->screen->w - ball_width && dist_x < dist_w)
            this->ball->correctBottleneck(ballNr, -dist_x);
        else
            this->ball->correctBottleneck(ballNr, dist_w);
    }
}

void UpdateGame::ballVerticalCollision(int ballNr) {
    this->y_motion_rates[ballNr] *= -1;

    if (this->detected_collision_paddle == "Vertical" && (this->x_motion_rates[ballNr] == this->MOTION_RATE_BALL_X || this->x_motion_rates[ballNr]
                                                                                                                      == -this->MOTION_RATE_BALL_X))
    {
        this->y_motion_rates[ballNr] = this->MOTION_RATE_BALL_Y;

        if (this->ball->getBallPosition(ballNr, "x") > 0)
            this->x_motion_rates[ballNr] = this->MOTION_RATE_BALL_X_SLOW;
        else
            this->x_motion_rates[ballNr] = -this->MOTION_RATE_BALL_X_SLOW;

        this->ball->setBallMotion(ballNr, "x", this->x_motion_rates[ballNr]);
    }

    this->sound_system->playSoundSample("ball_collision");
}

void UpdateGame::onResumeGame()
{
    // IF ALL BRICKS ARE DELETED FROM SCREEN - PLAYER WIN:
    if (bricks_level != nullptr && bricks_level->getTableOfIgnoredBricks().size() == bricks_level->getAllBricks().size()
    )
    {
        // We don't want to move a ball when starting new or the same level
        for (auto i = 0; i < ball->getBallNumbers(); i++)
        {
            y_motion_rates[i] = MOTION_RATE_BALL_Y;
            x_motion_rates[i] = 0;
        }
        is_ball_motion = false;

        if (level < MAX_LEVEL)
        {
            game_points->endGame("next_level");
            if (keystate[SDL_SCANCODE_RETURN])
                game_state->changeGameState("NEXT_LEVEL");
        }
        else
        {
            game_points->endGame("win");
            game_state->changeGameState("WIN_GAME");
        }
    }

    /* *** BASIC BALL MOTION HANDLE *** */
    if (is_ball_motion)
    {
        for (auto i = 0; i < ball->getBallNumbers(); i++)
        {
            ball->setBallMotion(i, "y", y_motion_rates[i]);
            ball->setBallMotion(i, "x", x_motion_rates[i]);
        }
    }

    wallCollisionHandle();
    objectsCollisionHandle();

    collisions->clearData();
    detected_collision_brick = "None";
    detected_collision_paddle = "None";
    detected_collision_shoot = "None";
}

void UpdateGame::onNextLevel()
{
    clearData();

    // Set starting positions of ball and paddle
    paddle->positionPaddleAtStart();

    ball->resetBalls();
    bonus->clearBonus();
    y_motion_rates.clear();
    x_motion_rates.clear();
    y_motion_rates.push_back(MOTION_RATE_BALL_Y);
    x_motion_rates.push_back(0);
    ball->createBall();

    bricks_level->clearData();
    free(bricks_level);

    // Load next level
    if (level < MAX_LEVEL)
        level += 1;
    else
        level = 1;

    loadLevelAtStart();

    // Set game state to "Next Level"
    game_points->updateLevel(1);

    game_points->endGame("new_start");
    game_state->changeGameState("RESUME_GAME");
}

void UpdateGame::onLoseGame()
{
    clearData();

    // We don't want to move a ball when starting new or the same level
    y_motion_rates[0] = MOTION_RATE_BALL_Y;
    x_motion_rates[0] = 0;
    is_ball_motion = false;

    if (keystate[SDL_SCANCODE_RETURN])
    {
        ball->resetBalls();
        ball->createBall();

        bonus->clearBonus();

        // Back to level 1 - restart game after lose
        if (level != 1)
        {
            bricks_level->clearData();
            bricks_level->replaceAllBricks();

            level = 1;
            loadLevelAtStart();
        }
        else {
            // Reset data and clear all tables left from previous level
            bricks_level->clearData();
            bricks_level->replaceAllBricks();
        }

        game_points->resetLevel();

        game_points->endGame("new_start");
        game_state->changeGameState("RESUME_GAME");
    }
}

void UpdateGame::onWinGame()
{
    if (keystate[SDL_SCANCODE_RETURN])
    {
        clearData();

        ball->resetBalls();
        bonus->clearBonus();

        bricks_level->clearData();
        free(bricks_level);
        game_points->resetLevel();

        game_points->endGame("new_start");
        game_state->changeGameState("MAIN_MENU");
    }
}

void UpdateGame::updateGame()
{
    SDL_PumpEvents();

    /* *** MENU STATE PROCEDURES *** */
    current_state = game_state->getCurrentState();

    /* *** KEYBOARD HANDLE *** */
    if (current_state != "MAIN_MENU")
        keysHandle(keystate);

    if (current_state == "MAIN_MENU")
    {
        mainMenuHandle();
    }

    /* *** SET DECLARATIONS AT START THE APPLICATION - AFTER MENU DESTROY: *** */
    if (current_state == "START_GAME")
    {
        onStartGame();
    }
    else if (current_state == "RESUME_GAME")
    {
        onResumeGame();
    }
    else if (current_state == "NEXT_LEVEL")
    {
        onNextLevel();
    }

    if (current_state == "LOSE_GAME")
    {
        onLoseGame();
    }
    else if (current_state == "WIN_GAME")
    {
        onWinGame();
    }
}


void UpdateGame::removeBrick() const
{
    // Add scores to actual
    game_points->updateScores(3);

    // Get number of brick, which is collided in recent frame...
    const int brick = collisions->getCollidedBrick();

    // and add it to Table of ignored bricks
    bricks_level->addToTableIgnoredBricks(brick);

    // Try a luck and randomize bonusName
    const std::string bonusName = this->bonus->getBonus();
    if (bonusName == "none")
    {
        // If collision occurred, get brick's coordinates needed to generate proper Bonus Pack
        const SDL_Rect dst_brick = *bricks_level->getOneBrick(brick);

        this->bonus->randomBonus();
        this->bonus->setBonusPosition(dst_brick);
    }
}

/* CREATING INSTANCE METHOD - SET OF BRICKS FROM PROPER LEVEL */
void UpdateGame::loadLevelAtStart()
{
    switch (level)
    {
    case 1:
        bricks_level = new BricksLevel1();
        break;

    case 2:
        bricks_level = new BricksLevel2();
        break;

    case 3:
        bricks_level = new BricksLevel3();
        break;

    case 4:
        bricks_level = new BricksLevel4();
        break;

    default:
        bricks_level = new BricksLevel1();
        break;
    }
}

void UpdateGame::debugKeys(const Uint8* keyState)
{
    if (keyState[SDL_SCANCODE_PAUSE])
        is_ball_motion = false;

    if (keyState[SDL_SCANCODE_P])
        ball->setBallMotion(0, "y", MOTION_RATE_BALL_Y);

    if (keyState[SDL_SCANCODE_L])
        ball->setBallMotion(0, "y", -MOTION_RATE_BALL_Y);

    if (keyState[SDL_SCANCODE_END])
        ball->setBallMotion(0, "x", MOTION_RATE_BALL_X);

    if (keyState[SDL_SCANCODE_PAGEDOWN])
        ball->setBallMotion(0, "x", -MOTION_RATE_BALL_X);

    if (keyState[SDL_SCANCODE_F1])
        game_state->changeGameState("START_GAME");

    if (keyState[SDL_SCANCODE_F12])
    {
        game_state->changeGameState("NEXT_LEVEL");
    }

    if (keyState[SDL_SCANCODE_DELETE])
        clearData();

    if (keyState[SDL_SCANCODE_1])
        activateBonusLaser();
    if (keyState[SDL_SCANCODE_2])
        activateBonusLive();
    if (keyState[SDL_SCANCODE_3])
        activateBonusSlowdown();
    if (keyState[SDL_SCANCODE_4])
        activateBonusDuplicateBall();
}

/* KEYBOARD HANDLE METHODS */
void UpdateGame::keysHandle(const Uint8* keyState)
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            done = true;
        }

        /* * DEBUG GOD MODE: * */
        debugKeys(keyState);
    }

    // If user pressed Space - ball was started moving
    if (keyState[SDL_SCANCODE_SPACE] || event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        is_ball_motion = true;

    if ((keyState[SDL_SCANCODE_LCTRL]
            || event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT) && is_gun)
    {
        auto offset = time_point_cast<std::chrono::seconds>(std::chrono::steady_clock::now()) - allow_to_shot_start_clock;
        if (offset >= 1s) {
            paddle->createBullet();
            allow_to_shot_start_clock = time_point_cast<std::chrono::seconds>(std::chrono::steady_clock::now());
        }
    }

    if (keyState[SDL_SCANCODE_ESCAPE])
    {
        game_state->changeGameState("MAIN_MENU");

        start_menu_music = true;
    }

    // STEER PADDLE TO THE LEFT
    if (keyState[SDL_SCANCODE_LEFT] || event.type == SDL_MOUSEMOTION && event.motion.xrel < 0)
    {
        event.motion.xrel = 0;

        // Set new position to x of paddle when LEFT key pressed
        if (event.type != SDL_MOUSEMOTION)
            paddle->setPaddleMotion(-MOTION_RATE_PADDLE);
        else
            paddle->setPaddleMotion(-9);

        // Back if paddle go off the screen at left
        const SDL_Rect temp_paddle = paddle->getPaddle();
        if (temp_paddle.x <= 0)
            paddle->setPaddlePosition(0);
    }

    // STEER PADDLE TO THE RIGHT
    else if (keyState[SDL_SCANCODE_RIGHT] || event.type == SDL_MOUSEMOTION && event.motion.xrel > 0)
    {
        event.motion.xrel = 0;

        // Set new position to x of paddle when RIGHT key pressed
        if (event.type != SDL_MOUSEMOTION)
            paddle->setPaddleMotion(MOTION_RATE_PADDLE);
        else
            paddle->setPaddleMotion(9);

        // Back if paddle go off the screen at right
        const SDL_Rect temp_paddle = paddle->getPaddle();
        if ((temp_paddle.x + temp_paddle.w) >= screen->w)
            paddle->setPaddlePosition(screen->w - temp_paddle.w);
    }
}

void UpdateGame::menuKeyHandle()
{
    if (game_state->getCurrentState() == "MAIN_MENU")
    {
        if (SDL_WaitEvent(&event))
        {
            if (event.type == SDL_QUIT || main_menu->getExitState())
            {
                done = true;
            }

            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_DOWN:
                    main_menu->moveSelection("down");
                    break;

                case SDLK_UP:
                    main_menu->moveSelection("up");
                    break;

                case SDLK_RETURN:
                    {
                        const bool is_new_game = main_menu->nextStep();

                        if (is_new_game)
                        {
                            game_state->changeGameState("START_GAME");
                            current_state = game_state->getCurrentState();

                            sound_system->stopMenuMusic();
                        }
                        break;
                    }

                    // QUIT FROM PROGRAM
                case SDLK_ESCAPE:
                    {
                        this->done = true;
                        break;
                    }

                default:
                    break;
                }
            }
        }
    }
}

void UpdateGame::menuMouseHandle()
{
    if (event.button.state == SDL_RELEASED && event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
    {
        const Sint32 x = event.button.x;
        const Sint32 y = event.button.y;

        if (x < 460 && x > 164)
        {
            if (main_menu->getPageNumber() == 1)
            {
                if (y > 140 && y < 173)
                {
                    const bool is_new_game = main_menu->nextStep();

                    if (is_new_game)
                    {
                        game_state->changeGameState("START_GAME");
                        current_state = game_state->getCurrentState();

                        sound_system->stopMenuMusic();
                    }
                }
                else if (y > 236 && y < 262)
                {
                    main_menu->setSelection(3);

                    main_menu->nextStep();
                }
                else if (y > 285 && y < 320)
                {
                    this->done = true;
                }
            }
            else
            {
                if (y > 140 && y < 173)
                {
                    main_menu->setSelection(1);

                    main_menu->nextStep();
                }
                else if (y > 180 && y < 202)
                {
                    main_menu->setSelection(2);

                    main_menu->nextStep();
                }
                else if (y > 223 && y < 237)
                {
                    main_menu->setSelection(3);

                    main_menu->nextStep();
                }
                else if (y > 263 && y < 278)
                {
                    main_menu->setSelection(4);

                    main_menu->nextStep();
                }
                else if (y > 300 && y < 315)
                {
                    main_menu->setSelection(5);

                    main_menu->nextStep();
                }
                else if (y > 341 && y < 353)
                {
                    main_menu->setSelection(6);

                    main_menu->nextStep();
                }
                else if (y > 378 && y < 391)
                {
                    main_menu->setSelection(7);

                    main_menu->nextStep();
                }
            }
        }
    }
}

void UpdateGame::setTimer()
{
    timeBeginPeriod(0);

    timer_id = timeSetEvent(10000, 0, &UpdateGame::TimeProc, 0, TIME_ONESHOT);
}

void CALLBACK UpdateGame::TimeProc(UINT uID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
    if (!set_paddle_default_look)
        set_paddle_default_look = true;

    if (slow_down) slow_down = false;

    timeKillEvent(timer_id);
    timeEndPeriod(0);
}

void UpdateGame::bonusHandle()
{
    if (bonus->getBonus() != "none")
    {
        const SDL_Rect temp_dst_paddle = paddle->getPaddle();
        const SDL_Rect temp_dst_bonus = bonus->getBonusPosition();

        bonus->moveBonus();

        detected_collision_bonus = collisions->detectCollision(temp_dst_bonus, temp_dst_paddle);

        if (detected_collision_bonus == "Vertical" || detected_collision_bonus == "Horizontal")
        {
            const auto which_bonus_exec = bonus->executeBonus();

            switch (which_bonus_exec)
            {
                case 1:
                    activateBonusLaser();
                    break;
                case 2:
                    activateBonusLive();
                    break;
                case 3:
                    activateBonusSlowdown();
                    break;
                case 4:
                    activateBonusDuplicateBall();
                    break;
                default:
                    activateBonusLive();
                    break;
            }
        }

        auto& bonus_pos = this->bonus->getBonusPosition();
        if (bonus_pos.y > screen->h)
            this->bonus->removeBonus();
    }

    paddle->moveBullets();

    if (set_paddle_default_look)
    {
        is_gun = false;
        paddle->changePaddle("paddle");

        set_paddle_default_look = false;
    }
}

void UpdateGame::activateBonusLaser()
{
    is_gun = true;
    paddle->changePaddle("paddle_war");
    setTimer();
}

void UpdateGame::activateBonusLive() const
{
    game_points->updateLives(1);
}

void UpdateGame::activateBonusSlowdown()
{
    slow_down = true;
    setTimer();
}

void UpdateGame::activateBonusDuplicateBall()
{
    if (ball->getBallNumbers() <= MAX_BALLS)
    {
        const int id = ball->createBall()-1;

        const int temp_x = paddle->getPaddlePosition("x");
        const int temp_w = paddle->getPaddlePosition("w");
        const int temp_y = paddle->getPaddlePosition("y");

        ball->setBallPosition(id, "x", temp_x + temp_w / 2);
        ball->setBallPosition(id, "y", temp_y - 21);

        y_motion_rates.push_back(MOTION_RATE_BALL_Y);
        x_motion_rates.push_back(0);
    }
}

void UpdateGame::clearData()
{
    if (is_gun)
    {
        set_paddle_default_look = true;
        is_gun = false;
        paddle->changePaddle("paddle");
        set_paddle_default_look = false;
    }

    if (slow_down) slow_down = false;
}