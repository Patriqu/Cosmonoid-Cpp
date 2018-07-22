#include "MainMenuView.h"

MainMenuView:: MainMenuView()
    : screen_mode_name( "none" ),
    resolution_name ( "640x480" ),
    bgd_name( "yes" ),
    screen( SDL_GetWindowSurface(SDL_GetWindowFromID(1)) ),
    main_menu ( new MainMenu() ),
    font ( TTF_OpenFont("arialbd.ttf", 20) ),
    font_sec ( TTF_OpenFont("arialbd.ttf", 13) ),
    font_color ( { 0, 0, 0 } ),

    new_surface ( NULL ),
    trial_surface ( NULL ),
    options_surface ( NULL ),
        opt_screen_surface ( NULL ),
        opt_resolution_surface ( NULL ),
        opt_bgd_surface ( NULL ),
        opt_language_surface ( NULL ),
        opt_volume_sound_surface ( NULL ),
        opt_volume_music_surface ( NULL ),
        opt_back_surface ( NULL ) ,
    quit_surface ( NULL ),

    restart_warn_surface ( NULL ),

    text_new( new char[16] ),
    text_trial( new char[16] ),
    text_options( new char[16] ),
        text_opt_screen( new char[16] ),
        text_opt_resolution( new char[16] ),
        text_opt_bgd( new char[16] ),
        text_opt_language( new char[16] ),
        text_opt_volume_sound( new char[16] ),
        text_opt_volume_music( new char[16] ),
        text_opt_back( new char[16] ),
    text_quit( new char[16] ),

    text_restart_warn( new char[16] ),

    page ( 1 )
{
    initOptions();
}

MainMenuView:: ~MainMenuView()
{
    SDL_FreeSurface(screen);
    SDL_FreeSurface(new_surface);
    SDL_FreeSurface(trial_surface);
    SDL_FreeSurface(options_surface);
        SDL_FreeSurface(opt_screen_surface);
        SDL_FreeSurface(opt_resolution_surface);
        SDL_FreeSurface(opt_bgd_surface);
        SDL_FreeSurface(opt_language_surface);
        SDL_FreeSurface(opt_volume_sound_surface);
        SDL_FreeSurface(opt_volume_music_surface);
        SDL_FreeSurface(opt_back_surface);
    SDL_FreeSurface(quit_surface);

    SDL_FreeSurface(restart_warn_surface);

    delete screen;
    delete new_surface;
    delete trial_surface;
    delete options_surface;
        delete opt_screen_surface;
        delete opt_resolution_surface;
        delete opt_bgd_surface;
        delete opt_language_surface;
        delete opt_volume_sound_surface;
        delete opt_volume_music_surface;
        delete opt_back_surface;
    delete quit_surface;

    delete restart_warn_surface;

    TTF_CloseFont( font );
}

void MainMenuView:: renderMenu()
{
    SDL_BlitSurface( ResManager::getInstance().getImage( "menu" ), 0, screen, &bgd );

    updateDisplaySelection();

    SDL_BlitSurface( ResManager::getInstance().getImage( "selection" ), 0, screen, &selection_dst );

    updateTexts();
    renderTexts();
}

void MainMenuView:: renderTexts()
{
    page = main_menu -> getPageNumber();
    bool is_option_restart_warn = main_menu -> isOptionRestartWarn();

    if ( page == 1 )
    {
        if ( is_option_restart_warn == true )
            main_menu -> resetOptionRestartWarn();

        SDL_BlitSurface( new_surface, 0, screen, &new_dest );
        SDL_BlitSurface( trial_surface, 0, screen, &trial_dest );
        SDL_BlitSurface( options_surface, 0, screen, &options_dest );
        SDL_BlitSurface( quit_surface, 0, screen, &quit_dest );
    }
    else if ( page == 2 )
    {
        SDL_BlitSurface( opt_screen_surface, 0, screen, &opt_screen_dest );
        SDL_BlitSurface( opt_resolution_surface, 0, screen, &opt_resolution_dest );
        SDL_BlitSurface( opt_bgd_surface, 0, screen, &opt_bgd_dest );
        SDL_BlitSurface( opt_language_surface, 0, screen, &opt_language_dest );
        SDL_BlitSurface( opt_volume_sound_surface, 0, screen, &opt_volume_sound_dest );
        SDL_BlitSurface( opt_volume_music_surface, 0, screen, &opt_volume_music_dest );
        SDL_BlitSurface( opt_back_surface, 0, screen, &opt_back_dest );

        if ( is_option_restart_warn == true )
            SDL_BlitSurface( restart_warn_surface, 0, screen, &restart_warn_dest );
    }
    else
    {
        SDL_BlitSurface( new_surface, 0, screen, &new_dest );
        SDL_BlitSurface( trial_surface, 0, screen, &trial_dest );
        SDL_BlitSurface( options_surface, 0, screen, &options_dest );
        SDL_BlitSurface( quit_surface, 0, screen, &quit_dest );
    }
}


