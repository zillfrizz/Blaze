#pragma once

#include "vulkan/vulkan.h"

class Instance{
    public:

      static void init();
      static void cleanup();
      static Instance& get();

    private:
      static Instance s_instance;
      VkInstance m_vkInstance = nullptr;

      static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

      VkDebugUtilsMessengerEXT m_callback;

      static void setupDebugMessenger();

      Instance();
      Instance(Instance&) = delete;
      Instance& operator = (const Instance&) = delete;

};