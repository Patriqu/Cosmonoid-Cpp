#include "MainMenu.h"

int MainMenu:: selection = 1;
int MainMenu:: page = 1;
const char* MainMenu:: screen_mode = "none";
const char* MainMenu:: resolution = "640x480";
const char* MainMenu:: background = "yes";
const char* MainMenu:: language = "pl";
const char* MainMenu:: volume_sound = "low";
const char* MainMenu:: volume_music = "medium";
const char* MainMenu:: changed_text = "none";
int MainMenu:: text_state = 1;
bool MainMenu:: is_option_restart_warn = false;
bool MainMenu:: have_exit = false;

const char* MainMenu:: config_file_path = "config/config.xml";

MainMenu:: MainMenu()
{
    readOptionsFromXML();
}

MainMenu:: ~MainMenu()
{

}

bool MainMenu:: isOptionToChange()
{
    if ( changed_text != "none" )
        return true;

    return false;
}

bool MainMenu:: nextStep()
{
    // NEW GAME
    if ( page == 1 )
    {
        if ( selection == 1 )
        {
            return true;
        }
        // OPTIONS
        else if ( selection == 3 )
        {
            page = 2;
            selection = 1;
        }
        // EXIT GAME
        else if ( selection == 4 )
        {
            have_exit = true;
        }
    }
    else if ( page == 2 )
    {
        if ( selection == 1 )
        {
            changed_text = "screen_mode";

            if ( screen_mode == "window" || screen_mode == "none" )
                screen_mode = "full";
            else if ( screen_mode == "full" )
                screen_mode = "window";

            saveOptionToXML(changed_text, screen_mode);

            is_option_restart_warn = true;
        }
        else if ( selection == 2 )
        {
            changed_text = "resolution";

            if ( resolution == "640x480" )
            {
                resolution = "800x600";
            }
            else if ( resolution == "800x600" )
                resolution = "1024x768";
            else if ( resolution == "1024x768" )
                resolution = "1280x720";
            else if ( resolution == "1280x720" )
                resolution = "640x480";

            saveOptionToXML(changed_text, resolution);

            is_option_restart_warn = true;
        }
        else if ( selection == 3 )
        {
            changed_text = "background";

            if ( background == "yes" )
                background = "no";
            else if ( background == "no" )
                background = "yes";

        }
        else if ( selection == 4 )
        {
            changed_text = "language";

            if ( language == "pl" )
                language = "en";
            else if ( language == "en" )
                language = "pl";
        }
        else if ( selection == 5 )
        {
            changed_text = "volume_sound";

            if ( volume_sound == "off" )
                volume_sound = "low";
            else if ( volume_sound == "low" )
                volume_sound = "medium";
            else if ( volume_sound == "medium" )
                volume_sound = "high";
            else if ( volume_sound == "high" )
                volume_sound = "very high";
            else if ( volume_sound == "very high" )
                volume_sound = "off";

            saveOptionToXML(changed_text, volume_sound);
        }
        else if ( selection == 6 )
        {
            changed_text = "volume_music";

            if ( volume_music == "off" )
                volume_music = "low";
            else if ( volume_music == "low" )
                volume_music = "medium";
            else if ( volume_music == "medium" )
                volume_music = "high";
            else if ( volume_music == "high" )
                volume_music = "very high";
            else if ( volume_music == "very high" )
                volume_music = "off";

            saveOptionToXML(changed_text, volume_music);
        }

        // OPTIONS > BACK
        else if ( selection == 7 )
        {
            page = 1;
            selection = 1;
        }
    }
    else
        return false;

    return false;
}

int MainMenu:: getSelectionNumber()
{
    return selection;
}

int MainMenu:: getPageNumber()
{
    return page;
}

std:: string MainMenu:: getChangedText()
{
    return changed_text;
}

int MainMenu:: getTextState()
{
    return text_state;
}

void MainMenu:: resetTextState()
{
    text_state = 1;
}

std:: string MainMenu:: getScreenMode()
{
    //std:: string mode = screen_mode;
    //screen_mode = "none";

    //return mode;
    return screen_mode;
}

std:: string MainMenu:: getResolution()
{
    return resolution;
}

std:: string MainMenu:: getBackground()
{
    return background;
}

std:: string MainMenu:: getLanguage()
{
    return language;
}

std:: string MainMenu:: getVolume( std::string which )
{
    if ( which == "music" )
    {
        return volume_music;
    }
    else if ( which == "sound" )
    {
        return volume_sound;
    }

    return "error";
}

bool MainMenu:: isOptionRestartWarn()
{
    return is_option_restart_warn;
}

void MainMenu:: setSelection( int selection )
{
    this->selection = selection;
}

