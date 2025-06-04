#pragma once

#include <vulkan/vulkan.h>
#include <vector>
class Device;

class VkImpl{
    public:

      static void init();
      static void cleanup();
      static VkImpl& get();

      uint32_t getVersion(){
        return m_version;
      };

    private:
      static VkImpl s_instance;
      VkInstance m_handle = nullptr;
      uint32_t m_version;

      Device* m_device;

      static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
      VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
      static void setupDebugMessenger(VkDebugUtilsMessengerCreateInfoEXT &messengerInfo);
      
      VkImpl();
      VkImpl(VkImpl&) = delete;
      VkImpl& operator = (const VkImpl&) = delete;

};