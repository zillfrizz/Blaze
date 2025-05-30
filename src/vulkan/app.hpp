#pragma once

#include <cstdint>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class Window;
class Instance;

class BlazeEngine {
  public:

    void run();

  private:

    void mainLoop();

    void init();

    void cleanup();
    
};