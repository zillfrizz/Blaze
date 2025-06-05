#include "VkImpl.hpp"

#include <iostream>
#include <cstring>

#include <GLFW/glfw3.h>

#include <utils/u_globals.hpp>

#include "Device.hpp"
#include "Window.hpp"

#define LOAD_INSTANCE_FN(instance, name) \
    name = (PFN_##name) vkGetInstanceProcAddr(instance, #name); \
    if (!name) { fprintf(stderr, "Échec chargement %s\n", #name); exit(1); }

VkImpl VkImpl::s_instance;

VKAPI_ATTR VkBool32 VKAPI_CALL VkImpl::debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {

    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}

void VkImpl::setupDebugMessenger(VkDebugUtilsMessengerCreateInfoEXT &messengerInfo){
    messengerInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    messengerInfo.pNext = nullptr;
    messengerInfo.flags = 0;
    messengerInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    messengerInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    messengerInfo.pfnUserCallback = VkImpl::debugCallback;
    messengerInfo.pUserData = nullptr;
    
}

VkImpl& VkImpl::get(){
    if(s_instance.m_handle == VK_NULL_HANDLE){
        throw std::runtime_error("get(): trying to get null instance");
    }
    return s_instance;
}

void VkImpl::init(){
    vkEnumerateInstanceVersion(&s_instance.m_version);

    VkInstanceCreateInfo instanceInfo{
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO
    };

    VkApplicationInfo appInfo{
        VK_STRUCTURE_TYPE_APPLICATION_INFO,
        nullptr,     
        "Blaze",  
        static_cast<uint32_t>(std::stoi(globals::settings[globals::Version])),
        "BlazeEngine",
        static_cast<uint32_t>(std::stoi(globals::settings[globals::EngineVersion])),
        VK_API_VERSION_1_3     
    }; 

    instanceInfo.pApplicationInfo = &appInfo;

    std::vector<const char*> extensions{ // EXTENSIONS D'INSTANCE REQUISES
    };

    uint32_t glfwExtensionsCount;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);  // EXTENSIONS GLFW (REQUISES)
    extensions.reserve(extensions.size() + glfwExtensionsCount);
    extensions.insert(extensions.end(), glfwExtensions, glfwExtensions + glfwExtensionsCount);


    // AVAILABLE EXTENSIONS AND LAYERS INIT
    
    uint32_t availableEXT_count;
    vkEnumerateInstanceExtensionProperties(nullptr, &availableEXT_count, nullptr);
    std::vector<VkExtensionProperties> availableEXT(availableEXT_count);
    vkEnumerateInstanceExtensionProperties(nullptr, &availableEXT_count, availableEXT.data());

    uint32_t availableLAYER_count;
    vkEnumerateInstanceLayerProperties(&availableLAYER_count, nullptr);
    std::vector<VkLayerProperties> availableLAYER(availableLAYER_count);
    vkEnumerateInstanceLayerProperties(&availableLAYER_count, availableLAYER.data());

    std::cout << "Available Instance Extensions: " << std::endl;
    for(auto& EXT : availableEXT){
        std::cout << '\t' << EXT.extensionName << " (v" << EXT.specVersion << ")" << std::endl; 
    }
    std::cout << std::endl;

    std::cout << "Available Instance Layers: " << std::endl;
    for(auto& LAYER : availableLAYER){
        std::cout << '\t' << LAYER.layerName << " (v" << LAYER.specVersion << ")" << std::endl; 
    }
    std::cout << std::endl;

    // TESTING EXTENSIONS AND LAYERS COMPATIBILITY

    for(auto& extension : extensions){
        bool extensionFound = false;
        for(auto& EXT : availableEXT){
            if(strcmp(extension, EXT.extensionName) == 0){
                extensionFound = true;
            }
        }
        if(!extensionFound){throw std::runtime_error("required extension " + std::string(extension) + " not supported.\n");}
    }

    for(int i = globals::instanceEXT.size() - 1; i >= 0; i--){
        bool extensionFound = false;
        for(auto& EXT : availableEXT){
            if(strcmp(globals::instanceEXT[i], EXT.extensionName) == 0){
                extensionFound = true;
                extensions.push_back(globals::instanceEXT[i]);
            }
        }
        if(!extensionFound){std::cout << "Extension: " << globals::instanceEXT[i] << " not supported.\n";
            globals::instanceEXT.erase(globals::instanceEXT.begin() + i);
        }
    }

    for(int i = globals::layers.size() - 1; i >= 0; i--){
        bool layerFound = false;
        for(auto& LAYER : availableLAYER){
            if(strcmp(globals::layers[i], LAYER.layerName) == 0){
                layerFound = true;
            }
        }
        if(!layerFound){std::cout << "Layer: " << globals::layers[i] << " not supported.\n";
            globals::layers.erase(globals::layers.begin() + i);
        }
    }

    instanceInfo.enabledLayerCount = globals::layers.size();
    instanceInfo.ppEnabledLayerNames = globals::layers.data();
    instanceInfo.enabledExtensionCount = extensions.size();
    instanceInfo.ppEnabledExtensionNames = extensions.data();

    #ifndef NDEBUG
    VkDebugUtilsMessengerCreateInfoEXT messenger;
    setupDebugMessenger(messenger);
    instanceInfo.pNext = &messenger;
    #endif
    if(vkCreateInstance(&instanceInfo, nullptr, &s_instance.m_handle) != VK_SUCCESS){throw std::runtime_error("can't create instance !\n");};
    s_instance.m_device = new Device(s_instance.m_handle);  
    Window::init(s_instance.m_handle, s_instance.m_device->get(), s_instance.m_device->getPhysical());
}

void VkImpl::cleanup(){
    Window::cleanup(s_instance.m_handle,s_instance.m_device->get());
    s_instance.m_device->cleanup();
    vkDestroyInstance(s_instance.m_handle, nullptr);
}

VkImpl::VkImpl(){}