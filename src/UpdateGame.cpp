#include "UpdateGame.h"

bool UpdateGame:: slow_down = false;
bool UpdateGame:: set_paddle_default_look = false;
MMRESULT UpdateGame:: timerID;


UpdateGame:: UpdateGame( GameState* game_state, /*std::map<std::string, int>& surfer,*/ const Uint8* keystate, int level )
    : done ( false ),
    game_state ( game_state ),
    //surf_nbs ( surfer ),
    screen ( SDL_GetWindowSurface(SDL_GetWindowFromID(1)) ),

    MAX_LEVEL ( 4 ),
    keystate ( keystate ),
    level ( level ),
    current_state ( "" ),
    is_ball_motion ( false ),

    MOTION_RATE_BALL_Y ( 4 ),
    MOTION_RATE_BALL_X ( 9 ),

    MOTION_RATE_BALL_X_SLOW ( 3 ),
    MOTION_RATE_BALL_Y_SLOW ( 2 ),

    MOTION_RATE_PADDLE ( 6 ),
    main_menu ( new MainMenu() ),
    paddle ( new Paddle( /*surfer*/ ) ),
    ball ( new Ball( /*surfer*/ ) ),
    bricks_level ( NULL ),
    collisions ( new Collisions() ),
    game_points ( new GamePoints() ),
    bonus ( new Bonus() ),
    detected_collision_brick ( "" ),
    detected_collision_paddle ( "" ),
    detected_collision_bonus( "" ),
    detected_collision_shoot( "" ),
    nr_of_collision(0),
    is_gun ( false ),
    is_shoot ( false ),
    ball_numbers( 0 ),
    MAX_BALLS( 4 ),
    start_menu_music ( true )
{
    y_motion_rates.push_back(MOTION_RATE_BALL_Y);
    x_motion_rates.push_back(0);

    // Music definitions
    menu_music = Mix_LoadMUS("sound/menu_music.mp3");
    Mix_VolumeMusic( 15 );

    // Sound sample definition
    snd_bounce = Mix_LoadWAV("sound/92622__nigelcoop__canbounce-2.wav");
    Mix_Volume( 1, 8 );

    // Load data of images in menu
    SDL_Surface* screen = SDL_GetWindowSurface(SDL_GetWindowFromID(1));
    int h = screen->h;
    std:: string tmp;

    sprintf((char*)tmp.c_str(), "%d", h);
    std:: string str = tmp.c_str();

    ResManager:: getInstance().loadImageMenu(str);
    ResManager:: getInstance().loadImageSelection();

    // Load images of game objects:
    ResManager:: getInstance().loadImageBall();
    ResManager:: getInstance().loadImagePaddle();
    ResManager:: getInstance().loadImagePaddleWar();
    ResManager:: getInstance().loadImageBullet();
    ResManager:: getInstance().loadImageBlocks();

    ResManager:: getInstance().loadImageLivePack();
    ResManager:: getInstance().loadImageSlowPack();
    ResManager:: getInstance().loadImageDupPack();
    ResManager:: getInstance().loadImageGunPack();
}

UpdateGame:: ~UpdateGame()
{
    delete paddle;
    delete ball;
    delete bricks_level;

    delete keystate;
    delete game_state;
}

