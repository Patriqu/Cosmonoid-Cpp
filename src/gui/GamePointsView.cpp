#include "gui/GamePointsView.h"

GamePointsView::GamePointsView()
    : screen(SDL_GetWindowSurface(SDL_GetWindowFromID(1))),
      game_points(new GamePoints()),
      scores_surface(NULL),
      lives_surface(NULL),
      level_surface(NULL),
      font(TTF_OpenFont("arialbd.ttf", 15)),
      font_end(NULL),
      font_end_2(NULL),
      font_color({255, 255, 255}),
      text_score(new char[12]),
      text_lives(new char[12]),
      text_level(new char[12])
{
    // Constant positions of points surfaces:
    score_dest.x = 40;
    score_dest.y = 15;

    lives_dest.x = 230;
    lives_dest.y = 15;

    level_dest.x = 430;
    level_dest.y = 15;

    // Default starting texts of scores:
    text_score = "Punkty: 0";
    c_text_score = const_cast<char*>(text_score.c_str());

    text_lives = "Zycia: 3";
    c_text_lives = const_cast<char*>(text_lives.c_str());

    text_level = "Poziom 1";
    c_text_level = const_cast<char*>(text_level.c_str());

    // Generate standard texts to display when starting the level:
    scores_surface = TTF_RenderText_Solid(font, c_text_score, font_color);
    lives_surface = TTF_RenderText_Solid(font, c_text_lives, font_color);
    level_surface = TTF_RenderText_Solid(font, c_text_level, font_color);
}

GamePointsView::~GamePointsView()
{
    SDL_FreeSurface(screen);
    SDL_FreeSurface(scores_surface);
    SDL_FreeSurface(lives_surface);
    SDL_FreeSurface(level_surface);
    SDL_FreeSurface(end_surface);
    SDL_FreeSurface(end_surface_2);

    delete screen;
    delete scores_surface;
    delete lives_surface;
    delete level_surface;
    delete end_surface;
    delete end_surface_2;

    TTF_CloseFont(font);
}

