#include "graphic.hpp"
#include <array>

VkPipeline& GraphicPipeline::get(){
    return m_handle;
}

GraphicPipeline::GraphicPipeline(VkDevice& device){

    VkDescriptorSetLayoutCreateInfo descLayoutInfo{};
    descLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    descLayoutInfo.pBindings = VK_NULL_HANDLE;
    descLayoutInfo.


    VkFormat colorFormats[] = {
        VK_FORMAT_R8G8B8A8_SRGB
    };

    VkPipelineRenderingCreateInfo dynamicRenderingInfo{};
    dynamicRenderingInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO;
    dynamicRenderingInfo.pNext = VK_NULL_HANDLE;
    dynamicRenderingInfo.viewMask = 0;
    dynamicRenderingInfo.colorAttachmentCount = 1;
    dynamicRenderingInfo.pColorAttachmentFormats = colorFormats;
    dynamicRenderingInfo.depthAttachmentFormat = VK_FORMAT_D32_SFLOAT;
    dynamicRenderingInfo.stencilAttachmentFormat = VK_FORMAT_UNDEFINED;

    VkDynamicState dynamicStates[] = {
    VK_DYNAMIC_STATE_VIEWPORT,
    VK_DYNAMIC_STATE_SCISSOR
    };

    VkPipelineDynamicStateCreateInfo dynamicInfo{};
    dynamicInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicInfo.pNext = VK_NULL_HANDLE; // FUTURE USE
    dynamicInfo.flags = 0; // FUTURE USE
    dynamicInfo.dynamicStateCount = 2;
    dynamicInfo.pDynamicStates = dynamicStates;

    VkPipelineColorBlendAttachmentState blendState{};
    blendState.blendEnable = VK_FALSE;

    VkPipelineColorBlendStateCreateInfo blendInfo{};
    blendInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    blendInfo.pNext = VK_NULL_HANDLE;
    blendInfo.flags = 0; // RASTERIZATION ORDER
    blendInfo.logicOpEnable = VK_FALSE;
    blendInfo.attachmentCount = 1;
    blendInfo.pAttachments = &blendState;

    VkPipelineDepthStencilStateCreateInfo depthInfo{};
    depthInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthInfo.pNext = VK_NULL_HANDLE;
    depthInfo.flags = 0;    // FUTURE USE
    depthInfo.depthTestEnable = VK_TRUE;
    depthInfo.depthWriteEnable = VK_TRUE;
    depthInfo.depthCompareOp = VK_COMPARE_OP_LESS;
    depthInfo.depthBoundsTestEnable = VK_FALSE;
    depthInfo.stencilTestEnable = VK_FALSE;

    VkPipelineInputAssemblyStateCreateInfo assemblyInfo{};
    assemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    assemblyInfo.pNext = VK_NULL_HANDLE;
    assemblyInfo.flags = 0; // FUTURE USE
    assemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    assemblyInfo.primitiveRestartEnable = VK_FALSE;

    VkPipelineRasterizationStateCreateInfo rasterizationInfo{};
    rasterizationInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizationInfo.pNext = VK_NULL_HANDLE;
    rasterizationInfo.flags = 0; // FUTURE USE
    rasterizationInfo.depthClampEnable = VK_FALSE;
    rasterizationInfo.rasterizerDiscardEnable = VK_FALSE;
    rasterizationInfo.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizationInfo.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizationInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizationInfo.depthBiasEnable = VK_FALSE;
    rasterizationInfo.lineWidth = 1.0f;

    VkPipelineMultisampleStateCreateInfo samplingInfo{};
    samplingInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    samplingInfo.pNext = VK_NULL_HANDLE;
    samplingInfo.flags = 0; // RESERVED
    samplingInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    samplingInfo.minSampleShading = 1.0f;
    samplingInfo.alphaToCoverageEnable = VK_FALSE;
    samplingInfo.alphaToOneEnable = VK_FALSE;

    std::array<VkVertexInputBindingDescription,2> bindings = {
        VkVertexInputBindingDescription{
            .binding = 0,
            .stride = sizeof(uint8_t[3]),
            .inputRate = VK_VERTEX_INPUT_RATE_VERTEX   
        },
        VkVertexInputBindingDescription{
            .binding = 1,
            .stride = sizeof(FaceInstance),
            .inputRate = VK_VERTEX_INPUT_RATE_INSTANCE
        }
    };

    std::array<VkVertexInputAttributeDescription, 6> attributes = {
        VkVertexInputAttributeDescription{  // VERTEX POS
            .location = 0,
            .binding = 0,
            .format = VK_FORMAT_R8G8B8_UINT,
            .offset = 0
        },
        VkVertexInputAttributeDescription{  // FACE POS
            .location = 1,
            .binding = 1,
            .format = VK_FORMAT_R8G8B8_UINT,
            .offset = 0
        },
        VkVertexInputAttributeDescription{  // FACE SIZE
            .location = 2,
            .binding = 1,
            .format = VK_FORMAT_R8G8_UINT,
            .offset = offsetof(FaceInstance, size)
        },
        VkVertexInputAttributeDescription{  // FACE LIGHT VALUE
            .location = 3,
            .binding = 1,
            .format = VK_FORMAT_R8_UINT,
            .offset = offsetof(FaceInstance, rot)
        },
         VkVertexInputAttributeDescription{  // FACE LIGHT VALUE
            .location = 4,
            .binding = 1,
            .format = VK_FORMAT_R16_UINT,
            .offset = offsetof(FaceInstance, texId)
        },
         VkVertexInputAttributeDescription{  // FACE LIGHT VALUE
            .location = 5,
            .binding = 1,
            .format = VK_FORMAT_R8_UINT,
            .offset = offsetof(FaceInstance, light)
        },
    };

    VkPipelineVertexInputStateCreateInfo inputInfo{};
    inputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    inputInfo.pNext = VK_NULL_HANDLE;
    inputInfo.flags = 0; // FUTUR USE
    inputInfo.vertexBindingDescriptionCount = 2;
    inputInfo.vertexAttributeDescriptionCount = 4;
    inputInfo.pVertexBindingDescriptions = bindings.data();
    inputInfo.pVertexAttributeDescriptions = attributes.data();

    VkPipelineShaderStageCreateInfo shaderInfos[2];
    for(auto& shaderInfo : shaderInfos){
        shaderInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        shaderInfo.pNext = VK_NULL_HANDLE;
        shaderInfo.flags = 0;
        shaderInfo.pName = "main";
        shaderInfo.pSpecializationInfo = VK_NULL_HANDLE;
    }

    shaderInfos[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
    shaderInfos[0].module = ;
    shaderInfos[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    shaderInfos[0].module = ;

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.pNext = &dynamicRenderingInfo;
    pipelineInfo.flags = 0; // VRS OR DEBUG EXT
    pipelineInfo.stageCount = 2;
    pipelineInfo.renderPass = VK_NULL_HANDLE;
    pipelineInfo.pStages = shaderInfos;
    pipelineInfo.layout 
    pipelineInfo.pVertexInputState = &inputInfo;
    pipelineInfo.pInputAssemblyState = &assemblyInfo;
    pipelineInfo.pTessellationState = VK_NULL_HANDLE; // NO TESSELLSATION FOR NOW
    pipelineInfo.pViewportState = VK_NULL_HANDLE; // DYNAMIC VIEWPORT AND SCISSOR
    pipelineInfo.pColorBlendState = &blendInfo;
    pipelineInfo.pDepthStencilState = &depthInfo;
    pipelineInfo.pMultisampleState = &samplingInfo;
    pipelineInfo.pRasterizationState = &rasterizationInfo;
    pipelineInfo.pDynamicState = &dynamicInfo;

    vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_handle);
}