void UpdateGAme:: mainMenuHandle() {
    if (SDL_GetRelativeMouseMode() == SDL_TRUE)
        SDL_SetRelativeMouseMode(SDL_FALSE);

    // Handle keyboard in menu
    menuKeyHandle();
    menuMouseHandle();

    // CHECK IF IS CHANGED OPTIONS TO EXECUTE AND DO IT
    if ( main_menu -> isOptionToChange() == true || start_menu_music == true )
    {
        std::string option = main_menu -> getChangedText();

        if ( option == "volume_sound" || start_menu_music == true )
        {
            std::string sound_vol = main_menu -> getVolume( "sound" );

            if ( sound_vol == "off" )
                Mix_Volume( 1, 0 );
            else if ( sound_vol == "low" )
                Mix_Volume( 1, 8 );
            else if ( sound_vol == "medium" )
                Mix_Volume( 1, 15 );
            else if ( sound_vol == "high" )
                Mix_Volume( 1, 30 );
            else if ( sound_vol == "very high" )
                Mix_Volume( 1, 45 );
        }
        if ( option == "volume_music" || start_menu_music == true )
        {
            std::string music_vol = main_menu -> getVolume( "music" );

            if ( music_vol == "off" )
                Mix_VolumeMusic( 0 );
            else if ( music_vol == "low" )
                Mix_VolumeMusic( 8 );
            else if ( music_vol == "medium" )
                Mix_VolumeMusic( 15 );
            else if ( music_vol == "high" )
                Mix_VolumeMusic( 30 );
            else if ( music_vol == "very high" )
                Mix_VolumeMusic( 45 );
        }
    }

    if ( start_menu_music == true )
    {
        Mix_PlayMusic(menu_music, -1);

        start_menu_music = false;
    }
}

void UpdateGame:: startGameHandle() {
    SDL_SetRelativeMouseMode(SDL_TRUE);

    if( is_ball_motion == true )
        is_ball_motion = false;

    // Set coordinates to place objects on the screen after start a level
    paddle -> posPaddleAtStart();
    ball -> createBall();
    ball_numbers++;

    // Finally load bricks from current level at start
    if ( level != 1 )
    {
        level = 1;
        loadLevelAtStart();
    }
    else
    {
        loadLevelAtStart();
    }

    // Initiate generator of random numbers for random a bonus
    bonus -> initiateGenerator();
}

