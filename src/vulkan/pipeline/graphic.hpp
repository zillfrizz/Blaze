#pragma once

#include <vulkan/vulkan.h>
#include <vector>

class GraphicPipeline{
    public:

    VkPipeline& get();


    private:

    VkPipeline m_handle;
    static std::vector<VkShaderModule> m_modules;
    static std::vector<VkShaderModule> m_fragModules;
};