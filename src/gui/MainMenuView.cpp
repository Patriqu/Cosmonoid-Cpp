#include "gui/MainMenuView.h"
#include "Constants/MenuTexts.h"

MainMenuView::MainMenuView()
    : screen_mode_name("none"),
      resolution_name("640x480"),
      bgd_name("yes"),
      screen(SDL_GetWindowSurface(SDL_GetWindowFromID(1))),
      main_menu(new MainMenu()),
      font(TTF_OpenFont("arialbd.ttf", 20)),
      font_sec(TTF_OpenFont("arialbd.ttf", 13)),
      font_color({0, 0, 0}),

      new_surface(nullptr),
      trial_surface(nullptr),
      options_surface(nullptr),
      opt_screen_surface(nullptr),
      opt_resolution_surface(nullptr),
      opt_bgd_surface(nullptr),
      opt_language_surface(nullptr),
      opt_volume_sound_surface(nullptr),
      opt_volume_music_surface(nullptr),
      opt_back_surface(nullptr),
      quit_surface(nullptr),

      restart_warn_surface(nullptr),

      text_new(new char[16]),
      text_trial(new char[16]),
      text_options(new char[16]),
      text_opt_screen(new char[16]),
      text_opt_resolution(new char[16]),
      text_opt_bgd(new char[16]),
      text_opt_language(new char[16]),
      text_opt_volume_sound(new char[16]),
      text_opt_volume_music(new char[16]),
      text_opt_back(new char[16]),
      text_quit(new char[16]),

      text_restart_warn(new char[16]),

      page(1)
{
    initOptions();
}

MainMenuView::~MainMenuView()
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

    TTF_CloseFont(font);
}

void MainMenuView::renderMenu()
{
    SDL_BlitSurface(ResManager::getInstance().getImage("menu"), 0, screen, &bgd);

    updateDisplaySelection();

    SDL_BlitSurface(ResManager::getInstance().getImage("selection"), 0, screen, &selection_dst);

    updateTexts();
    renderTexts();
}

void MainMenuView::renderTexts()
{
    page = main_menu->getPageNumber();
    const bool is_option_restart_warn = main_menu->isOptionRestartWarn();

    if (page == 1)
    {
        if (is_option_restart_warn)
            main_menu->resetOptionRestartWarn();

        SDL_BlitSurface(new_surface, 0, screen, &new_dest);
        SDL_BlitSurface(trial_surface, 0, screen, &trial_dest);
        SDL_BlitSurface(options_surface, 0, screen, &options_dest);
        SDL_BlitSurface(quit_surface, 0, screen, &quit_dest);
    }
    else if (page == 2)
    {
        SDL_BlitSurface(opt_screen_surface, 0, screen, &opt_screen_dest);
        SDL_BlitSurface(opt_resolution_surface, 0, screen, &opt_resolution_dest);
        SDL_BlitSurface(opt_bgd_surface, 0, screen, &opt_bgd_dest);
        SDL_BlitSurface(opt_language_surface, 0, screen, &opt_language_dest);
        SDL_BlitSurface(opt_volume_sound_surface, 0, screen, &opt_volume_sound_dest);
        SDL_BlitSurface(opt_volume_music_surface, 0, screen, &opt_volume_music_dest);
        SDL_BlitSurface(opt_back_surface, 0, screen, &opt_back_dest);

        if (is_option_restart_warn)
            SDL_BlitSurface(restart_warn_surface, 0, screen, &restart_warn_dest);
    }
    else
    {
        SDL_BlitSurface(new_surface, 0, screen, &new_dest);
        SDL_BlitSurface(trial_surface, 0, screen, &trial_dest);
        SDL_BlitSurface(options_surface, 0, screen, &options_dest);
        SDL_BlitSurface(quit_surface, 0, screen, &quit_dest);
    }
}

