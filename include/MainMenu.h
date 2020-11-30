#ifndef MAINMENU_H
#define MAINMENU_H

#include <iostream>
#include <cstdlib>
#include <string>

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

#include "ResManager.h"

#include "GameState.h"

class MainMenu
{
    public:
        MainMenu();
        virtual ~MainMenu();

        bool isOptionToChange();

        bool nextStep();
        void setSelection( int selection );
        void moveSelection( std:: string dest );

        int getSelectionNumber();
        int getPageNumber();
        std:: string getScreenMode();
        std:: string getResolution();
        std:: string getBackground();
        std:: string getLanguage();
        std:: string getVolume( std::string which );
        std:: string getChangedText();
        bool isOptionRestartWarn();
        int getTextState();
        void resetTextState();

        bool getExitState();

        void readOptionsFromXML();
        void saveOptionToXML( std:: string option, const char* value ) const;

        void clearChangedText();
        void resetOptionRestartWarn();

    private:
        static int selection;
        static int page;

        static const char* screen_mode;
        static const char* resolution;
        static const char* background;
        static const char* language;
        static const char* volume_sound;
        static const char* volume_music;
        static const char* changed_text;
        static int text_state;

        static bool is_option_restart_warn;
        static bool have_exit;

        static const char* config_file_path;
};

#endif // MAINMENU_H