void UpdateGame:: resumeGameHandle() {
    // IF ALL BRICKS ARE DELETED FROM SCREEN - PLAYER WIN:
    if ( (bricks_level != NULL) && (bricks_level->getTableOfIgnoredBricks().size()) == (bricks_level->getAllBricks().size()) )
    {
        // We don't want to move a ball when starting new or the same level
        for (int i = 0; i < ball_numbers; i++)
        {
            y_motion_rates[i] = MOTION_RATE_BALL_Y;
            x_motion_rates[i] = 0;
        }
        is_ball_motion = false;
        nr_of_collision = 0;

        if ( level < MAX_LEVEL )
        {
            game_points -> endGame( "next_level" );
            if ( keystate [ SDL_SCANCODE_RETURN ] )
                game_state -> changeGameState( "NEXT_LEVEL" );
        }
        else
        {
            game_points -> endGame( "win" );
            game_state -> changeGameState( "WIN_GAME" );
        }
    }

    /* *** BASIC BALL MOTION HANDLE *** */
    if ( is_ball_motion == true )
    {
        for (int i = 0; i < ball_numbers; i++)
        {
            // motion in "y" axis
            ball -> setBallMotion( i, "y", y_motion_rates[i] );

            // motion in "x" axis
            ball -> setBallMotion( i, "x", x_motion_rates[i] );
        }
    }

    /* *** WALL COLLISIONS HANDLE *** */
    int ball_x[ball_numbers+1];
    int ball_y[ball_numbers+1];
    int ball_w[ball_numbers+1];
    int ball_h[ball_numbers+1];

    for ( int i = 0; i < ball_numbers; i++ )
    {
        ball_x[i] = ball -> getBallPosition( i, "x" );
        ball_y[i] = ball -> getBallPosition( i, "y" );
        ball_w[i] = ball -> getBallPosition( i, "w" );
        ball_h[i] = ball -> getBallPosition( i, "h" );

        // TOP WALL:
        if ( ball_y[i] < 0 )
        {
            ball -> setBallPosition( i, "y", 0 );
            y_motion_rates[i] *= -1;
        }
        // LEFT WALL:
        else if ( ball_x[i] < 0 )
        {
            ball -> setBallPosition( i, "x", 0 );
            x_motion_rates[i] *= -1;
        }
        // RIGHT WALL:
        else if ( (ball_x[i] + ball_w[i]) > screen->w /*surf_nbs["width"]*/ )
        {
            ball -> setBallPosition( i, "x", /*surf_nbs["width"]*/ screen->w-ball_w[i] );
            x_motion_rates[i] *= -1;
        }
        // BOTTOM AND LOSE HANDLE:
        else if ( (ball_y[i] + ball_h[i]) > screen->h /*surf_nbs["height"]*/ )
        {
            if ( ball_numbers > 1 )
            {
                x_motion_rates.erase(x_motion_rates.begin() + i);
                y_motion_rates.erase(y_motion_rates.begin() + i);

                ball -> deleteBall(i);
                ball_numbers--;
            }
            else if (ball_numbers == 1)
            {
                game_points -> updateLives( -1 );

                // Back to starting positions
                paddle -> posPaddleAtStart();
                ball -> posBallAtStart(i);

                // Set default values of ball motion
                for (int i = 0; i < ball_numbers; i++)
                {
                    y_motion_rates[i] = MOTION_RATE_BALL_Y;
                    x_motion_rates[i] = 0;
                }

                is_ball_motion = false;

                nr_of_collision = 0;

                int actual_lives = game_points -> getLives();
                if ( actual_lives == 0 )
                {
                    game_points -> endGame( "lose" );
                    game_state -> changeGameState ( "LOSE_GAME" );
                }
            }

        }
    }

    /* *** COLLISION OF OBJECTS HANDLE *** */
    SDL_Rect& temp_dst_paddle = paddle -> getPaddle();
    std:: map < const int, SDL_Rect* > temp_bricks;
    temp_bricks = bricks_level -> getAllBricks();

    // CHECK LASER COLLISION:
    if ( is_shoot == true )
    {
        SDL_Rect& temp_dst_shoot = paddle -> getBullet();
        detected_collision_shoot = collisions -> detectCollision( temp_dst_shoot, temp_bricks );
    }

    // CHECK BALL -> PADDLE & BALL -> BRICK COLLISIONS:
    for ( int i = 0; i < ball_numbers; i++ )
    {
        SDL_Rect& temp_dst_ball = ball -> getBall(i);

        detected_collision_brick = collisions -> detectCollision( temp_dst_ball, temp_bricks );
        detected_collision_paddle = collisions -> detectCollision( temp_dst_ball, temp_dst_paddle );

        // Change move vector of ball if collision was detected:
        if ( detected_collision_brick == "Vertical" || detected_collision_paddle == "Vertical" )
        {
            y_motion_rates[i] *= -1;

            if ( detected_collision_paddle == "Vertical" && (x_motion_rates[i] == MOTION_RATE_BALL_X || x_motion_rates[i] == -MOTION_RATE_BALL_X) )
            {
                y_motion_rates[i] = MOTION_RATE_BALL_Y;

                if ( ball -> getBallPosition( i, "x" ) > 0 )
                    x_motion_rates[i] = MOTION_RATE_BALL_X_SLOW;
                else
                    x_motion_rates[i] = -MOTION_RATE_BALL_X_SLOW;

                ball -> setBallMotion( i, "x", x_motion_rates[i] );
            }

            if ( Mix_PlayChannel( 1, snd_bounce, 0 ) == -1 )
            {
                printf("Mix_PlayChannel: %s\n",Mix_GetError());
            }
        }
        else if ( detected_collision_brick == "Horizontal" || detected_collision_paddle == "Horizontal" )
        {
            // Change move x-axis
            if ( x_motion_rates[i] != -MOTION_RATE_BALL_X )
                x_motion_rates[i] = MOTION_RATE_BALL_X;

            x_motion_rates[i] *= -1;

            // Change move y-axis
            if ( y_motion_rates[i] == MOTION_RATE_BALL_Y || y_motion_rates[i] == -MOTION_RATE_BALL_Y )
                y_motion_rates[i] /= -MOTION_RATE_BALL_Y;
            else
                y_motion_rates[i] /= -MOTION_RATE_BALL_Y_SLOW;

            y_motion_rates[i] *= MOTION_RATE_BALL_Y_SLOW;

            ball -> setBallMotion( i, "y", y_motion_rates[i] );

            // play bounce sound
            if ( Mix_PlayChannel( 1, snd_bounce, 0 ) == -1 )
            {
                printf("Mix_PlayChannel: %s\n",Mix_GetError());
            }

            // If ball is hanging at paddle, fix this:
            bool is_bottleneck = collisions -> isBottleneck();
            if ( is_bottleneck )
            {
                int paddle_position = paddle -> getPaddlePosition("x");
                int paddle_width = paddle -> getPaddlePosition("w");
                int paddle_length = paddle_position + paddle_width;

                int ball_position = ball -> getBallPosition(i, "x");
                int ball_width = ball -> getBallPosition(i, "w");
                int ball_length = ball_position + ball_width;

                int dist_x = std::abs( paddle_position - ball_position );
                int dist_w = std::abs( paddle_length - ball_position );

                if ( (ball_length < screen->w /*surf_nbs["width"]*/ - ball_width) && dist_x < dist_w )
                    ball -> correctBottleneck( i, -dist_x );
                else
                    ball -> correctBottleneck( i, dist_w );
            }
        }

        if ( detected_collision_brick != "None" )
        {
            deleteBrickHandle();
        }

        bonusHandle();
    }

    if ( detected_collision_shoot == "Vertical" )
    {
        deleteBrickHandle();
    }

    collisions->clearData();
    detected_collision_brick = "None";
    detected_collision_paddle = "None";
    detected_collision_shoot = "None";
}

