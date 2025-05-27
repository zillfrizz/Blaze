#pragma once

#include <cstdint>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class GLFWwindow;

class BlazeEngine {
    public:

    void run();

    private:

    GLFWwindow* m_window;
      uint16_t m_windowWidth;
      uint16_t m_windowHeight;
      char* m_windowTitle;

    VkInstance m_instance;

    void createInstance();
    void initWindow();
    void initVulkan();

    void mainLoop();

    void cleanup();
    
};