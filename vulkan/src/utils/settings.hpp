#pragma once

#include <string>

namespace utils {
    
    enum Setting {
        Version,
        EngineVersion,
        WindowWidth,
        WindowHeight,
        SettingsNbr
    };

    extern std::string settingsValues[SettingsNbr];

    bool isOnLength(std::string str, int p_length);

    bool isOnSize(std::string str, int p_size);

    extern bool(* verifFuncs[2])(std::string, int);

    void loadSettings();

}