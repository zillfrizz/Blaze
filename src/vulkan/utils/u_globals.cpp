#include "u_globals.hpp"

namespace globals{

// CES VALEURS SONT CELLES PAR DEFAUT, ELLES SONT DONC AMENEES A CHANGER A L'INITIALISATION
    std::string settings[SettingsNbr]{ // VALEUR DES OPTIONS (STRING)
        "0.0.0",
        "0.0.0",
        "800",
        "600"
    };

    std::vector<const char*> layers{    // LAYERS DISPONIBLES (DEBUG MODE ONLY)
        #ifndef NDEBUG
        "VK_LAYER_KHRONOS_validation", // VALIDATION LAYERS
        //"VK_LAYER_LUNARG_monitor",  // RUNTIME GPU MONITORING
        //"VK_LAYER_LUNARG_api_dump", // API CALLS TRACKING
        //"VK_LAYER_LUNARG_device_simulation", // GPU SIMULATION
        //"VK_LAYER_LUNARG_screenshot", // AUTOMATIC SCREENSHOTS
        //VK_LAYER_GOOGLE_threading
        //VK_LAYER_GOOGLE_unique_objects
        #endif
    };

    std::vector<const char*> instanceEXT{   // EXTENSIONS D'INSTANCE OPTIONNELLES
        #ifndef NDEBUG
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,  // DEBUG CALLBACKS
        #endif
        "VK_KHR_get_surface_capabilities2"
    };

}