#pragma once

#include "GLFW/glfw3.h"
#include "Camera.h"

GLFWwindow* window_init(unsigned int width, unsigned int height, Camera* p_camera, bool fullscreen, int hz);

class Window {
    Window();
    ~Window();
    void toggle_fullscreen();
private:
    GLFWwindow* glfw_window;
    GLFWmonitor* monitor;
    bool is_fullscreen;

    int width;
    int height;
    int pos_x;
    int pos_y;
    int hz;

    double mouse_x;
    double mouse_y;
};