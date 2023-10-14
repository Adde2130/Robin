#include "Window.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include "Camera.h"
#include "Math.h"
#include <iostream>

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

Camera* camera;

double mouse_x = -1;
double mouse_y = -1;

GLFWwindow* window;
GLFWmonitor* monitor;
int windowed_width, windowed_height, windowed_xpos, windowed_ypos;
bool is_fullscreen = false;
int hz = 60;

GLFWwindow* window_init(unsigned int width, unsigned int height, Camera* p_camera, bool fullscreen, int p_hz) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    windowed_width = 
    hz = p_hz;
    is_fullscreen = fullscreen;

    if(fullscreen) {
        window = glfwCreateWindow(mode->width, mode->height, "Robin", monitor, nullptr);
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, hz);
    } else {
        window = glfwCreateWindow(width, height, "Robin", nullptr, nullptr);
    }

    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }

    int icon_width, icon_height, nrChannels;
    unsigned char* data = stbi_load("gfx/Robin.png", &icon_width, &icon_height, &nrChannels, 0);
    if (data) {
        GLFWimage images[1];
        images[0].width = icon_width;
        images[0].height = icon_height;
        images[0].pixels = data;
        glfwSetWindowIcon(window, 1, images);
        stbi_image_free(data);
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetKeyCallback(window, keyboard_callback);

    camera = p_camera;

    return window;
}

void toggle_fullscreen() {
    if (is_fullscreen) {
        glfwSetWindowMonitor(window, NULL, windowed_xpos, windowed_ypos, windowed_width, windowed_height, GLFW_DONT_CARE);
    } else {
        glfwGetWindowSize(window, &windowed_width, &windowed_height);
        glfwGetWindowPos(window, &windowed_xpos, &windowed_ypos);
        monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    is_fullscreen = !is_fullscreen;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    const float sens = 0.1f;

    if(mouse_x != -1 && mouse_y != -1) {
        camera->yaw   += (xpos - mouse_x) * sens;
        camera->pitch += (mouse_y - ypos) * sens;
        camera->pitch = clampf(camera->pitch, -89.9f, 89.9f);

        glm::vec3 front;
        front.x = cos(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
        front.y = sin(glm::radians(camera->pitch));
        front.z = sin(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
        camera->camera_front = glm::normalize(front);
    }

    mouse_y = ypos;
    mouse_x = xpos;
}

void keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if(key == GLFW_KEY_F4 && action == GLFW_PRESS) {
        toggle_fullscreen();
    }
}