void UpdateGame:: nextLevelHandle() {
    clearDatas();

    // Set starting positions of ball and paddle
    paddle -> posPaddleAtStart();

    ball_numbers = 0;
    ball -> resetBall();
    bonus -> clearBonus();
    y_motion_rates.clear();
    x_motion_rates.clear();
    y_motion_rates.push_back(MOTION_RATE_BALL_Y);
    x_motion_rates.push_back(0);
    ball -> createBall();
    ball_numbers++;

    bricks_level -> clearData();
    free( bricks_level );

    // Load next level
    if ( level < MAX_LEVEL )
        level += 1;
    else
        level = 1;

    loadLevelAtStart();

    // Set game state to "Next Level"
    game_points -> updateLevel( 1 );

    game_points -> endGame( "new_start" );
    game_state -> changeGameState( "RESUME_GAME" );
}

void UpdateGame:: loseGameHandle() {
    clearDatas();

    // We don't want to move a ball when starting new or the same level
    y_motion_rates[0] = MOTION_RATE_BALL_Y;
    x_motion_rates[0] = 0;
    is_ball_motion = false;

    if ( keystate [ SDL_SCANCODE_RETURN ] )
    {
        ball_numbers = 0;
        ball -> resetBall();
        ball -> createBall();
        ball_numbers++;

        bonus -> clearBonus();

        // Back to level 1 - restart game after lose
        if ( level != 1 )
        {
            bricks_level -> clearData();
            bricks_level -> replaceAllBricks();

            level = 1;
            loadLevelAtStart();
        }
        else if ( level == 1 )
        {
            // Reset data and clear all tables left from previous level
            bricks_level -> clearData();
            bricks_level -> replaceAllBricks();
        }

        game_points -> resetLevel();

        game_points -> endGame( "new_start" );
        game_state -> changeGameState( "RESUME_GAME" );
    }
}

void UpdateGame:: winGameHandle() {
    if ( keystate [ SDL_SCANCODE_RETURN ] )
    {
        clearDatas();

        ball_numbers = 0;
        ball -> resetBall();
        bonus -> clearBonus();

        bricks_level -> clearData();
        free( bricks_level );
        game_points -> resetLevel();

        game_points -> endGame( "new_start" );
        game_state -> changeGameState( "MAIN_MENU" );
    }
}

