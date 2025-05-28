#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <vector>
#include <cstring>

#include "app.hpp"
#include "instance.hpp"
#include "window.hpp"

#include "utils/settings.hpp"


void BlazeEngine::run(){
    init();
    mainLoop();
    cleanup();
};

void BlazeEngine::mainLoop(){
    while(!glfwWindowShouldClose(Window::get().getGLFWwindow())){
        glfwPollEvents();
    }
};

void BlazeEngine::init(){
    utils::loadSettings();
    Window::init();
    Instance::init();
};

void BlazeEngine::cleanup(){
    Instance::cleanup();
    Window::cleanup();
};