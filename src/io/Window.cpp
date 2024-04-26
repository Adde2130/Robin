#include "Window.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include "Camera.h"
#include "Math.h"
#include <iostream>

Window::Window(const char* name, unsigned int width, unsigned int height, bool fullscreen, int hz)
 : fullscreen(fullscreen), width(width), height(height), windowed_width(width), windowed_height(height), hz(hz) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    xpos = (mode->width - width) / 2;
    ypos = (mode->height - height) / 2;
    if(fullscreen) {
        glfw_window = glfwCreateWindow(mode->width, mode->height, name, monitor, nullptr);
        glfwSetWindowMonitor(glfw_window, monitor, 0, 0, mode->width, mode->height, hz);
        this->width = mode->width;
        this->height = mode->height;
    } else {
        glfw_window = glfwCreateWindow(width, height, name, nullptr, nullptr);
        glfwSetWindowMonitor(glfw_window, NULL, xpos, ypos, width, height, hz);
    }

    int icon_width, icon_height, nr_channels;
    unsigned char* data = stbi_load("gfx/Robin.png", &icon_width, &icon_height, &nr_channels, 0);
    if (data) {
        GLFWimage images[1];
        images[0].width = icon_width;
        images[0].height = icon_height;
        images[0].pixels = data;
        glfwSetWindowIcon(glfw_window, 1, images);
        stbi_image_free(data);
    }

    glfwMakeContextCurrent(glfw_window);
    glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(glfw_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

}

Window::~Window() {
    glfwDestroyWindow(glfw_window);
}

void Window::set_mouse_callback(void (*mouse_callback)(GLFWwindow* window, double xpos, double ypos)) {
    glfwSetCursorPosCallback(glfw_window, mouse_callback);
}

void Window::set_keyboard_callback(void (*keyboard_callback)(GLFWwindow* window, int key, int scancode, int action, int mods)) {
    glfwSetKeyCallback(glfw_window, keyboard_callback);
}

void Window::set_framebuffer_size_callback(void (*framebuffer_size_callback)(GLFWwindow* window, int width, int height)){
    glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);
}

void Window::set_scroll_callback(void (*scroll_callback)(GLFWwindow* window, double xoffset, double yoffset)) {
    glfwSetScrollCallback(glfw_window, scroll_callback);
}

void Window::toggle_fullscreen() {
    if (fullscreen) {
        glfwSetWindowMonitor(glfw_window, NULL, xpos, ypos, windowed_width, windowed_height, GLFW_DONT_CARE);
        width = windowed_width;
        height = windowed_height;
    } else {
        glfwGetWindowSize(glfw_window, &windowed_width, &windowed_height);
        glfwGetWindowPos(glfw_window, &xpos, &ypos);
        monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(glfw_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        width = mode->width;
        height = mode->height;
    }
    fullscreen = !fullscreen;
}