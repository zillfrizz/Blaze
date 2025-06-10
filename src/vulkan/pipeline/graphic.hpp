#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <glm/glm.hpp>

class GraphicPipeline{
    public:

    VkPipeline& get();

    GraphicPipeline(VkDevice& device);

    private:

    VkPipeline m_handle;
    static std::vector<VkShaderModule> m_modules;
    static std::vector<VkShaderModule> m_fragModules;
    VkPipelineLayout m_layout;
    VkDescriptorSetLayout m_descLayout;

    struct FaceInstance{
        uint8_t pos[3]; 
        uint8_t size[2];
        uint8_t rot;
        uint16_t texId;
        uint8_t light;              
    };
};