/* Placing all scores, lives and bonus icons at the screen */
void GamePointsView::placeAllPoints()
{
    // Update scores at frame
    updatePointsText();

    // Temporaries
    std::string end_state = game_points->getEndState();
    bool is_changed_lives = game_points->isChangedLives();

    // Sum number of lives and update it at screen
    if (is_changed_lives == true)
        updateLivesDisplay();

    if (end_state == "new_start")
        updateLevelDisplay();

    // Blit all points and scores at screen
    SDL_BlitSurface(scores_surface, 0, screen, &score_dest);
    SDL_BlitSurface(lives_surface, 0, screen, &lives_dest);
    SDL_BlitSurface(level_surface, 0, screen, &level_dest);

    /* EXECUTED ONLY WHEN GAME STATE IS LOSE, WIN OR NEXT LEVEL */
    if (end_state == "lose")
    {
        if ((font_end == NULL) && (font_end_2 == NULL))
        {
            font_end = TTF_OpenFont("arialbd.ttf", 30);
            font_end_2 = TTF_OpenFont("arial.ttf", 15);
        }

        end_surface = TTF_RenderText_Solid(font_end, "Przegrales", font_color);
        end_surface_2 = TTF_RenderText_Solid(font_end_2, "Nacisnij Enter, by zaczac gre od nowa", font_color);

        SDL_Rect end_msg_dest;
        end_msg_dest.x = 220;
        end_msg_dest.y = 180;

        SDL_Rect end_msg_dest_2;
        end_msg_dest_2.x = 200;
        end_msg_dest_2.y = 225;

        SDL_BlitSurface(end_surface, 0, screen, &end_msg_dest);
        SDL_BlitSurface(end_surface_2, 0, screen, &end_msg_dest_2);

        // reset points
        game_points->resetData();

        // after that free surface:
        SDL_FreeSurface(end_surface);
        SDL_FreeSurface(end_surface_2);
        end_surface = NULL;
        end_surface_2 = NULL;
    }
    else if (end_state == "next_level")
    {
        // Open Fonts
        if (font_end == NULL && font_end_2 == NULL)
        {
            font_end = TTF_OpenFont("arialbd.ttf", 30);
            font_end_2 = TTF_OpenFont("arial.ttf", 15);
        }

        // Set texts
        end_surface = TTF_RenderText_Solid(font_end, "Poziom ukonczony", font_color);
        end_surface_2 = TTF_RenderText_Solid(font_end_2, "Nacisnij Enter, aby przejsc do nastepnego.", font_color);

        // Set destinations to put texts at screen
        SDL_Rect end_msg_dest;
        end_msg_dest.x = 205;
        end_msg_dest.y = 180;

        SDL_Rect end_msg_dest_2;
        end_msg_dest_2.x = 200;
        end_msg_dest_2.y = 225;

        // Blit texts at screen
        SDL_BlitSurface(end_surface, 0, screen, &end_msg_dest);
        SDL_BlitSurface(end_surface_2, 0, screen, &end_msg_dest_2);

        // after that free surface:
        SDL_FreeSurface(end_surface);
        SDL_FreeSurface(end_surface_2);
        end_surface = NULL;
        end_surface_2 = NULL;
    }
    else if (end_state == "win")
    {
        // Open fonts
        if (font_end == NULL)
        {
            font_end = TTF_OpenFont("arialbd.ttf", 30);
            font_end_2 = TTF_OpenFont("arial.ttf", 15);
        }

        // Set texts
        end_surface = TTF_RenderText_Solid(font_end, "Gratulacje! Wygrales!", font_color);
        end_surface_2 = TTF_RenderText_Solid(font_end_2, "Nacisnij Enter aby przejsc do menu", font_color);

        // Set destinations to put texts at screen
        SDL_Rect end_msg_dest;
        end_msg_dest.x = 200;
        end_msg_dest.y = 180;

        SDL_Rect end_msg_dest_2;
        end_msg_dest_2.x = 200;
        end_msg_dest_2.y = 225;

        // Blit texts at screen
        SDL_BlitSurface(end_surface, 0, screen, &end_msg_dest);
        SDL_BlitSurface(end_surface_2, 0, screen, &end_msg_dest_2);

        // Reset points earned in game (starting new game)
        game_points->resetData();

        // after that free surface:
        SDL_FreeSurface(end_surface);
        SDL_FreeSurface(end_surface_2);
        end_surface = NULL;
        end_surface_2 = NULL;
    }
        // IF PLAYER PLAY WITH "NEW START" AFTER "LOSE":
    else if (game_points->getEndState() == "new_start")
    {
        // Close all fonts
        if (font_end != NULL)
        {
            TTF_CloseFont(font_end);
            font_end = NULL;
        }

        if (font_end_2 != NULL)
        {
            TTF_CloseFont(font_end_2);
            font_end_2 = NULL;
        }

        // Return to default state value
        game_points->endGame("none");
    }
}

/* Updating actual text of scores displayed at the screen */
void GamePointsView::updatePointsText()
{
    SDL_FreeSurface(scores_surface);

    int points = game_points->getScores();

    /* Conversions of text */
    std::ostringstream ss;
    ss << points;

    std::string temp = ss.str();

    text_score = "Punkty: " + temp;
    c_text_score = const_cast<char*>(text_score.c_str());

    // Generate text of scores
    scores_surface = TTF_RenderText_Solid(font, c_text_score, font_color);
}

/* Updating actual text of lives left displayed at the screen */
void GamePointsView::updateLivesDisplay()
{
    SDL_FreeSurface(lives_surface);

    int lives = game_points->getLives();

    /* Conversions of text */
    std::ostringstream ss;
    ss << lives;

    std::string temp = ss.str();

    text_lives = "Zycia: " + temp;
    c_text_lives = const_cast<char*>(text_lives.c_str());

    // Generate text of lives left
    lives_surface = TTF_RenderText_Solid(font, c_text_lives, font_color);
}

void GamePointsView::updateLevelDisplay()
{
    SDL_FreeSurface(level_surface);

    int level = game_points->getLevelNumber();

    /* Conversions of text */
    std::ostringstream ss;
    ss << level;

    std::string temp = ss.str();

    text_level = "Poziom " + temp;
    c_text_level = const_cast<char*>(text_level.c_str());

    // Generate text of lives left
    level_surface = TTF_RenderText_Solid(font, c_text_level, font_color);
}
