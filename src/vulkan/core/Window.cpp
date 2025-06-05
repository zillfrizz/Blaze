#include "window.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <thread>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <utils/u_globals.hpp>

Window Window::s_window;

void Window::createSwapchain(VkInstance& instance, VkDevice& device, VkPhysicalDevice& physicalDevice){

    VkSwapchainKHR oldSwapchain = m_swapchain;

    VkSurfaceCapabilitiesKHR capabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, m_surface, &capabilities);
    while(!capabilities.maxImageExtent.width || !capabilities.currentExtent.width){
        glfwPollEvents();
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, m_surface, &capabilities);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    if(capabilities.maxImageCount < 3){throw std::runtime_error("triple buffering not supported.\n");}
    if(capabilities.currentExtent.width != UINT32_MAX){
        m_extent = capabilities.currentExtent;
    }else{m_extent = VkExtent2D{std::clamp(capabilities.minImageExtent.width, m_extent.width, capabilities.maxImageExtent.width),
        std::clamp(capabilities.minImageExtent.height, m_extent.height, capabilities.maxImageExtent.height)};}

    VkSwapchainCreateInfoKHR swapInfo{};
    swapInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapInfo.surface = m_surface;
    swapInfo.flags = 0;
    swapInfo.minImageCount = 3;
    swapInfo.imageFormat = VK_FORMAT_R8G8B8A8_SRGB;
    swapInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    swapInfo.imageExtent = m_extent;
    swapInfo.imageArrayLayers = 1;
    swapInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swapInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    swapInfo.preTransform = capabilities.currentTransform;
    swapInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapInfo.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
    swapInfo.clipped = VK_TRUE;
    swapInfo.oldSwapchain = oldSwapchain;
    
    vkCreateSwapchainKHR(device, &swapInfo, nullptr, &m_swapchain);
    vkGetSwapchainImagesKHR(device, m_swapchain, &m_imageCount, nullptr);
    vkGetSwapchainImagesKHR(device, m_swapchain, &m_imageCount, m_images);

// TODO: Attendre que GPU ait fini d'utiliser oldSwapchain ici

    if(oldSwapchain != VK_NULL_HANDLE){
        vkDestroySwapchainKHR(device, oldSwapchain, nullptr);
    }   
}

void Window::loadSettings(){
    m_extent.width = std::stoi(globals::settings[globals::WindowWidth]);
    m_extent.height = std::stoi(globals::settings[globals::WindowHeight]);
    m_title = "Blaze (v" + globals::settings[globals::Version] + ")";
}

GLFWwindow* Window::getGLFWwindow(){
        if(s_window.m_glfwWindow == nullptr){
        throw std::runtime_error("getGLFWwindow(): Trying to get null window");
    }
    return s_window.m_glfwWindow;
}

Window& Window::get(){
    if(s_window.m_glfwWindow == nullptr){
        throw std::runtime_error("get(): Trying to get null window");
    }
    return s_window;
}

void Window::init(VkInstance& instance, VkDevice& device, VkPhysicalDevice& physicalDevice){
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    s_window.loadSettings();
    s_window.m_glfwWindow = glfwCreateWindow(s_window.m_extent.width, s_window.m_extent.height, s_window.m_title.c_str(), nullptr, nullptr);
    if (glfwCreateWindowSurface(instance, s_window.m_glfwWindow, nullptr, &s_window.m_surface) != VK_SUCCESS) {
        throw std::runtime_error("Échec de la création de la surface Vulkan !");
    }   
    s_window.createSwapchain(instance, device, physicalDevice);
}

void Window::cleanup(VkInstance& instance, VkDevice& device){
    vkDestroySwapchainKHR(device, s_window.m_swapchain, nullptr);
    vkDestroySurfaceKHR(instance, s_window.m_surface, nullptr);
    glfwDestroyWindow(s_window.m_glfwWindow); 
    glfwTerminate();
}

Window::Window(){}