void MainMenuView:: initOptions()
{
    std::cout << "init: width: " << screen->w << std::endl
    << "init: height: " << screen -> h << std::endl;

    // Constant positions of menu objects surfaces:
    bgd.x = screen->w/4;  //screen->w/1/4;
    bgd.y = screen->h/1/7;

    int HORIZONT = screen->w * 0.27;

    selection_dst.x = screen->w * 0.25;
    selection_dst.y = 480 * 0.29 /*0.7*/;

    if (screen->w == 800)
    {
        bgd.x += 40;
        bgd.y -= 17;

        HORIZONT += 40;

        selection_dst.x += 40;
        selection_dst.y += 17;
    }
    else if (screen->w == 1024)
    {
        bgd.x += 96;
        bgd.y -= 41;

        HORIZONT += 96;

        selection_dst.x += 96;
        selection_dst.y += 41;
    }
    else if (screen->w == 1280)
    {
        bgd.x += 160;
        bgd.y -= 34;

        HORIZONT += 160;

        selection_dst.x += 160;
        selection_dst.y += 34;
    }

    new_dest.x = HORIZONT;
    new_dest.y = screen->h * 0.3;

    trial_dest.x = HORIZONT;
    trial_dest.y = screen->h * 0.4;

    options_dest.x = HORIZONT;
    options_dest.y = screen->h * 0.5;

        opt_screen_dest.x = HORIZONT;
        opt_screen_dest.y = screen->h * 0.3;

        opt_resolution_dest.x = HORIZONT;
        opt_resolution_dest.y = screen->h * 0.38;

        opt_bgd_dest.x = HORIZONT;
        opt_bgd_dest.y = screen->h * 0.46;

        opt_language_dest.x = HORIZONT;
        opt_language_dest.y = screen->h * 0.54;

        opt_volume_sound_dest.x = HORIZONT;
        opt_volume_sound_dest.y = screen->h * 0.62;

        opt_volume_music_dest.x = HORIZONT;
        opt_volume_music_dest.y = screen->h * 0.70;

        opt_back_dest.x = HORIZONT;
        opt_back_dest.y = screen->h * 0.78;

    quit_dest.x = HORIZONT;
    quit_dest.y = screen->h * 0.6;

    if (screen->w == 800)
    {
        new_dest.y -= 36;
        trial_dest.y -= 48;
        options_dest.y -= 60;
        opt_screen_dest.y -= 36;
        opt_resolution_dest.y -= 46;
        opt_bgd_dest.y -= 56;
        opt_language_dest.y -= 65;
        opt_volume_sound_dest.y -= 75;
        opt_volume_music_dest.y -= 84;
        opt_back_dest.y -= 94;
        quit_dest.y -= 72;
    }
    else if (screen->w == 1024)
    {
        new_dest.y -= 86;
        trial_dest.y -= 115;
        options_dest.y -= 144;
        opt_screen_dest.y -= 86;
        opt_resolution_dest.y -= 109;
        opt_bgd_dest.y -= 133;
        opt_language_dest.y -= 155;
        opt_volume_sound_dest.y -= 179;
        opt_volume_music_dest.y -= 201;
        opt_back_dest.y -= 220; //185;
        quit_dest.y -= 172;
    }
    else if (screen->w == 1280)
    {
        new_dest.y -= 72;
        trial_dest.y -= 96;
        options_dest.y -= 120;
        opt_screen_dest.y -= 72;
        opt_resolution_dest.y -= 91;
        opt_bgd_dest.y -= 111;
        opt_language_dest.y -= 129;
        opt_volume_sound_dest.y -= 149;
        opt_volume_music_dest.y -= 168;
        opt_back_dest.y -= 187;
        quit_dest.y -= 144;
    }

    restart_warn_dest.x = screen->w * 0.1;
    restart_warn_dest.y = screen->h * 0.93;

    // Default starting texts of menu objects:
    std:: string language = main_menu -> getLanguage();
    screen_mode_name = main_menu -> getScreenMode();
    resolution_name = main_menu -> getResolution();
    std:: string sound_name = main_menu -> getVolume("sound");
    std:: string music_name = main_menu -> getVolume("music");

    std:: string temp_screen;
    std:: string temp_res;

    if (screen_mode_name == "full")
    {
        if ( language == "pl" )
            temp_screen = "Ekran: Pelny";
        else if (language == "en")
            temp_screen = "Screen: Full";
    }
    else if (screen_mode_name == "window")
    {
        if ( language == "pl" )
            temp_screen = "Ekran: Okno";
        else if (language == "en")
            temp_screen = "Screen: Window";
    }

    if ( resolution_name == "640x480" )
    {
        if ( language == "pl" )
            temp_res = "Rozdzielczosc: 640x480";
        else if ( language == "en" )
            temp_res = "Resolution: 640x480";
    }
    else if ( resolution_name == "800x600" )
    {
        if ( language == "pl" )
            temp_res = "Rozdzielczosc: 800x600";
        else if ( language == "en" )
            temp_res = "Resolution: 800x600";
    }
    else if ( resolution_name == "1024x768" )
    {
        if ( language == "pl" )
            temp_res = "Rozdzielczosc: 1024x768";
        else if ( language == "en" )
            temp_res = "Resolution: 1024x768";
    }
    else if ( resolution_name == "1280x720" )
    {
        if ( language == "pl" )
            temp_res = "Rozdzielczosc: 1280x720";
        else if ( language == "en" )
            temp_res = "Resolution: 1280x720";
    }

    if ( sound_name == "medium" )
    {
        if ( language == "pl" )
        {
            text_opt_volume_sound = "Glosnosc dzwieku: Srednia";

            std::cout << text_opt_volume_sound << std::endl;
        }
        else if ( language == "en" )
            text_opt_volume_sound = "Sound Volume: Medium";
    }
    else if ( sound_name == "high" )
    {
        if ( language == "pl" )
        {
            text_opt_volume_sound = "Glosnosc dzwieku: Wysoka";

            std::cout << text_opt_volume_sound << std::endl;
        }
        else if ( language == "en" )
            text_opt_volume_sound = "Sound Volume: High";
    }
    else if ( sound_name == "very high" )
    {
        if ( language == "pl" )
        {
            text_opt_volume_sound = "Glosnosc dzwieku: B. Wysoka";

            std::cout << text_opt_volume_sound << std::endl;
        }
        else if ( language == "en" )
            text_opt_volume_sound = "Sound Volume: Very High";
    }
    else if ( sound_name == "off" )
    {
        if ( language == "pl" )
        {
            text_opt_volume_sound = "Glosnosc dzwieku: Wyl";

            std::cout << text_opt_volume_sound << std::endl;
        }
        else if ( language == "en" )
            text_opt_volume_sound = "Sound Volume: Off";
    }
    else if ( sound_name == "low" )
    {
        if ( language == "pl" )
        {
            text_opt_volume_sound = "Glosnosc dzwieku: Niska";

            std::cout << text_opt_volume_sound << std::endl;
        }
        else if ( language == "en" )
            text_opt_volume_sound = "Sound Volume: Low";
    }

    if ( music_name == "medium" )
    {
        if ( language == "pl" )
        {
            text_opt_volume_music = "Glosnosc muzyki: Srednia";

            std::cout << text_opt_volume_music << std::endl;
        }
        else if ( language == "en" )
            text_opt_volume_music = "Music Volume: Medium";
    }
    else if ( music_name == "high" )
    {
        if ( language == "pl" )
        {
            text_opt_volume_music = "Glosnosc muzyki: Wysoka";

            std::cout << text_opt_volume_music << std::endl;
        }
        else if ( language == "en" )
            text_opt_volume_music = "Music Volume: High";
    }
    else if ( music_name == "very high" )
    {
        if ( language == "pl" )
        {
            text_opt_volume_music = "Glosnosc muzyki: B. Wysoka";

            std::cout << text_opt_volume_music << std::endl;
        }
        else if ( language == "en" )
            text_opt_volume_music = "Music Volume: Very High";
    }
    else if ( music_name == "off" )
    {
        if ( language == "pl" )
        {
            text_opt_volume_music = "Glosnosc muzyki: Wyl";

            std::cout << text_opt_volume_music << std::endl;
        }
        else if ( language == "en" )
            text_opt_volume_music = "Music Volume: Off";
    }
    else if ( music_name == "low" )
    {
        if ( language == "pl" )
        {
            text_opt_volume_music = "Glosnosc muzyki: Niska";

            std::cout << text_opt_volume_music << std::endl;
        }
        else if ( language == "en" )
            text_opt_volume_music = "Music Volume: Low";
    }


    text_new = "Nowa Gra";
    c_text_new = const_cast<char*>(text_new.c_str());

    text_trial = "Proba czasu";
    c_text_trial = const_cast<char*>(text_trial.c_str());

    text_options = "Opcje";
    c_text_options = const_cast<char*>(text_options.c_str());

        text_opt_screen = temp_screen;
        c_text_opt_screen = const_cast<char*>(text_opt_screen.c_str());

        text_opt_resolution = temp_res;
        c_text_opt_resolution = const_cast<char*>(text_opt_resolution.c_str());

        text_opt_bgd = "Tlo: Tak";
        c_text_opt_bgd = const_cast<char*>(text_opt_bgd.c_str());

        text_opt_language = "Jezyk: Polski";
        c_text_opt_language = const_cast<char*>(text_opt_language.c_str());

        //text_opt_volume_sound = sound_name; /*"Glosnosc dzwieku: Niska";*/
        c_text_opt_volume_sound = const_cast<char*>(text_opt_volume_sound.c_str());

        //text_opt_volume_music = music_name; /*"Glosnosc muzyki: Srednia"*/;
        c_text_opt_volume_music = const_cast<char*>(text_opt_volume_music.c_str());

        text_opt_back = "Powrot";
        c_text_opt_back = const_cast<char*>(text_opt_back.c_str());

    text_quit = "Wyjscie";
    c_text_quit = const_cast<char*>(text_quit.c_str());

    text_restart_warn = "Aby wprowadzic opcje w zycie uruchom ponownie gre.";
    c_text_restart_warn = const_cast<char*>(text_restart_warn.c_str());

    // Generate standard texts to display within menu:
    new_surface = TTF_RenderText_Solid( font, c_text_new, font_color );
    trial_surface = TTF_RenderText_Solid( font, c_text_trial, font_color );
    options_surface = TTF_RenderText_Solid( font, c_text_options, font_color );
        opt_screen_surface = TTF_RenderText_Solid( font, c_text_opt_screen, font_color );
        opt_resolution_surface = TTF_RenderText_Solid( font, c_text_opt_resolution, font_color );
        opt_bgd_surface = TTF_RenderText_Solid( font, c_text_opt_bgd, font_color );
        opt_language_surface = TTF_RenderText_Solid( font, c_text_opt_language, font_color );
        opt_volume_sound_surface = TTF_RenderText_Solid( font, c_text_opt_volume_sound, font_color );
        opt_volume_music_surface = TTF_RenderText_Solid( font, c_text_opt_volume_music, font_color );
        opt_back_surface = TTF_RenderText_Solid( font, c_text_opt_back, font_color );
    quit_surface = TTF_RenderText_Solid( font, c_text_quit, font_color );

    restart_warn_surface = TTF_RenderText_Solid( font_sec, c_text_restart_warn, { 255, 0, 0 } );
}