void MainMenuView::initOptions()
{
    std::cout << "init: width: " << screen->w << std::endl
        << "init: height: " << screen->h << std::endl;

    // Constant positions of menu objects surfaces:
    bgd.x = screen->w / 4;
    bgd.y = screen->h / 1 / 7;

    int HORIZONT = screen->w * 0.27;

    selection_dst.x = screen->w * 0.25;
    selection_dst.y = 480 * 0.29;

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
    const std::string language = main_menu->getLanguage();
    screen_mode_name = main_menu->getScreenMode();
    resolution_name = main_menu->getResolution();
    bgd_name = main_menu->getBackground();
    std::string sound_name = main_menu->getVolume("sound");
    std::string music_name = main_menu->getVolume("music");

    // menu item texts
    background_iterator = menu_texts_new.values["background"].begin();
    language_iterator = menu_texts_new.values["language"].begin();

    screen_mode_iterator = std::find(menu_texts_new.values["screen_mode"].begin(), menu_texts_new.values["screen_mode"].end(),
                                     screen_mode_name);
    const std::string temp_screen = menu_texts_new.baseTexts["screen_mode"][language]
            + menu_texts_new.mappings["screen_mode"][*screen_mode_iterator][language];
    std::cout << temp_screen << std::endl;

    resolution_iterator = std::find(menu_texts_new.values["resolution"].begin(), menu_texts_new.values["resolution"].end(),
                                    resolution_name);
    const std::string temp_res = menu_texts_new.baseTexts["resolution"][language] + *resolution_iterator;
    std::cout << temp_res << std::endl;

    background_iterator = std::find(menu_texts_new.values["background"].begin(),
                                    menu_texts_new.values["background"].end(), bgd_name);
    const std::string temp_background = menu_texts_new.baseTexts["background"][language]
            + menu_texts_new.mappings["background"][*background_iterator][language];
    std::cout << temp_background << std::endl;

    language_iterator = std::find(menu_texts_new.values["language"].begin(), menu_texts_new.values["language"].end(), language);
    const std::string temp_language = menu_texts_new.baseTexts["language"][language]
            + menu_texts_new.mappings["language"][*language_iterator][language];
    std::cout << temp_language << std::endl;

    volume_sound_iterator = std::find(menu_texts_new.values["volume_sound"].begin(), menu_texts_new.values["volume_sound"].end(), sound_name);
    text_opt_volume_sound = menu_texts_new.baseTexts["volume_sound"][language]
            + menu_texts_new.mappings["volume_sound"][*volume_sound_iterator][language];
    std::cout << text_opt_volume_sound << std::endl;

    volume_music_iterator = std::find(menu_texts_new.values["volume_music"].begin(), menu_texts_new.values["volume_music"].end(), music_name);
    text_opt_volume_music = menu_texts_new.baseTexts["volume_music"][language]
            + menu_texts_new.mappings["volume_music"][*volume_music_iterator][language];
    std::cout << text_opt_volume_music << std::endl;

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

    text_opt_bgd = temp_background;
    c_text_opt_bgd = const_cast<char*>(text_opt_bgd.c_str());

    text_opt_language = temp_language;
    c_text_opt_language = const_cast<char*>(text_opt_language.c_str());

    c_text_opt_volume_sound = const_cast<char*>(text_opt_volume_sound.c_str());

    c_text_opt_volume_music = const_cast<char*>(text_opt_volume_music.c_str());

    text_opt_back = "Powrot";
    c_text_opt_back = const_cast<char*>(text_opt_back.c_str());

    text_quit = "Wyjscie";
    c_text_quit = const_cast<char*>(text_quit.c_str());

    text_restart_warn = "Aby wprowadzic opcje w zycie uruchom ponownie gre.";
    c_text_restart_warn = const_cast<char*>(text_restart_warn.c_str());

    // Generate standard texts to display within menu:
    new_surface = TTF_RenderText_Solid(font, c_text_new, font_color);
    trial_surface = TTF_RenderText_Solid(font, c_text_trial, font_color);
    options_surface = TTF_RenderText_Solid(font, c_text_options, font_color);
    opt_screen_surface = TTF_RenderText_Solid(font, c_text_opt_screen, font_color);
    opt_resolution_surface = TTF_RenderText_Solid(font, c_text_opt_resolution, font_color);
    opt_bgd_surface = TTF_RenderText_Solid(font, c_text_opt_bgd, font_color);
    opt_language_surface = TTF_RenderText_Solid(font, c_text_opt_language, font_color);
    opt_volume_sound_surface = TTF_RenderText_Solid(font, c_text_opt_volume_sound, font_color);
    opt_volume_music_surface = TTF_RenderText_Solid(font, c_text_opt_volume_music, font_color);
    opt_back_surface = TTF_RenderText_Solid(font, c_text_opt_back, font_color);
    quit_surface = TTF_RenderText_Solid(font, c_text_quit, font_color);

    restart_warn_surface = TTF_RenderText_Solid(font_sec, c_text_restart_warn, {255, 0, 0});
}

