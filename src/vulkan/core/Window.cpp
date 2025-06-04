#include "window.hpp"

#include <iostream>
#include <fstream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <utils/u_globals.hpp>

Window Window::s_window;

void Window::loadSettings(){
    m_width = std::stoi(globals::settings[globals::WindowWidth]);
    m_height = std::stoi(globals::settings[globals::WindowHeight]);
    m_title = ("Blaze (v" + globals::settings[globals::Version] + ")").c_str();
}

GLFWwindow* Window::getGLFWwindow(){
        if(s_window.m_glfwWindow == nullptr){
        throw std::runtime_error("getGLFWwindow(): Trying to get null window");
    }
    return s_window.m_glfwWindow;
}

Window& Window::get(){
    if(s_window.m_glfwWindow == nullptr){
        throw std::runtime_error("get(): Trying to get null window");
    }
    return s_window;
}

void Window::init(){
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    s_window.loadSettings();
    s_window.m_glfwWindow = glfwCreateWindow(s_window.m_width, s_window.m_height, s_window.m_title, nullptr, nullptr);
}

void Window::cleanup(){
    glfwDestroyWindow(s_window.m_glfwWindow); 
    glfwTerminate();
}

Window::Window(){}