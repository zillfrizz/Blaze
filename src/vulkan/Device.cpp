#include "Device.hpp"
#include "VkImpl.hpp"

#include <iostream>
#include <cstring>

Device Device::s_instance = Device();

void Device::init(VkInstance& p_instance){
    
    const std::string featureNames[] = {
        "robustBufferAccess",
        "fullDrawIndexUint32",
        "imageCubeArray",
        "independentBlend",
        "geometryShader",
        "tessellationShader",
        "sampleRateShading",
        "dualSrcBlend",
        "logicOp",
        "multiDrawIndirect",
        "drawIndirectFirstInstance",
        "depthClamp",
        "depthBiasClamp",
        "fillModeNonSolid",
        "depthBounds",
        "wideLines",
        "largePoints",
        "alphaToOne",
        "multiViewport",
        "samplerAnisotropy",
        "textureCompressionETC2",
        "textureCompressionASTC_LDR",
        "textureCompressionBC",
        "occlusionQueryPrecise",
        "pipelineStatisticsQuery",
        "vertexPipelineStoresAndAtomics",
        "fragmentStoresAndAtomics",
        "shaderTessellationAndGeometryPointSize",
        "shaderImageGatherExtended",
        "shaderStorageImageExtendedFormats",
        "shaderStorageImageMultisample",
        "shaderStorageImageReadWithoutFormat",
        "shaderStorageImageWriteWithoutFormat",
        "shaderUniformBufferArrayDynamicIndexing",
        "shaderSampledImageArrayDynamicIndexing",
        "shaderStorageBufferArrayDynamicIndexing",
        "shaderStorageImageArrayDynamicIndexing",
        "shaderClipDistance",
        "shaderCullDistance",
        "shaderFloat64",
        "shaderInt64",
        "shaderInt16",
        "shaderResourceResidency",
        "shaderResourceMinLod",
        "sparseBinding",
        "sparseResidencyBuffer",
        "sparseResidencyImage2D",
        "sparseResidencyImage3D",
        "sparseResidency2Samples",
        "sparseResidency4Samples",
        "sparseResidency8Samples",
        "sparseResidency16Samples",
        "sparseResidencyAliased",
        "variableMultisampleRate",
        "inheritedQueries"
    };
    const std::vector<std::string> featureNames11 = {
        "shaderDrawParameters",
        "sparseResidency16Samples",
        "sparseResidencyAliased",
        "variablePointersStorageBuffer",
        "variablePointers",
        "protectedMemory",
        "samplerYcbcrConversion",
        "shaderTerminateInvocation",
        "shaderSubgroupExtendedTypes",
        "shaderSubgroupVote",
        "shaderSubgroupBallot",
        "shaderSubgroupShuffle",
        "shaderSubgroupShuffleRelative",
        "shaderSubgroupClustered",
        "shaderSubgroupQuad",
        "computeDerivativeGroupQuads",
        "coverageModulationMode",
        "coverageModulationTable",
        "coverageReductionMode",
        "nullDescriptor",
        "shaderResourceResidency",
        "shaderResourceMinLod"
    };
    const std::vector<std::string> featureNames12 = {
        "samplerMirrorClampToEdge",
        "drawIndirectCount",
        "storageBuffer8BitAccess",
        "uniformAndStorageBuffer8BitAccess",
        "storagePushConstant8",
        "shaderBufferInt64Atomics",
        "shaderSharedInt64Atomics",
        "shaderFloat16",
        "shaderInt8",
        "descriptorIndexing",
        "shaderInputAttachmentArrayDynamicIndexing",
        "shaderUniformTexelBufferArrayDynamicIndexing",
        "shaderStorageTexelBufferArrayDynamicIndexing",
        "shaderUniformBufferArrayNonUniformIndexing",
        "shaderSampledImageArrayNonUniformIndexing",
        "shaderStorageBufferArrayNonUniformIndexing",
        "shaderStorageImageArrayNonUniformIndexing",
        "shaderInputAttachmentArrayNonUniformIndexing",
        "shaderUniformTexelBufferArrayNonUniformIndexing",
        "shaderStorageTexelBufferArrayNonUniformIndexing",
        "descriptorBindingUniformBufferUpdateAfterBind",
        "descriptorBindingSampledImageUpdateAfterBind",
        "descriptorBindingStorageImageUpdateAfterBind",
        "descriptorBindingStorageBufferUpdateAfterBind",
        "descriptorBindingUniformTexelBufferUpdateAfterBind",
        "descriptorBindingStorageTexelBufferUpdateAfterBind",
        "descriptorBindingUpdateUnusedWhilePending",
        "descriptorBindingPartiallyBound",
        "descriptorBindingVariableDescriptorCount",
        "runtimeDescriptorArray",
        "samplerFilterMinmax",
        "scalarBlockLayout",
        "imagelessFramebuffer",
        "uniformBufferStandardLayout",
        "shaderSubgroupUniformControlFlow",
        "separateDepthStencilLayouts",
        "hostQueryReset",
        "timelineSemaphore",
        "bufferDeviceAddress",
        "bufferDeviceAddressCaptureReplay",
        "bufferDeviceAddressMultiDevice",
        "vulkanMemoryModel",
        "vulkanMemoryModelDeviceScope",
        "vulkanMemoryModelAvailabilityVisibilityChains",
        "shaderOutputViewportIndex",
        "shaderOutputLayer",
        "subgroupBroadcastDynamicId"
};
    const std::vector<std::string> featureNames13 = {
        "robustImageAccess",
        "inlineUniformBlock",
        "descriptorBindingInlineUniformBlockUpdateAfterBind",
        "pipelineCreationCacheControl",
        "privateData",
        "shaderDemoteToHelperInvocation",
        "shaderTerminateInvocation",
        "subgroupSizeControl",
        "computeFullSubgroups",
        "synchronization2",
        "textureCompressionASTC_HDR",
        "shaderZeroInitializeWorkgroupMemory",
        "dynamicRendering",
        "shaderIntegerDotProduct",
        "maintenance4"
};

    uint32_t devicesCount;
    vkEnumeratePhysicalDevices(p_instance, &devicesCount, nullptr);
    std::vector<VkPhysicalDevice> devices(devicesCount);
    vkEnumeratePhysicalDevices(p_instance, &devicesCount, devices.data());

    std::vector<char*> optExtensions{};

    for(auto& device : devices){
        bool pickable = true;
        vkGetPhysicalDeviceProperties(device, &s_instance.m_props);
        if(s_instance.m_props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU){
            uint32_t familyCt;
            uint32_t extensionsCt;
            vkGetPhysicalDeviceQueueFamilyProperties(device, &familyCt, nullptr);
            std::vector<VkQueueFamilyProperties> familiesProps(familyCt);
            vkGetPhysicalDeviceQueueFamilyProperties(device, &familyCt, familiesProps.data());       
            vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionsCt, nullptr);
            std::vector<VkExtensionProperties> extensionsProps(extensionsCt); 
            vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionsCt, extensionsProps.data());

            // FEATURES DU DEVICE SELON LA VERSION DU LOADER
            uint32_t minorVersion = VkImpl::get().getVersion();
            VkPhysicalDeviceFeatures2 ft{
                ft.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2
            };
            
            VkPhysicalDeviceVulkan11Features ft11{
                ft11.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES
            };
            VkPhysicalDeviceVulkan12Features ft12{
                ft12.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES
            };
            VkPhysicalDeviceVulkan13Features ft13{
                ft13.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES
            };
            if(minorVersion >= 1){ft.pNext = &ft11; s_instance.m_features.pNext = &s_instance.m_features11;}
            if(minorVersion >= 2){ft11.pNext = &ft12; s_instance.m_features11.pNext = &s_instance.m_features12;}
            if(minorVersion >= 3){ft12.pNext = &ft13; s_instance.m_features12.pNext = &s_instance.m_features13;}
            vkGetPhysicalDeviceFeatures2(device, &ft);

            // FEATURES OPTIONNELS
            VkPhysicalDeviceFeatures2 optFt{};              
            VkPhysicalDeviceVulkan11Features optFt11{};
            VkPhysicalDeviceVulkan12Features optFt12{};
            VkPhysicalDeviceVulkan13Features optFt13{};

            // CHECKING DES FEATURES
            VkBool32* neededFeatures = reinterpret_cast<VkBool32*>(&s_instance.m_features.features);
            VkBool32* features = reinterpret_cast<VkBool32*>(&ft.features);
            VkBool32* optFeatures = reinterpret_cast<VkBool32*>(&optFt.features);
            
            for(size_t i = 0; i < sizeof(VkPhysicalDeviceFeatures) / sizeof(VkBool32); i++){
                if(neededFeatures[i] == VK_TRUE && features[i] != VK_TRUE){
                    pickable = false;
                }
                if(optFeatures[i] == VK_TRUE && features[i] == VK_TRUE){
                    neededFeatures[i] = VK_TRUE;
                }
            }
            if(minorVersion >= 1){
                VkBool32* neededFeatures = reinterpret_cast<VkBool32*>(&s_instance.m_features11);
                VkBool32* features = reinterpret_cast<VkBool32*>(&ft11);
                VkBool32* optFeatures = reinterpret_cast<VkBool32*>(&optFt11);
                
                for(size_t i = 0; i < sizeof(VkPhysicalDeviceVulkan11Features) / sizeof(VkBool32); i++){
                    if(neededFeatures[i] == VK_TRUE && features[i] != VK_TRUE){
                        pickable = false;
                    }
                    if(optFeatures[i] == VK_TRUE && features[i] == VK_TRUE){
                        neededFeatures[i] = VK_TRUE;
                    }
                }
            }
            if(minorVersion >= 2){
                VkBool32* neededFeatures = reinterpret_cast<VkBool32*>(&s_instance.m_features12);
                VkBool32* features = reinterpret_cast<VkBool32*>(&ft12);
                VkBool32* optFeatures = reinterpret_cast<VkBool32*>(&optFt12);
                
                for(size_t i = 0; i < sizeof(VkPhysicalDeviceVulkan12Features) / sizeof(VkBool32); i++){
                    if(neededFeatures[i] == VK_TRUE && features[i] != VK_TRUE){
                        pickable = false;
                    }
                    if(optFeatures[i] == VK_TRUE && features[i] == VK_TRUE){
                        neededFeatures[i] = VK_TRUE;
                    }
                }
            }
            if(minorVersion >= 3){
                VkBool32* neededFeatures = reinterpret_cast<VkBool32*>(&s_instance.m_features13);
                VkBool32* features = reinterpret_cast<VkBool32*>(&ft13);
                VkBool32* optFeatures = reinterpret_cast<VkBool32*>(&optFt13);
                
                for(size_t i = 0; i < sizeof(VkPhysicalDeviceVulkan13Features) / sizeof(VkBool32); i++){
                    if(neededFeatures[i] == VK_TRUE && features[i] != VK_TRUE){
                        pickable = false;
                    }
                    if(optFeatures[i] == VK_TRUE && features[i] == VK_TRUE){
                        neededFeatures[i] = VK_TRUE;
                    }
                }
            }

            // CHECKING DES QUEUES

            int queueIds[3]{-1, -1, -1}; // 0=GRAPHICS 1=TRANSFER 2=COMPUTE
            for(int i = 0; i < familyCt; i++){
                if((familiesProps[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) && (queueIds[0] == -1)){
                    queueIds[0] = i;
                    continue;
                }
                if((familiesProps[i].queueFlags & VK_QUEUE_TRANSFER_BIT) && (queueIds[1] == -1)){
                    queueIds[1] = i;
                    continue;
                }
                if((familiesProps[i].queueFlags & VK_QUEUE_COMPUTE_BIT) && (queueIds[2] == -1)){    
                    queueIds[2] = i;
                }
            }
            if(queueIds[0] == -1 || queueIds[1] == -1 || queueIds[2] == -1){
                std::cout << "queue family issue " + std::to_string(queueIds[0]) + " " + std::to_string(queueIds[1])
                + " " + std::to_string(queueIds[2]) + "\n"; pickable = false;}

            // CHECKING DES EXTENSIONS
            
            for(auto& extension : s_instance.m_extensions){
                bool founded = false;
                for(auto& extensionProps : extensionsProps){
                    if(strcmp(extension, extensionProps.extensionName) == 0){
                        founded = true;
                        break;
                    }
                }             
                if(!founded){std::cout << "device extension issue \n" ;pickable = false;}
            }
            for(auto& extensionProps : extensionsProps){
                for(auto& optExtension : optExtensions){
                    if(strcmp(optExtension, extensionProps.extensionName) == 0){
                        s_instance.m_extensions.push_back(optExtension);
                    }
                }
            }
            
            if(pickable){
                float priority = 1.0f;
                VkDeviceQueueCreateInfo queues[3];
                for(size_t i = 0; i < 3; i++){
                    queues[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                    queues[i].pNext = nullptr;
                    queues[i].flags = 0;
                    queues[i].pQueuePriorities = &priority;
                    queues[i].queueCount = 1;
                    queues[i].queueFamilyIndex = queueIds[i];
                }
                VkDeviceCreateInfo deviceInfo{};
                deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
                deviceInfo.pNext = &s_instance.m_features;
                deviceInfo.flags = 0;
                deviceInfo.queueCreateInfoCount = 3;
                deviceInfo.pQueueCreateInfos = queues;
                deviceInfo.enabledExtensionCount = s_instance.m_extensions.size();
                deviceInfo.ppEnabledExtensionNames = s_instance.m_extensions.data();
                deviceInfo.pEnabledFeatures = nullptr;
                
                if(vkCreateDevice(device, &deviceInfo, nullptr, &s_instance.m_handle) != VK_SUCCESS){
                    throw std::runtime_error("init(): device chosen but failed");
                }

                for(int i = 0; i < 3; i++){
                    vkGetDeviceQueue(s_instance.m_handle, queueIds[i], 0, &s_instance.m_queues[i]);
                }

                return;
            }
        }
    }
    throw std::runtime_error("init(): can't find adequate device");
}

void Device::cleanup(){
    vkDestroyDevice(s_instance.m_handle, nullptr);
}

Device::Device(){
    
}