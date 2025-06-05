#pragma once
#include <vulkan/vulkan.h>
#include <string>

class GLFWwindow;

class Window{
  public:
    static void init(VkInstance& instance, VkDevice& device, VkPhysicalDevice& physicalDevice);
    static void cleanup(VkInstance& instance, VkDevice& device);
    static Window& get();
    
    GLFWwindow* getGLFWwindow();

  private:
    static Window s_window;

    GLFWwindow* m_glfwWindow = nullptr;
    VkExtent2D m_extent; // -- Loadés avec loadSettings
    std::string m_title;

    VkSwapchainKHR m_swapchain;
    VkSurfaceKHR m_surface;
    uint32_t m_imageCount;
    VkImage* m_images;
    VkImageView* m_imageViews;

    void createSwapchain(VkInstance& instance, VkDevice& device, VkPhysicalDevice& physicalDevice);

    void loadSettings();

    Window();
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

};