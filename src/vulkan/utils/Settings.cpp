#include <array>
#include <fstream>
#include <limits>
#include <iostream>

#include "Settings.hpp"

namespace utils {

    bool isOnLength(std::string str, int p_length){ return str.length() <= p_length; }

    bool isOnSize(std::string str, int p_size){ return std::stoi(str) <= p_size; }

    bool (* verifFuncs[])(std::string, int) = { isOnLength, isOnSize };

    void loadSettings(){

        std::array<std::pair<bool, int>, globals::SettingsNbr> settingsStruct = {{ // STRUCTURE DES OPTIONS (TYPE, TAILLE)
            {false, 5}, // version
            {false, 5}, // engineVersion
            {true, std::numeric_limits<unsigned short>::max()}, // windowWidth
            {true, std::numeric_limits<unsigned short>::max()}, // windowHeight
        }};

        std::string settingsTemp[globals::SettingsNbr] = {// Tableau temporaire contenant le contenu du fichier, les keys par défaut;
            "version",
            "engineVersion",
            "windowWidth",
            "windowHeight"
        };

        std::ofstream create(".settings/settings.txt", std::ios::app);
        create.close();

        std::ifstream reader(".settings/settings.txt", std::ios::in);
        int i = 0;
        std::string line;
        while(std::getline(reader, line) && i < globals::SettingsNbr){          
                for(int j = 0; j < line.length() ; j++){
                    if(line[j] == ' '){
                        if(line.substr(0, j) == settingsTemp[i]){          
                            std::string value = line.substr(j+1);
                            if (!verifFuncs[settingsStruct[i].first](value, settingsStruct[i].second)){ // Si la valeur est incorrecte
                                settingsTemp[i] = settingsTemp[i] + " " + globals::settings[i];
                            }
                            else{ settingsTemp[i] = line; globals::settings[i] = value;}
                            i++; 
                            break;
                        }
                    }
                }
        }

        for(int j = i; j < globals::SettingsNbr; j++){
            settingsTemp[j] = settingsTemp[j] + " " + globals::settings[j];
        }

        reader.close();

        std::ofstream writer(".settings/settings.txt", std::ios::out | std::ios::trunc);
        
        for(auto& str : settingsTemp){
            writer << str + "\n";
        }

        writer.close();
    }
}