void MainMenu:: moveSelection( std:: string dest )
{
    if ( dest == "up" )
    {
        selection -= 1;

        if ( page == 1 && selection == 0 )
            selection = 4;
        else if ( page == 2 && selection == 0 )
            selection = 7;
    }
    else if ( dest == "down" )
    {
        selection += 1;

        if ( (page == 1 && selection == 5) || (page == 2 && selection == 8) )
            selection = 1;
    }
    else
        selection += 0;
}

bool MainMenu:: getExitState()
{
    return have_exit;
}

void MainMenu:: readOptionsFromXML()
{
    rapidxml::file<> xmlFile(config_file_path);

    rapidxml::xml_document <> document;
    try {
        document.parse < rapidxml::parse_no_data_nodes >( xmlFile.data() );
    } catch( rapidxml::parse_error p ) {
        p.what();
    }

    rapidxml::xml_node <> * root = document.first_node("arkanoid");
    root = root->first_node("config");
    root = root->first_node("display");
    root = root->first_node("fullscreen");

    const char* s = root->value();

    if (s == "true")
        screen_mode = "full";
    else if (s == "false")
        screen_mode = "window";

    root = root->next_sibling("width");
    char* w(root->value());

    root = root->next_sibling("height");
    const char* h(root->value());

    //resolution = w + "x" + h;
    char buf[100];
    const char* x = "x";

    // TODO: Convert to strcpy_s and strcat_s
    strcpy(buf, w);
    strcat(buf, x);
    strcat(buf, h);

    /*strcat_s(buf, 2, x);
    strcat_s(buf, 2, h);*/
    
    /*strcat_s(w, 2, x);
    strcat_s(w, 2, h);*/

    root = document.first_node("arkanoid");
    root = root->first_node("config");
    root = root->first_node("sound");

    root = root->first_node("sound_volume");
    const char* sv(root->value());

    root = root->next_sibling("music_volume");
    const char* mv(root->value());

    volume_sound = sv;
    volume_music = mv;

    document.clear();
}

void MainMenu:: saveOptionToXML( std:: string option, const char* value ) const
{
    rapidxml::file<> xmlFile(config_file_path);

    rapidxml::xml_document <> document;
    try {
        document.parse < rapidxml::parse_no_data_nodes >( xmlFile.data() );
    } catch( rapidxml::parse_error p ) {
        p.what();
    }

    rapidxml::xml_node <> * root = document.first_node("arkanoid");

    if (option == "screen_mode")
    {
        root = root->first_node("config");
        root = root->first_node("display");

        if (value == "full")
            root->first_node("fullscreen")->value("true");
        else if (value == "window")
            root->first_node("fullscreen")->value("false");
    }
    else if (option == "resolution")
    {
        const char* w = "";
        const char* h = "";

        root = root->first_node("config");
        root = root->first_node("display");
        root = root->first_node("fullscreen");

        if (value == "640x480")
        {
            w = "640";
            h = "480";
        }
        else if (value == "800x600")
        {
            w = "800";
            h = "600";
        }
        else if (value == "1024x768")
        {
            w = "1024";
            h = "768";
        }
        else if (value == "1280x720")
        {
            w = "1280";
            h = "720";
        }

        root->next_sibling("width")->value(w);
        root->next_sibling("height")->value(h);
    }
    else if (option == "volume_sound")
    {
        root = root->first_node("config");
        root = root->first_node("sound");

        /*
        const char* sv = "";

        if (value == "off")
        {
            sv = "off";
        }
        else if (value == "low")
        {
            sv = "low";
        }
        else if (value == "medium")
        {
            sv = "medium";
        }
        else if (value == "high")
        {
            sv = "high";
        }
        else if (value == "very high")
        {
            sv = "very high";
        }*/

        root->first_node("sound_volume")->value(value);
    }
    else if (option == "volume_music")
    {
        root = root->first_node("config");
        root = root->first_node("sound");

        /*
        const char* mv = "";

        if (value == "off")
        {
            mv = "off";
        }
        else if (value == "low")
        {
            mv = "low";
        }
        else if (value == "medium")
        {
            mv = "medium";
        }
        else if (value == "high")
        {
            mv = "high";
        }
        else if (value == "very high")
        {
            mv = "very high";
        }*/

        root->first_node("music_volume")->value(value);
    }

    std::ofstream file(config_file_path);
    std::string s;
    rapidxml::print(back_inserter(s), document, 0);
    file << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << std::endl;
    file << s;
    file.close();

    document.clear();
}

void MainMenu:: clearChangedText()
{
    changed_text = "none";
}

void MainMenu:: resetOptionRestartWarn()
{
    is_option_restart_warn = false;
}
