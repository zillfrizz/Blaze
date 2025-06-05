#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <vector>
#include <cstring>

#include "BlazeVk.hpp"
#include "VkImpl.hpp"
#include "Window.hpp"

#include <utils/Settings.hpp>


void BlazeVk::run(){
    init();
    mainLoop();
    cleanup();
};

void BlazeVk::mainLoop(){
    while(!glfwWindowShouldClose(Window::get().getGLFWwindow())){
        glfwPollEvents();
    }
};

void BlazeVk::init(){
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    utils::loadSettings();
    VkImpl::init();
};

void BlazeVk::cleanup(){
    VkImpl::cleanup();
};