void UpdateGame::updateGame()
{
    // Pumping events
    SDL_PumpEvents();

    /* *** MENU STATE PROCEDURES *** */
    current_state = game_state -> getCurrentState();

    /* *** KEYBOARD HANDLE *** */
    if ( current_state != "MAIN_MENU" )
        keysHandle( keystate );

    if ( current_state == "MAIN_MENU" )
    {
        mainMenuHandle();
    }

    /* *** SET DECLARATIONS AT START THE APPLICATION - AFTER MENU DESTROY: *** */
    if ( current_state == "START_GAME" )
    {
        startGameHandle();
    }
    else if ( current_state == "RESUME_GAME" )
    {
        resumeGameHandle();
    }
    /* *** ENDING HANDLE *** */
    else if ( current_state == "NEXT_LEVEL" )
    {
        nextLevelHandle();
    }

    if ( current_state == "LOSE_GAME" )
    {
        loseGameHandle();
    }
    else if ( current_state == "WIN_GAME" )
    {
        winGameHandle();
    }
}


void UpdateGame:: deleteBrickHandle() {
    // Add scores to actual
    game_points -> updateScores( 3 );

    // Get number of brick, which is collided in recent frame...
    int brick = collisions -> getCollidedBrick();

    // and add it to Table of ignored bricks
    bricks_level -> addToTableIgnoredBricks( brick );

    // Try a luck and randomize bonus
    std::string bonus = this->bonus -> getBonus();
    if ( bonus == "none" )
    {
        // If collision occured, get brick's coordinates needed to generate proper Bonus Pack
        SDL_Rect dst_brick = *(bricks_level -> getOneBrick( brick ));

        this->bonus -> randomBonus();
        this->bonus -> setBonusPosition( dst_brick );
    }
}

