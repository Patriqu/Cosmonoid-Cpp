#pragma once
#include <list>
#include <map>
#include <string>

inline struct MenuTexts
{
    std::map<std::string, std::string> screen_mode_base_text =
    {
        {"en", "Screen: "},
        {"pl", "Ekran: "}
    };
    std::map<std::string, std::string> resolution_base_text =
    {
        {"en", "Resolution: "},
        {"pl", "Rozdzielczosc: "}
    };
    std::map<std::string, std::string> background_base_text =
    {
        {"en", "Background: "},
        {"pl", "Tlo: "}
    };
    std::map<std::string, std::string> language_base_text =
    {
        {"en", "Language: "},
        {"pl", "Jezyk: "}
    };
    std::map<std::string, std::string> volume_sound_base_text
        =
        {
            {"en", "Sound volume: "},
            {"pl", "Glosnosc dzwieku: "}
        };
    std::map<std::string, std::string> volume_music_base_text
        =
        {
            {"en", "Music volume: "},
            {"pl", "Glosnosc muzyki: "}
        };

    std::list<std::string> screen_mode_values
        =
        {
            "window",
            "full"
        };
    std::list<std::string> resolution_values
        =
        {
            "640x480",
            "800x600",
            "1024x768",
            "1280x720"
        };
    std::list<std::string> background_values
        =
        {
            "yes",
            "no"
        };
    std::list<std::string> language_values
        =
        {
            "en",
            "pl"
        };
    std::list<std::string> volume_values
        =
        {
            "off",
            "low",
            "medium",
            "high",
            "very high"
        };

    std::map<std::string, std::map<std::string, std::string>> screen_mode_mapping
        =
        {
            {"window", {{"en", "Window"}, {"pl", "Okno"}}},
            {"full", {{"en", "Full"}, {"pl", "Pelny"}}}
        };
    std::map<std::string, std::map<std::string, std::string>> background_mapping
        =
        {
            {"yes", {{"en", "yes"}, {"pl", "tak"}}},
            {"no", {{"en", "no"}, {"pl", "nie"}}}
        };
    std::map<std::string, std::map<std::string, std::string>> language_mapping
        =
        {
            {"en", {{"en", "English"}, {"pl", "Angielski"}}},
            {"pl", {{"en", "Polish"}, {"pl", "Polski"}}}
        };
    std::map<std::string, std::map<std::string, std::string>> volume_value_mapping
        =
        {
            {"off", {{"en", "off"}, {"pl", "wyl"}}},
            {"low", {{"en", "low"}, {"pl", "niska"}}},
            {"medium", {{"en", "medium"}, {"pl", "srednia"}}},
            {"high", {{"en", "high"}, {"pl", "wysoka"}}},
            {"very high", {{"en", "very high"}, {"pl", "b. wysoka"}}}
        };
} menu_texts;
