#pragma once
#include "u_globals.hpp"

namespace utils {

    bool isOnLength(std::string str, int p_length);

    bool isOnSize(std::string str, int p_size);

    extern bool(* verifFuncs[2])(std::string, int);

    void loadSettings();

}