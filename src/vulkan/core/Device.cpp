#include "Device.hpp"
#include "VkImpl.hpp"

#include <iostream>
#include <cstring>

#include <utils/u_device.hpp>

VkDevice& Device::get(){
    return m_handle;
}

VkPhysicalDevice& Device::getPhysical(){
    return m_physicalHandle;
}

void Device::cleanup(){
    vkDestroyDevice(m_handle, nullptr);
}

Device::Device(VkInstance& instance){
    // LOADING ALL DEVICES
    uint32_t devicesCount;
    vkEnumeratePhysicalDevices(instance, &devicesCount, nullptr);
    std::vector<VkPhysicalDevice> devices(devicesCount);
    vkEnumeratePhysicalDevices(instance, &devicesCount, devices.data());

    for(auto& device : devices){
        std::vector<const char*> requiredExtensions{  // REQUIRED EXTENSIONS
            "VK_KHR_swapchain",
            "VK_KHR_dynamic_rendering",
            "VK_KHR_synchronization2",
            "VK_KHR_timeline_semaphore",
        };
    // REQUIRED FEATURES
        VkPhysicalDeviceVulkan13Features requiredFT13{  // REQUIRED 1.3 FEATURES
            requiredFT13.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES,
        };
        VkPhysicalDeviceVulkan12Features requiredFT12{  // REQUIRED 1.2 FEATURES
            requiredFT12.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
            requiredFT12.pNext = &requiredFT13,
            .timelineSemaphore = VK_TRUE
        };
        VkPhysicalDeviceVulkan11Features requiredFT11{  // REQUIRED 1.1 FEATURES
            requiredFT11.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES,
            requiredFT11.pNext = &requiredFT12,
        };
        VkPhysicalDeviceFeatures2 requiredFT{   // REQUIRED 1.0 FEATURES
            requiredFT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
            requiredFT.pNext = &requiredFT11,
        };

        bool pickable = true;
        vkGetPhysicalDeviceProperties(device, &m_props);
        if(m_props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU){
            uint32_t minorVersion = VkImpl::get().getVersion(); // VULKAN MINOR VERSION
        // LOADING DEVICE EXTENSIONS AND QUEUE FAMILIES
            uint32_t family_count;
            vkGetPhysicalDeviceQueueFamilyProperties(device, &family_count, nullptr);
            std::vector<VkQueueFamilyProperties> families(family_count);
            vkGetPhysicalDeviceQueueFamilyProperties(device, &family_count, families.data());    
            uint32_t availableEXT_count;   
            vkEnumerateDeviceExtensionProperties(device, nullptr, &availableEXT_count, nullptr);
            std::vector<VkExtensionProperties> EXT(availableEXT_count); 
            vkEnumerateDeviceExtensionProperties(device, nullptr, &availableEXT_count, EXT.data());
        // LOADING DEVICE FEATURES
            VkPhysicalDeviceVulkan13Features ft13{
                .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES
            };
            VkPhysicalDeviceVulkan12Features ft12{
                .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
                .pNext = &ft13
            };
            VkPhysicalDeviceVulkan11Features ft11{
                .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES,
                .pNext = &ft12
            };
            VkPhysicalDeviceFeatures2 ft{
                .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
                .pNext = &ft11,
            };              
            vkGetPhysicalDeviceFeatures2(device, &ft);
        // CHECKING DES FEATURES
            unsigned int memSizes[4]{
                sizeof(VkPhysicalDeviceFeatures)/ sizeof(VkBool32),
                (sizeof(VkPhysicalDeviceVulkan11Features)-16)/ sizeof(VkBool32),
                (sizeof(VkPhysicalDeviceVulkan12Features)-16) / sizeof(VkBool32),
                (sizeof(VkPhysicalDeviceVulkan13Features)-16) / sizeof(VkBool32),
            };
            VkBool32* features[4][3]{   // 0 = FEATURES 1 = REQUIRED FEATURES 2 = OPTIONAL FEATURES
                {reinterpret_cast<VkBool32*>(&ft.features),reinterpret_cast<VkBool32*>(&requiredFT.features),reinterpret_cast<VkBool32*>(&m_features.features)},
                {reinterpret_cast<VkBool32*>(&ft11)+4,reinterpret_cast<VkBool32*>(&requiredFT11)+4,reinterpret_cast<VkBool32*>(&m_features11)+4},
                {reinterpret_cast<VkBool32*>(&ft12)+4,reinterpret_cast<VkBool32*>(&requiredFT12)+4,reinterpret_cast<VkBool32*>(&m_features12)+4},
                {reinterpret_cast<VkBool32*>(&ft13)+4,reinterpret_cast<VkBool32*>(&requiredFT13)+4,reinterpret_cast<VkBool32*>(&m_features13)+4}};
            for(int i = 0; i < 4; i++){
                for(size_t j = 0; j < memSizes[i]; j++){
                    if(features[i][1][j] && !features[i][0][j]){
                        pickable = false;
                        std::cout << "a required feature is not supported.\n";
                    }
                    if(features[i][2][j] && features[i][0][j]){
                        features[i][1][j] = VK_TRUE;
                    }else{features[i][2][j] = VK_FALSE;}
                }  
            }
        // CHECKING DES QUEUES

            int queueIds[3]{-1, -1, -1}; // 0=GRAPHICS 1=TRANSFER 2=COMPUTE
            for(int i = 0; i < family_count; i++){
                if((families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) && (queueIds[0] == -1)){
                    queueIds[0] = i;
                    continue;
                }
                if((families[i].queueFlags & VK_QUEUE_TRANSFER_BIT) && (queueIds[1] == -1)){
                    queueIds[1] = i;
                    continue;
                }
                if((families[i].queueFlags & VK_QUEUE_COMPUTE_BIT) && (queueIds[2] == -1)){    
                    queueIds[2] = i;
                }
            }
            if(queueIds[0] == -1 || queueIds[1] == -1 || queueIds[2] == -1){std::cout<<"can't find adequate queue families.\n";pickable = false;}

            // CHECKING DES EXTENSIONS
            
            for(auto& requiredExtension : requiredExtensions){
                bool founded = false;
                for(auto& extensionProps : EXT){
                    if(strcmp(requiredExtension, extensionProps.extensionName) == 0){
                        founded = true;
                        break;
                    }
                }             
                if(!founded){std::cout << "device extension " + std::string(requiredExtension) + " not supported.\n" ;pickable = false;}
            }

            for(int i = m_extensions.size() - 1; i >= 0; i--){
                bool founded = false;
                for(auto& extensionProps : EXT){
                    if(strcmp(m_extensions[i], extensionProps.extensionName) == 0){
                        founded = true;
                        requiredExtensions.push_back(m_extensions[i]);
                        break;
                    }
                }             
                if(!founded){std::cout << "optional device extension " + std::string(m_extensions[i]) + "not supported.\n";
                    m_extensions.erase(m_extensions.begin() + i);
                }
            }
            if(pickable){
                m_physicalHandle = device;
                float priority = 1.0f;
                VkDeviceQueueCreateInfo queues[3];
                for(size_t i = 0; i < 3; i++){
                    queues[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                    queues[i].pNext = nullptr;
                    queues[i].flags = 0;    // FOR FUTURE VERSIONS OF VULKAN
                    queues[i].pQueuePriorities = &priority;
                    queues[i].queueCount = 1;
                    queues[i].queueFamilyIndex = queueIds[i];
                }
                VkDeviceCreateInfo deviceInfo{};
                deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
                deviceInfo.pNext = &requiredFT;
                deviceInfo.flags = 0;   // FOR FUTURE VERSIONS OF VULKAN
                deviceInfo.queueCreateInfoCount = 3;
                deviceInfo.pQueueCreateInfos = queues;
                deviceInfo.enabledExtensionCount = requiredExtensions.size();
                deviceInfo.ppEnabledExtensionNames = requiredExtensions.data();
                deviceInfo.pEnabledFeatures = nullptr;  // ON pNext
                if(vkCreateDevice(device, &deviceInfo, nullptr, &m_handle) != VK_SUCCESS){
                    throw std::runtime_error("init(): device chosen but failed");
                }
                for(int i = 0; i < 3; i++){
                    vkGetDeviceQueue(m_handle, queueIds[i], 0, &m_queues[i]);
                }
                return;
            }
        }
    }
    throw std::runtime_error("init(): can't find adequate device");
}