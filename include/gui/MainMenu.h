#ifndef MAINMENU_H
#define MAINMENU_H

#include <iostream>
#include <cstdlib>
#include <string>

#include "tools/rapidxml.hpp"
#include "tools/rapidxml_utils.hpp"
#include "tools/rapidxml_print.hpp"

#include "controllers/ResManager.h"

#include "rules/GameState.h"

#include "Constants/MenuTexts.h"

class MainMenu
{
public:
    MainMenu();
    virtual ~MainMenu();

    bool isOptionToChange();

    bool nextStep();
    void setSelection(int selection);
    void moveSelection(const std::string& dest);

    int getSelectionNumber();
    int getPageNumber();
    std::string getScreenMode();
    std::string getResolution();
    std::string getBackground();
    std::string getLanguage();
    std::string getVolume(const std::string& which);
    std::string getChangedText();

    void resetChangedText();

    bool isOptionRestartWarn();

    void resetTextState();

    bool getExitState();

    void readOptionsFromXML();
    void saveOptionToXML(std::string option, std::string value) const;

    void resetOptionRestartWarn();

private:
    static int selection;
    static int page;

    static std::string screen_mode;
    static std::string resolution;
    static std::string background;
    static std::string language;
    static std::string volume_sound;
    static std::string volume_music;
    static std::string changed_text;
    static int text_state;

    static bool is_option_restart_warn;
    static bool have_exit;

    static const char* config_file_path;
};

#endif // MAINMENU_H
