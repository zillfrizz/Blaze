#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <vector>

#include "app.hpp"


void BlazeEngine::run(){
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void BlazeEngine::createInstance(){
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Blaze";
    appInfo.applicationVersion = VK_MAKE_VERSION(0,0,0);
    appInfo.pEngineName = "BlazeEngine";
    appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);
    appInfo.pNext = nullptr;

    VkInstanceCreateInfo instanceInfo{};
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pApplicationInfo = &appInfo;


    uint32_t glfwExtensionsCount;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);


    uint32_t extensionsCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, nullptr);
    std::vector<VkExtensionProperties> extensions(extensionsCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, extensions.data());

    std::cout << "Extensions disponibles :" << std::endl;
    for(const auto& extension : extensions){
        std::cout << '\t' << extension.extensionName << std::endl;
    }

    instanceInfo.enabledExtensionCount = glfwExtensionsCount;
    instanceInfo.ppEnabledExtensionNames = glfwExtensions;
    instanceInfo.enabledLayerCount = 0;

    if(vkCreateInstance(&instanceInfo, nullptr, &m_instance) != VK_SUCCESS){
        throw std::runtime_error("Echec de la création de l'instance");
    }

}

void BlazeEngine::initWindow(){
    m_windowWidth = 800; m_windowHeight = 600; m_windowTitle = (char*)"BlazeEngine v-1";
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, m_windowTitle, nullptr, nullptr);
};

void BlazeEngine::initVulkan(){
    createInstance();
};

void BlazeEngine::mainLoop(){
    while(!glfwWindowShouldClose(m_window)){
        glfwPollEvents();
    }
};

void BlazeEngine::cleanup(){
    vkDestroyInstance(m_instance, nullptr);
    glfwDestroyWindow(m_window);
    glfwTerminate();
};