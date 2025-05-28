#ifdef GRAPHIC_LIB_VULKAN
#include "vulkan/app.hpp"
#endif

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>

int main(){

    #ifdef GRAPHIC_LIB_VULKAN
    BlazeEngine engine;
    #else
    return EXIT_FAILURE;
    #endif

    try{
        engine.run();
    }catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}