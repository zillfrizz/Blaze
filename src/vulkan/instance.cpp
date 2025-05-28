#include "instance.hpp"

#include <iostream>
#include <vector>
#include <cstring>

#include <GLFW/glfw3.h>

#include <utils/settings.hpp>

Instance Instance::s_instance;

VKAPI_ATTR VkBool32 VKAPI_CALL Instance::debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {

    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}

void Instance::setupDebugMessenger(){
    VkDebugUtilsMessengerCreateInfoEXT messengerInfo{};
    messengerInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
}

Instance& Instance::get(){
    if(s_instance.m_vkInstance == VK_NULL_HANDLE){
        throw std::runtime_error("get(): trying to get null instance");
    }
    return s_instance;
}

void Instance::init(){
    VkApplicationInfo appInfo{}; 
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = nullptr;
    appInfo.applicationVersion = std::stoi(utils::settingsValues[utils::Version]);
    appInfo.pApplicationName = "Blaze";
    appInfo.engineVersion = std::stoi(utils::settingsValues[utils::EngineVersion]);
    appInfo.pEngineName = "BlazeEngine";

    VkInstanceCreateInfo instanceInfo{};
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pNext = nullptr;
    instanceInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionsCount;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionsCount);

    #ifndef NDEBUG

    setupDebugMessenger();

    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    uint32_t availableExtensionsCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, nullptr);
    std::vector<VkExtensionProperties> availableExtensionsProps(availableExtensionsCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, availableExtensionsProps.data());

    std::cout << "Available Instance Extensions: " << std::endl;
    for(auto& availableExtensionProps : availableExtensionsProps){
        std::cout << '\t' << availableExtensionProps.extensionName << " (v" << availableExtensionProps.specVersion << ")" << std::endl; 
    }
    std::cout << std::endl;

    uint32_t availableLayersCount;
    vkEnumerateInstanceLayerProperties(&availableLayersCount, nullptr);
    std::vector<VkLayerProperties> availableLayersProps(availableLayersCount);
    vkEnumerateInstanceLayerProperties(&availableLayersCount, availableLayersProps.data());

    std::cout << "Available Instance Layers: " << std::endl;
    for(auto& availableExtensionProps : availableExtensionsProps){
        std::cout << '\t' << availableExtensionProps.extensionName << " (v" << availableExtensionProps.specVersion << ")" << std::endl; 
    }
    std::cout << std::endl;

    const std::vector<const char*> validationLayers{
        "VK_LAYER_KHRONOS_validation"
    };

    for(auto& validationLayer : validationLayers){
        bool layerFound = false;
        for(auto& availableLayerProps : availableLayersProps){
            if(strcmp(validationLayer, availableLayerProps.layerName) == 0){
                layerFound = true;
            }
        }

        if(!layerFound){throw std::runtime_error("init(): wanted validation layer not supported");}
    }

    instanceInfo.enabledLayerCount = validationLayers.size();
    instanceInfo.ppEnabledLayerNames = validationLayers.data();

    #else

    

    instanceInfo.enabledLayerCount = 0;
    #endif

    instanceInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    instanceInfo.ppEnabledExtensionNames = extensions.data();

    VkResult result = vkCreateInstance(&instanceInfo, nullptr, &s_instance.m_vkInstance);
    if(result != VK_SUCCESS){
        throw std::runtime_error("init(): when creating instance -> " + result);
    }
}

void Instance::cleanup(){
    vkDestroyInstance(s_instance.m_vkInstance, nullptr);
}

Instance::Instance(){}