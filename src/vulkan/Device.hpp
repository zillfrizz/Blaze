#include <vulkan/vulkan.h>
#include <vector>

class Device{
  public:
    
    static void init(VkInstance& p_instance);
    static void cleanup();

  private:
    
    static Device s_instance;

    VkDevice m_handle;
    VkPhysicalDeviceProperties m_props;
    VkPhysicalDeviceFeatures2 m_features{ // DROP REQUIRED 1.0 FEATURES HERE
      m_features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2
    };
    VkPhysicalDeviceVulkan11Features m_features11{  // DROP REQUIRED 1.1 FEATURES HERE
      m_features11.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES
    };
    VkPhysicalDeviceVulkan12Features m_features12{  // DROP REQUIRED 1.2 FEATURES HERE
      m_features12.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES
    };
    VkPhysicalDeviceVulkan13Features m_features13{  // DROP REQUIRED 1.3 FEATURES HERE
      m_features13.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES
    };
    std::vector<char*> m_extensions{  // DROP REQUIRED EXTENSIONS HERE

    };
    VkQueue m_queues[3]{}; // 0=GRAPHICS 1=TRANSFER 2=COMPUTE

    Device();
    Device(Device&) = delete;
    Device& operator=(const Device&) = delete;

    
};