void MainMenuView:: updateDisplaySelection()
{
    int sel_number = main_menu -> getSelectionNumber();

    if ( page == 1 )
    {
        switch ( sel_number )
        {
            case 1:
                    selection_dst.y = /*screen->h*/ 480 * 0.29;
                    break;

            case 2:
                    selection_dst.y = /*screen->h*/ 480 * 0.39;
                    break;

            case 3:
                    selection_dst.y = /*screen->h*/ 480 * 0.49;
                    break;

            case 4:
                    selection_dst.y = /*screen->h*/ 480 * 0.59;
                    break;

            case 5:
                    selection_dst.y = /*screen->h*/ 480 * 0.69;
                    break;

            case 6:
                    selection_dst.y = /*screen->h*/ 480 * 0.79;
                    break;
        }
    }
    else if (page == 2)
    {
        switch ( sel_number )
        {
            case 1:
                    selection_dst.y = /*screen->h*/ 480 * 0.29;
                    break;

            case 2:
                    selection_dst.y = /*screen->h*/ 480 * 0.37;
                    break;

            case 3:
                    selection_dst.y = /*screen->h*/ 480 * 0.45;
                    break;

            case 4:
                    selection_dst.y = /*screen->h*/ 480 * 0.53;
                    break;

            case 5:
                    selection_dst.y = /*screen->h*/ 480 * 0.61;
                    break;

            case 6:
                    selection_dst.y = /*screen->h*/ 480 * 0.69;
                    break;

            case 7:
                    selection_dst.y = /*screen->h*/ 480 * 0.77;
                    break;
        }
    }
}

