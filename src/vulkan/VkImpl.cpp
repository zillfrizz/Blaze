#include "VkImpl.hpp"

#include <iostream>
#include <cstring>

#include <GLFW/glfw3.h>

#include <utils/settings.hpp>

#include "Device.hpp"

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

    VkApplicationInfo appInfo{
        VK_STRUCTURE_TYPE_APPLICATION_INFO,
        nullptr,     
        "Blaze",  
        VK_MAKE_VERSION(1, 0, 0),
        "BlazeEngine",
        VK_MAKE_VERSION(1, 0, 0),
        VK_API_VERSION_1_1     
    }; 


    VkInstanceCreateInfo instanceInfo{};
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionsCount;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionsCount);

    #ifndef NDEBUG

    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    uint32_t availExtsCt;
    vkEnumerateInstanceExtensionProperties(nullptr, &availExtsCt, nullptr);
    std::vector<VkExtensionProperties> availExtsProps(availExtsCt);
    vkEnumerateInstanceExtensionProperties(nullptr, &availExtsCt, availExtsProps.data());

    std::cout << "Available Instance Extensions: " << std::endl;
    for(auto& availExtProps : availExtsProps){
        std::cout << '\t' << availExtProps.extensionName << " (v" << availExtProps.specVersion << ")" << std::endl; 
    }
    std::cout << std::endl;

    uint32_t availLayersCt;
    vkEnumerateInstanceLayerProperties(&availLayersCt, nullptr);
    std::vector<VkLayerProperties> availLayersProps(availLayersCt);
    vkEnumerateInstanceLayerProperties(&availLayersCt, availLayersProps.data());

    std::cout << "Available Instance Layers: " << std::endl;
    for(auto& availLayerProps : availLayersProps){
        std::cout << '\t' << availLayerProps.layerName << " (v" << availLayerProps.specVersion << ")" << std::endl; 
    }
    std::cout << std::endl;

    const std::vector<const char*> validationLayers{
        "VK_LAYER_KHRONOS_validation"
    };

    for(auto& validationLayer : validationLayers){
        bool layerFound = false;
        for(auto& availLayerProps : availLayersProps){
            if(strcmp(validationLayer, availLayerProps.layerName) == 0){
                layerFound = true;
            }
        }
        if(!layerFound){throw std::runtime_error("init(): wanted validation layer" + std::string(validationLayer) + "not supported");}
    }

    instanceInfo.enabledLayerCount = validationLayers.size();
    instanceInfo.ppEnabledLayerNames = validationLayers.data();

    VkDebugUtilsMessengerCreateInfoEXT messenger;
    setupDebugMessenger(messenger);
    instanceInfo.pNext = &messenger;

    #else
    instanceInfo.enabledLayerCount = 0;
    instanceInfo.pNext = nullptr;
    #endif

    instanceInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    instanceInfo.ppEnabledExtensionNames = extensions.data();
    if(vkCreateInstance(&instanceInfo, nullptr, &s_instance.m_handle) != VK_SUCCESS){
    };
    Device::init(s_instance.m_handle);  
}

void VkImpl::cleanup(){
    Device::cleanup();
    vkDestroyInstance(s_instance.m_handle, nullptr);
}

VkImpl::VkImpl(){}