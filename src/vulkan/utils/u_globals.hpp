#pragma once
#include <string>
#include <vector>
#include <vulkan/vulkan.h>

namespace globals{

    enum Setting { // OPTIONS
        Version,
        EngineVersion,
        WindowWidth,
        WindowHeight,
        SettingsNbr // NOMBRE D'OPTIONS
    };

    // CES VALEURS SONT CELLES PAR DEFAUT, ELLES SONT DONC AMENEES A CHANGER A L'INITIALISATION
    extern std::string settings[SettingsNbr];

    extern std::vector<const char*> layers;

    extern std::vector<const char*> instanceEXT;

}