void MainMenuView:: updateTexts()
{
    std:: string screen_mode = main_menu -> getScreenMode();
    std:: string resolution = main_menu -> getResolution();
    std:: string background = main_menu -> getBackground();
    std:: string language = main_menu -> getLanguage();
    std:: string volume_sound = main_menu -> getVolume( "sound" );
    std:: string volume_music = main_menu -> getVolume( "music" );

    std:: string changed_text = main_menu -> getChangedText();
    int text_state = main_menu -> getTextState();

    if ( changed_text == "none" )
        return;

    else if ( changed_text == "screen_mode" )
    {
        if ( screen_mode == "window" )
        {
            if ( language == "pl" )
                text_opt_screen = "Ekran: Okno";
            else if ( language == "en" )
                text_opt_screen = "Screen: Window";

            screen_mode_name = "window";
        }
        else if ( screen_mode == "full" )
        {
            if ( language == "pl" )
                text_opt_screen = "Ekran: Pelny";
            else if ( language == "en" )
                text_opt_screen = "Screen: Full";

            screen_mode_name = "full";
        }

        c_text_opt_screen = const_cast<char*>(text_opt_screen.c_str());
        opt_screen_surface = TTF_RenderText_Solid( font, c_text_opt_screen, font_color );

        main_menu -> resetTextState();

    }
    else if ( changed_text == "resolution" )
    {
        std::cout << resolution << std::endl;

        if ( resolution == "640x480" )
        {
            if ( language == "pl" )
                text_opt_resolution = "Rozdzielczosc: 640x480";
            else if ( language == "en" )
                text_opt_resolution = "Resolution: 640x480";

            resolution_name = "800x600";
        }
        if ( resolution == "800x600" )
        {
            if ( language == "pl" )
                text_opt_resolution = "Rozdzielczosc: 800x600";
            else if ( language == "en" )
                text_opt_resolution = "Resolution: 800x600";

            resolution_name = "800x600";
        }
        else if ( resolution == "1024x768" )
        {
            if ( language == "pl" )
                text_opt_resolution = "Rozdzielczosc: 1024x768";
            else if ( language == "en" )
                text_opt_resolution = "Resolution: 1024x768";

            resolution_name = "1024x768";
        }
        else if ( resolution == "1280x720" )
        {
            if ( language == "pl" )
                text_opt_resolution = "Rozdzielczosc: 1280x720";
            else if ( language == "en" )
                text_opt_resolution = "Resolution: 1280x720";

            resolution_name = "1280x720";
        }

        c_text_opt_resolution = const_cast<char*>(text_opt_resolution.c_str());
        opt_resolution_surface = TTF_RenderText_Solid( font, c_text_opt_resolution, font_color );
    }
    else if ( changed_text == "background" )
    {
        if ( background == "no" )
        {
            if ( language == "pl" )
                text_opt_bgd = "Tlo: Nie";
            else if ( language == "en" )
                text_opt_bgd = "Background: No";

            bgd_name = "no";
        }
        else if ( background == "yes" )
        {
            if ( language == "pl" )
                text_opt_bgd = "Tlo: Tak";
            else if ( language == "en" )
                text_opt_bgd = "Background: Yes";

            bgd_name = "yes";
        }

        c_text_opt_bgd = const_cast<char*>(text_opt_bgd.c_str());
        opt_bgd_surface = TTF_RenderText_Solid( font, c_text_opt_bgd, font_color );

        main_menu -> resetTextState();
    }
    else if ( changed_text == "language" )
    {
        if ( language == "en" )
        {
            // if ( language == "pl" )
            //    text_opt_language = "Jezyk: Polski";
            // else if ( language == "en" )
            text_opt_language = "Language: English";
        }
        else if ( language == "pl" )
        {
            //if ( language == "pl" )
            //    text_opt_bgd = "Jezyk: Angielski";
            //else if ( language == "en" )
            //    text_opt_bgd = "Language: Polish";
            text_opt_language = "Jezyk: Polski";
        }

        c_text_opt_language = const_cast<char*>( text_opt_language.c_str() );
        opt_language_surface = TTF_RenderText_Solid( font, c_text_opt_language, font_color );

        main_menu -> resetTextState();
    }
    else if ( changed_text == "volume_sound" )
    {
        if ( volume_sound == "medium" )
        {
            if ( language == "pl" )
            {
                text_opt_volume_sound = "Glosnosc dzwieku: Srednia";

                std::cout << text_opt_volume_sound << std::endl;
            }
            else if ( language == "en" )
                text_opt_volume_sound = "Sound Volume: Medium";
        }
        else if ( volume_sound == "high" )
        {
            if ( language == "pl" )
            {
                text_opt_volume_sound = "Glosnosc dzwieku: Wysoka";

                std::cout << text_opt_volume_sound << std::endl;
            }
            else if ( language == "en" )
                text_opt_volume_sound = "Sound Volume: High";
        }
        else if ( volume_sound == "very high" )
        {
            if ( language == "pl" )
            {
                text_opt_volume_sound = "Glosnosc dzwieku: B. Wysoka";

                std::cout << text_opt_volume_sound << std::endl;
            }
            else if ( language == "en" )
                text_opt_volume_sound = "Sound Volume: Very High";
        }
        else if ( volume_sound == "off" )
        {
            if ( language == "pl" )
            {
                text_opt_volume_sound = "Glosnosc dzwieku: Wyl";

                std::cout << text_opt_volume_sound << std::endl;
            }
            else if ( language == "en" )
                text_opt_volume_sound = "Sound Volume: Off";
        }
        else if ( volume_sound == "low" )
        {
            if ( language == "pl" )
            {
                text_opt_volume_sound = "Glosnosc dzwieku: Niska";

                std::cout << text_opt_volume_sound << std::endl;
            }
            else if ( language == "en" )
                text_opt_volume_sound = "Sound Volume: Low";
        }

        c_text_opt_volume_sound = const_cast<char*>( text_opt_volume_sound.c_str() );
        opt_volume_sound_surface = TTF_RenderText_Solid( font, c_text_opt_volume_sound, font_color );

        main_menu -> resetTextState();
    }
    else if ( changed_text == "volume_music" )
    {
        if ( volume_music == "medium" )
        {
            if ( language == "pl" )
            {
                text_opt_volume_music = "Glosnosc muzyki: Srednia";

                std::cout << text_opt_volume_music << std::endl;
            }
            else if ( language == "en" )
                text_opt_volume_music = "Music Volume: Medium";
        }
        else if ( volume_music == "high" )
        {
            if ( language == "pl" )
            {
                text_opt_volume_music = "Glosnosc muzyki: Wysoka";

                std::cout << text_opt_volume_music << std::endl;
            }
            else if ( language == "en" )
                text_opt_volume_music = "Music Volume: High";
        }
        else if ( volume_music == "very high" )
        {
            if ( language == "pl" )
            {
                text_opt_volume_music = "Glosnosc muzyki: B. Wysoka";

                std::cout << text_opt_volume_music << std::endl;
            }
            else if ( language == "en" )
                text_opt_volume_music = "Music Volume: Very High";
        }
        else if ( volume_music == "off" )
        {
            if ( language == "pl" )
            {
                text_opt_volume_music = "Glosnosc muzyki: Wyl";

                std::cout << text_opt_volume_music << std::endl;
            }
            else if ( language == "en" )
                text_opt_volume_music = "Music Volume: Off";
        }
        else if ( volume_music == "low" )
        {
            if ( language == "pl" )
            {
                text_opt_volume_music = "Glosnosc muzyki: Niska";

                std::cout << text_opt_volume_music << std::endl;
            }
            else if ( language == "en" )
                text_opt_volume_music = "Music Volume: Low";
        }

        c_text_opt_volume_music = const_cast<char*>( text_opt_volume_music.c_str() );
        opt_volume_music_surface = TTF_RenderText_Solid( font, c_text_opt_volume_music, font_color );

        main_menu -> resetTextState();
    }
    else
        return;
}

std:: string MainMenuView:: getScreenModeName()
{
    //std:: string temp = screen_mode_name;
    //screen_mode_name = "none";

    //return temp;
    return screen_mode_name;
}

std::string MainMenuView:: getBgdName()
{
    //std:: string temp = bgd_name;
    //bgd_name = "none";

    //return bgd_name;
    return bgd_name;
}