void MainMenuView::updateDisplaySelection()
{
    const int sel_number = main_menu->getSelectionNumber();

    if (page == 1)
    {
        switch (sel_number)
        {
        case 1:
            selection_dst.y = 480 * 0.29;
            break;

        case 2:
            selection_dst.y = 480 * 0.39;
            break;

        case 3:
            selection_dst.y = 480 * 0.49;
            break;

        case 4:
            selection_dst.y = 480 * 0.59;
            break;

        case 5:
            selection_dst.y = 480 * 0.69;
            break;

        case 6:
            selection_dst.y = 480 * 0.79;
            break;
        }
    }
    else if (page == 2)
    {
        switch (sel_number)
        {
        case 1:
            selection_dst.y = 480 * 0.29;
            break;

        case 2:
            selection_dst.y = 480 * 0.37;
            break;

        case 3:
            selection_dst.y = 480 * 0.45;
            break;

        case 4:
            selection_dst.y = 480 * 0.53;
            break;

        case 5:
            selection_dst.y = 480 * 0.61;
            break;

        case 6:
            selection_dst.y = 480 * 0.69;
            break;

        case 7:
            selection_dst.y = 480 * 0.77;
            break;
        }
    }
}

void MainMenuView::updateTexts()
{
    const std::string screen_mode = main_menu->getScreenMode();
    const std::string resolution = main_menu->getResolution();
    const std::string background = main_menu->getBackground();
    const std::string language = main_menu->getLanguage();
    const std::string volume_sound = main_menu->getVolume("sound");
    const std::string volume_music = main_menu->getVolume("music");

    const std::string changed_text = main_menu->getChangedText();

    if (changed_text == "none")
        return;

    if (changed_text == "screen_mode")
    {
        opt_screen_surface = updateText(changed_text, screen_mode_iterator, text_opt_screen, c_text_opt_screen, language);
    }
    else if (changed_text == "resolution")
    {
        opt_resolution_surface = updateText(changed_text, resolution_iterator, text_opt_resolution, c_text_opt_resolution, language);
    }
    else if (changed_text == "background")
    {
        opt_bgd_surface = updateText(changed_text, background_iterator, text_opt_bgd, c_text_opt_bgd, language);
    }
    else if (changed_text == "language")
    {
        opt_language_surface = updateText(changed_text, language_iterator, text_opt_language, c_text_opt_language, language);
    }
    else if (changed_text == "volume_sound")
    {
        opt_volume_sound_surface = updateText(changed_text, volume_sound_iterator, text_opt_volume_sound, c_text_opt_volume_sound, language);
    }
    else if (changed_text == "volume_music")
    {
        opt_volume_music_surface = updateText(changed_text, volume_music_iterator, text_opt_volume_music, c_text_opt_volume_music, language);
    }

    main_menu->resetTextState();
    main_menu->resetChangedText();
}

SDL_Surface* MainMenuView::updateText(const std::string& changed_text, std::list<std::string>::iterator& iterator,
                              std::string& text_opt, const char *c_text_opt, const std::string& language) {
    iterateMenuItemIfNeeded(changed_text, iterator);

    const std::string val = *iterator;

    return this->changeToNextOption(text_opt, c_text_opt, val, language, changed_text);
}

void MainMenuView::iterateMenuItemIfNeeded(const std::string& item, std::list<std::string>::iterator& iterator) {
    if (++iterator == menu_texts_new.values[item].end())
        iterator = menu_texts_new.values[item].begin();
}

SDL_Surface * MainMenuView::changeToNextOption(std::string &text, const char *c_text, const std::string &value,
                                               const std::string &language, const std::string &option)
{
    text = menu_texts_new.baseTexts[option][language] + menu_texts_new.mappings[option][value][language];

    c_text = (text.c_str());
    return TTF_RenderText_Solid( font, c_text, font_color );
}

std::string MainMenuView::getBgdName()
{
    return *background_iterator;
}