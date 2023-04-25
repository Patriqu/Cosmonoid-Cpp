#pragma once
#include <list>
#include <map>
#include <string>

inline struct MenuTexts {
    std::map<std::string, std::map<std::string, std::string>> baseTexts =
        {
            {
            "screen_mode", {
                {"en", "Screen: "},
                {"pl", "Ekran: "} }
            },
            {
            "resolution", {
                {"en", "Resolution: "},
                {"pl", "Rozdzielczosc: "} }
            },
            {
            "background", {
                {"en", "Background: "},
                {"pl", "Tlo: "} }
            },
            {
            "language", {
                {"en", "Language: "},
                {"pl", "Jezyk: "} }
            },
            {
            "volume_sound", {
                {"en", "Sound volume: "},
                {"pl", "Glosnosc dzwieku: "} }
            },
            {
            "volume_music", {
                {"en", "Music volume: "},
                {"pl", "Glosnosc muzyki: "} }
            }
        };

    std::map<std::string, std::list<std::string>> values =
        {
            { "screen_mode", {"window", "full"} },
            { "resolution", {"640x480", "800x600", "1024x768", "1280x720"} },
            { "background", {"yes", "no"} },
            { "language", {"en", "pl"} },
            { "volume_sound", {"off", "low", "medium", "high", "very high"} },
            { "volume_music", {"off", "low", "medium", "high", "very high"} }
        };

    std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> mappings =
        {
            {
                "screen_mode", {
                    {"window", {{"en", "Window"}, {"pl", "Okno"}}},
                    {"full", {{"en", "Full"}, {"pl", "Pelny"}}} }
            },
            {
                "resolution", {
                   {"640x480", {{"en", "640x480"}, {"pl", "640x480"}}},
                   {"800x600", {{"en", "800x600"}, {"pl", "800x600"}}},
                  {"1024x768", {{"en", "1024x768"}, {"pl", "1024x768"}}},
                  {"1280x720", {{"en", "1280x720"}, {"pl", "1280x720"}}} }
            },
            {
                "background", {
                {
                    "yes", {{"en", "yes"},
                            {"pl", "tak"}}
                },
                {
                    "no", {{"en", "no"},
                           {"pl", "nie"}}
                } }
            },
            {
                "language",
                {
                        {
                                "en", {{"en", "English"},
                                              {"pl", "Angielski"}}
                        },
                        {
                                "pl", {{"en", "Polish"},
                                              {"pl", "Polski"}}
                        } }
            },
            {
                "volume_sound",
                {
                        {
                                "off", {{"en", "off"},
                                               {"pl", "wyl"}}
                        },
                        {
                                "low", {{"en", "low"},
                                               {"pl", "niska"}}
                        },
                        {
                                "medium", {{"en", "medium"},
                                                  {"pl", "srednia"}}
                        },
                        {
                                "high", {{"en", "high"},
                                                {"pl", "wysoka"}}
                        },
                        {
                                "very high", {{"en", "very high"},
                                                     {"pl", "b. wysoka"}}
                        }
                }
            },
            {
                "volume_music",
                {
                        {
                                "off", {{"en", "off"},
                                               {"pl", "wyl"}}
                        },
                        {
                                "low", {{"en", "low"},
                                               {"pl", "niska"}}
                        },
                        {
                                "medium", {{"en", "medium"},
                                                  {"pl", "srednia"}}
                        },
                        {
                                "high", {{"en", "high"},
                                                {"pl", "wysoka"}}
                        },
                        {
                                "very high", {{"en", "very high"},
                                                     {"pl", "b. wysoka"}}
                        }
                }
            }
        };
} menu_texts_new;