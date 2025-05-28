#pragma once

class GLFWwindow;

class Window{
  public:
    static void init();
    static void cleanup();
    static Window& get();
    
    GLFWwindow* getGLFWwindow();

  private:
    static Window s_window;

    GLFWwindow* m_glfwWindow = nullptr;
    unsigned short m_width; // -- Loadés avec loadSettings
    unsigned short m_height; // --
    const char* m_title;

    void loadSettings();

    Window();
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

};