/* CREATING INSTANCE METHOD - SET OF BRICKS FROM PROPER LEVEL */
void UpdateGame:: loadLevelAtStart()
{
    switch ( level )
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

/* KEYBOARD HANDLE METHODS */
void UpdateGame:: keysHandle( const Uint8 * keystate )
{
    int x = event.motion.x;

    while( SDL_PollEvent( &event ) )
    {
        if( event.type == SDL_QUIT )
        {
            done = true;
        }
    }

    SDL_Rect temp_paddle = paddle -> getPaddle();

    /* * DEBUG GOD MODE: * */
    if ( keystate [ SDL_SCANCODE_PAUSE ] )
        is_ball_motion = false;

    if ( keystate [ SDL_SCANCODE_P ] )
        ball -> setBallMotion( 0, "y", MOTION_RATE_BALL_Y );

    if ( keystate [ SDL_SCANCODE_L ] )
        ball -> setBallMotion( 0, "y", -MOTION_RATE_BALL_Y );

    if ( keystate [ SDL_SCANCODE_END ] )
        ball -> setBallMotion( 0, "x", MOTION_RATE_BALL_X );

    if ( keystate [ SDL_SCANCODE_PAGEDOWN ] )
        ball -> setBallMotion( 0, "x", -MOTION_RATE_BALL_X );

    if ( keystate [ SDL_SCANCODE_F1 ] )
        game_state -> changeGameState( "START_GAME" );

    if ( keystate [ SDL_SCANCODE_F12 ] )
        game_state -> changeGameState( "NEXT_LEVEL" );

    if ( keystate [ SDL_SCANCODE_DELETE ] )
        clearDatas();

    /* *************** */


    // If user pressed Space - ball was started moving
    if ( keystate [ SDL_SCANCODE_SPACE ] || (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT ) )
        is_ball_motion = true;

    if ( (keystate [ SDL_SCANCODE_LCTRL ] || (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT )) && is_gun == true )
    {
        is_shoot = true;
        paddle -> createBullet();
    }

    if ( keystate [ SDL_SCANCODE_ESCAPE ] )
    {
        game_state -> changeGameState( "MAIN_MENU" );

        start_menu_music = true;
    }

    // STEER PADDLE TO THE LEFT
    if ( keystate [ SDL_SCANCODE_LEFT ] || (event.type == SDL_MOUSEMOTION && (event.motion.xrel < 0)) )
    {
        event.motion.xrel = 0;

        // Set new position to x of paddle when LEFT key pressed
        if (event.type != SDL_MOUSEMOTION)
            paddle -> setPaddleMotion( -MOTION_RATE_PADDLE );
        else
            paddle -> setPaddleMotion(-9);

        // Back if paddle go off the screen at left
        if ( temp_paddle.x <= 0 )
            paddle -> setPaddlePosition(0);
    }

    // STEER PADDLE TO THE RIGHT
    else if ( keystate [ SDL_SCANCODE_RIGHT ] || (event.type == SDL_MOUSEMOTION && (event.motion.xrel > 0) ) )
    {
        event.motion.xrel = 0;

        // Set new position to x of paddle when RIGHT key pressed
        if (event.type != SDL_MOUSEMOTION)
            paddle -> setPaddleMotion( MOTION_RATE_PADDLE );
        else
            paddle -> setPaddleMotion(9);

        // Back if paddle go off the screen at right
        if ( (temp_paddle.x + temp_paddle.w) >= screen->w /*surf_nbs["width"]*/ )
            paddle -> setPaddlePosition( screen->w - temp_paddle.w );
    }

}

void UpdateGame:: menuKeyHandle()
{
    // ONLY VALID KEYS WHEN GAME STATE IS "MAIN_MENU" (MENU MODE):
    if ( game_state -> getCurrentState() == "MAIN_MENU" )
    {
        //If there's an event to handle
        if( SDL_WaitEvent( &event ) )
        {
            if( event.type == SDL_QUIT || main_menu -> getExitState() == true )
            {
                done = true;
            }

            //If a key was pressed
            if( event.type == SDL_KEYDOWN )
            {
                switch( event.key.keysym.sym )
                {
                    case SDLK_DOWN:
                        main_menu -> moveSelection( "down" );
                        break;

                    case SDLK_UP:
                        main_menu -> moveSelection( "up" );
                        break;

                    case SDLK_RETURN:
                    {
                        bool is_new_game = main_menu -> nextStep();

                        if ( is_new_game == true )
                        {
                            game_state -> changeGameState( "START_GAME" );
                            current_state = game_state -> getCurrentState();

                            stop_menu_music();
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

void UpdateGame:: menuMouseHandle()
{
    // click at option in menu
    //if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1))
    //    std:: cout << "\nMouse Button 1(left) is pressed.\n";

    if( event.button.state == SDL_RELEASED && event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT )
    {
        int x = event.button.x;
        int y = event.button.y;

        //std:: cout << "\nx: " << x;
        //std:: cout << "\ny: " << y;

        if (x < 460 && x > 164)
        {
            if (main_menu->getPageNumber() == 1)
            {
                if (y>140 && y < 173)
                {
                    bool is_new_game = main_menu -> nextStep();

                    if ( is_new_game == true )
                    {
                        game_state -> changeGameState( "START_GAME" );
                        current_state = game_state -> getCurrentState();

                        stop_menu_music();
                    }
                }
                else if (y>180 && y < 210)
                {

                }
                else if (y>236 && y < 262)
                {
                    main_menu -> setSelection(3);

                    main_menu -> nextStep();
                }
                else if (y>285 && y < 320)
                {
                    this->done = true;
                }
            }
            else
            {
                if (y>140 && y < 173)
                {
                    main_menu -> setSelection(1);

                    main_menu -> nextStep();
                }
                else if (y>180 && y < 202)
                {
                    main_menu -> setSelection(2);

                    main_menu -> nextStep();
                }
                else if (y>223 && y < 237)
                {
                    main_menu -> setSelection(3);

                    main_menu -> nextStep();
                }
                else if (y>263 && y < 278)
                {
                    main_menu -> setSelection(4);

                    main_menu -> nextStep();
                }
                else if (y>300 && y < 315)
                {
                    main_menu -> setSelection(5);

                    main_menu -> nextStep();
                }
                else if (y>341 && y < 353)
                {
                    main_menu -> setSelection(6);

                    main_menu -> nextStep();
                }
                else if (y>378 && y < 391)
                {
                    main_menu -> setSelection(7);

                    main_menu -> nextStep();
                }
            }
        }
    }
}

void UpdateGame:: setTimer()
{
    timeBeginPeriod(0);

    timerID = timeSetEvent(10000, 0, &UpdateGame:: TimeProc, 0, TIME_ONESHOT);
}

void CALLBACK UpdateGame:: TimeProc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
    if ( set_paddle_default_look == false )
        set_paddle_default_look = true;

    if ( slow_down == true )
    {
        slow_down = false;
    }

    timeKillEvent(timerID);
    timeEndPeriod(0);
}

void UpdateGame:: bonusHandle()
{
    if ( bonus -> getBonus() != "none" )
        {
            SDL_Rect temp_dst_paddle = paddle -> getPaddle();
            SDL_Rect temp_dst_bonus = bonus -> getBonusPosition();

            bonus -> moveBonus();

            detected_collision_bonus = collisions -> detectCollision( temp_dst_bonus, temp_dst_paddle );

            if ( detected_collision_bonus == "Vertical" || detected_collision_bonus == "Horizontal" )
            {
                detected_collision_bonus = "none";

                int which_bonus_exec = bonus -> executeBonus();

                switch ( which_bonus_exec )
                {
                    // gun
                    case 1:
                            is_gun = true;
                            paddle -> changePaddle( "paddle_war" );
                            setTimer();
                            which_bonus_exec = 0;
                            break;

                    // live
                    case 2:
                            game_points -> updateLives( 1 );
                            which_bonus_exec = 0;
                            break;

                     // slow
                    case 3:
                            slow_down = true;
                            setTimer();
                            which_bonus_exec = 0;
                            break;

                    // dup
                    case 4:
                            if ( ball_numbers < MAX_BALLS )
                            {
                                int id = ball -> createBall();
                                ball_numbers++;

                                int temp_x = paddle -> getPaddlePosition( "x" );
                                int temp_w = paddle -> getPaddlePosition( "w" );
                                int temp_y = paddle -> getPaddlePosition( "y" );

                                ball -> setBallPosition ( id, "x", temp_x + temp_w/2 );
                                ball -> setBallPosition ( id, "y", temp_y - 21 );

                                y_motion_rates.push_back(MOTION_RATE_BALL_Y);
                                x_motion_rates.push_back(0);
                            }
                            which_bonus_exec = 0;
                            break;
                }
            }

            SDL_Rect& bonus_pos = this->bonus -> getBonusPosition();
            if ( bonus_pos.y > screen->h /*surf_nbs["height"]*/ )
                this->bonus -> removeBonus();
        }

        if ( is_shoot == true )
        {
            paddle -> moveBullet();
        }

        if ( set_paddle_default_look == true )
        {
            is_gun = false;
            paddle -> changePaddle( "paddle" );

            set_paddle_default_look = false;
        }
}

void UpdateGame:: clearDatas()
{
    if( is_gun == true )
    {
        set_paddle_default_look = true;
        is_gun = false;
        paddle -> changePaddle( "paddle" );
        set_paddle_default_look = false;
    }

    if( slow_down == true )
    {
        slow_down = false;
    }
}

int UpdateGame:: getBallNumbers()
{
    return ball_numbers;
}

void UpdateGame:: stop_menu_music()
{
    Mix_HaltMusic();
    //Mix_FreeMusic(menu_music);
    //menu_music = NULL;
}
