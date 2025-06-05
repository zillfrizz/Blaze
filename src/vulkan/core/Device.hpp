#include <vulkan/vulkan.h>
#include <vector>

class Device{
  public:
    
    Device(VkInstance& instance);
    void cleanup();

    VkDevice& get();
    VkPhysicalDevice& getPhysical();

  private:

    VkDevice m_handle;
    VkPhysicalDevice m_physicalHandle;

    VkPhysicalDeviceProperties m_props;

  // DROP OPTIONAL 1.3 FEATURES HERE
    VkPhysicalDeviceVulkan13Features m_features13{
      m_features13.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES
    };
  // DROP OPTIONAL 1.2 FEATURES HERE
    VkPhysicalDeviceVulkan12Features m_features12{  
      m_features12.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
      m_features12.pNext = &m_features13,
    };
  // DROP OPTIONAL 1.1 FEATURES HERE
    VkPhysicalDeviceVulkan11Features m_features11{  
      m_features11.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES,
      m_features11.pNext = &m_features12
    };
  // DROP OPTIONAL 1.0 FEATURES HERE
    VkPhysicalDeviceFeatures2 m_features{ 
      m_features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
      m_features.pNext = &m_features11
    };
  
  // DROP OPTIONAL EXTENSIONS HERE
    std::vector<const char*> m_extensions { 
      "VK_EXT_full_screen_exclusive" 
    };

    VkQueue m_queues[3]{}; // 0=GRAPHICS 1=TRANSFER 2=COMPUTE

};