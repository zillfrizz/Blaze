#include <array>
#include <fstream>
#include <limits>

#include "settings.hpp"

namespace utils {

    std::string settingsValues[SettingsNbr] = { // Options chargés, avec noms + valeurs par défaut
        "0.0.0",
        "0.0.0",
        "800",
        "600"
    };

    bool isOnLength(std::string str, int p_length){ return str.length() <= p_length; }

    bool isOnSize(std::string str, int p_size){ return std::stoi(str) <= p_size; }

    bool (* verifFuncs[])(std::string, int) = { isOnLength, isOnSize };

    void loadSettings(){

        std::array<std::pair<bool, int>, SettingsNbr> settingsStruct = {{ // structure des options (bool isInt, int tailleMax)
            {false, 5}, // version
            {false, 5}, // engineVersion
            {true, std::numeric_limits<unsigned short>::max()}, // windowWidth
            {true, std::numeric_limits<unsigned short>::max()}, // windowHeight
        }};

        std::string settingsTemp[SettingsNbr] = {// Tableau temporaire contenant le contenu du fichier, les keys par défaut;
            "version",
            "engineVersion",
            "windowWidth",
            "windowHeight"
        };

        std::ofstream create(".settings/settings.txt", std::ios::app);
        create.close();

        std::ifstream reader(".settings/settings.txt", std::ios::in | std::ios::ate);
        int i = 0;
        std::string line;
        while(std::getline(reader, line) && i < SettingsNbr){          
                for(int j = 0; j < line.length() ; j++){
                    if(line[j] == ' '){
                        if(line.substr(0, j) == settingsTemp[i]){             
                            if (!verifFuncs[settingsStruct[i].first](line.substr(j), settingsStruct[i].second)){ // Si la valeur est incorrecte
                                settingsTemp[i] = settingsTemp[i] + " " + settingsValues[i];
                            }
                            else{ settingsTemp[i] = line;}
                            i++; 
                        }
                    }
                }
        }

        for(int j = i; j < SettingsNbr; j++){
            settingsTemp[j] = settingsTemp[j] + " " + settingsValues[j];
        }

        reader.close();

        std::ofstream writer(".settings/settings.txt", std::ios::out | std::ios::trunc);
        
        for(auto& str : settingsTemp){
            writer << str + "\n";
        }

        writer.close();
    }
}