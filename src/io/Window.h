#pragma once

#include "GLFW/glfw3.h"
#include "Camera.h"

class Window {
public:
    Window(const char* name, unsigned int width, unsigned int height, bool fullscreen, int hz);
    ~Window();
    void toggle_fullscreen();
    void set_mouse_callback(void (*mouse_callback)(GLFWwindow* window, double xpos, double ypos));
    void set_keyboard_callback(void (*keyboard_callback)(GLFWwindow *window, int key, int scancode, int action, int mods));
    void set_framebuffer_size_callback(void (*framebuffer_size_callback)(GLFWwindow* window, int width, int height));
    void set_scroll_callback(void (*scroll_callback)(GLFWwindow* window, double xoffset, double yoffset));

    bool should_close() const { return glfwWindowShouldClose(glfw_window); }
    bool is_fullscreen() const { return fullscreen; }

    int get_width() const { return width; }
    int get_height() const { return height; }

    GLFWwindow* get_glfw_window() { return glfw_window; }
private:
    GLFWwindow* glfw_window;
    GLFWmonitor* monitor;

    const char* name;
    bool fullscreen;

    int width;
    int height;
    int windowed_width;
    int windowed_height;
    int xpos;
    int ypos;
    int hz;

    double mouse_x;
    double mouse_y;
};