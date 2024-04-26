#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include "graphics/Shader.h"
#include "debug/opengl_debug.h"
#include "graphics/Renderer.h"
#include "graphics/Texture.h"
#include "util/Math.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image.h"
#include "Window.h"
#include "Camera.h"
#include "Cube.h"
#include "Player.h"
#include <vector>
#include <synchapi.h>

const Vec4f COLOR_DARK      = { 45.9f / 255, 48.0f  / 255, 61.0f / 255, 1 };
const Vec4f COLOR_RED       = { 1          , 119.0f / 255, 121.0f / 255, 1 };
const Vec4f COLOR_YELLOW    = { 1, 238.0f / 255, 139.0f / 255, 1};
const Vec4f COLOR_GREEN     = { 123.0f / 255, 1, 113.0f / 255, 1};
const Vec4f COLOR_OTHER_GREEN = { 50.0f / 255, 168.0f / 255, 82.0f / 255, 1};
const Vec4f COLOR_PINK      = { 1, 143.0f / 255, 1, 1 };
const Vec4f COLOR_BLUE      = { 133.0f / 255, 182.0f / 255, 1, 1};
const Vec4f COLOR_BLUE_DARK = { 77.0f / 255, 134.0f / 255, 219.0f / 220, 1};

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

double mouse_x = -1;
double mouse_y = -1;

bool move_relative = false;

Camera* camera;
Window* window;
Renderer* renderer;

float velocity;

void update(GLFWwindow* window, Camera* camera) {
    if(move_relative) {
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera->camera_pos += camera->speed * camera->camera_front;
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera->camera_pos -= camera->speed * camera->camera_front;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera->camera_pos -= glm::normalize(glm::cross(camera->camera_front, CAMERA_UP)) * camera->speed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera->camera_pos += glm::normalize(glm::cross(camera->camera_front, CAMERA_UP)) * camera->speed;
    } else {
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            glm::vec3 temp = camera->camera_front;
            temp.y = 0;
            temp = glm::normalize(temp);
            camera->camera_pos += camera->speed * temp;
        }
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            glm::vec3 temp = camera->camera_front;
            temp.y = 0;
            temp = glm::normalize(temp);
            camera->camera_pos -= camera->speed * temp;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            glm::vec3 temp = camera->camera_front;
            temp.y = 0;
            camera->camera_pos -= glm::normalize(glm::cross(temp, CAMERA_UP)) * camera->speed;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            glm::vec3 temp = camera->camera_front;
            temp.y = 0;
            camera->camera_pos += glm::normalize(glm::cross(temp, CAMERA_UP)) * camera->speed;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && camera->camera_pos.y == 0)
        velocity = 0.025f;
    // if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    //     camera->camera_pos -= CAMERA_UP * camera->speed;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera->fov = clampf(camera->fov - 0.3f, 1, 45);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera->fov = clampf(camera->fov + 0.3f, 1, 45);
        
    camera->camera_pos.y += velocity;
    camera->camera_pos.y = clampf(camera->camera_pos.y, 0, 999);
    velocity -= 0.0004;
    
}

void mouse_callback(GLFWwindow* glfw_window, double xpos, double ypos){
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

void keyboard_callback(GLFWwindow *glfw_window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(glfw_window, true);
    if(key == GLFW_KEY_F4 && action == GLFW_PRESS) {
        if(window->is_fullscreen())
            camera->fov = clampf(camera->fov, 1, 45);
        else
            camera->fov += 45.0f;
        window->toggle_fullscreen();
        renderer->set_window_dimensions(window->get_width(), window->get_height());
    }

    if(key == GLFW_KEY_TAB && action == GLFW_PRESS)
        move_relative = !move_relative;
}

void framebuffer_size_callback(GLFWwindow* glfw_window, int width, int height) {
    glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* glfw_window, double xoffset, double yoffset) {
    camera->fov -= yoffset * 3;
    if(window->is_fullscreen())
        camera->fov = clampf(camera->fov, 1, 90);
    else
        camera->fov = clampf(camera->fov, 1, 45);
}

int main() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }



    camera = new Camera(45.0f);
    camera->camera_pos.x -= 2;

    window = new Window("Robin", WINDOW_WIDTH, WINDOW_HEIGHT, false, 240);
    window->set_mouse_callback(mouse_callback);
    window->set_keyboard_callback(keyboard_callback);
    window->set_framebuffer_size_callback(framebuffer_size_callback);
    window->set_scroll_callback(scroll_callback);

    // No V-SYNC
    // glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    enable_opengl_callbacks();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    glEnable(GL_DEPTH_TEST);


    renderer = new Renderer(window->get_width(), window->get_height());
    renderer->set_clear_color(COLOR_DARK);

    Vec4f cube1_color= {COLOR_RED.x, COLOR_RED.y, COLOR_RED.z, 0.6f};
    Cube cube(TransformComponent(0.0f, 0.0f, 5.0f, 2.5f, 0.5f, 0.5f), cube1_color);
    cube.render(*renderer);

    Vec4f cube2_color= {COLOR_GREEN.x, COLOR_GREEN.y, COLOR_GREEN.z, 0.6f};
    Cube cube2(TransformComponent(3.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f), cube2_color);
    cube2.render(*renderer);

    for(int i = 0; i < 24; i++) {
        for(int j = 0; j < 24; j++) {
            Cube temp_cube(TransformComponent(i - 8, -2, j - 8, 1, 1, 1), ((j + i) % 2) ? COLOR_YELLOW : COLOR_BLUE);
            temp_cube.render(*renderer);
        }
    }
    
    Player player(1.0f, 1.0f, 1.0f);
    player.add_render_component(*renderer);

    constexpr std::chrono::milliseconds one_second(1000);
    auto start_time = std::chrono::steady_clock::now();
    unsigned int frames = 0;

    while (!window->should_close()) {
        frames++;

        glfwPollEvents();

        update(window->get_glfw_window(), camera);

        renderer->draw(camera);

        glfwSwapBuffers(window->get_glfw_window());

        auto current_time = std::chrono::steady_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);
        if (elapsed_time >= one_second) {
            std::cout << "Frames per second: " << frames << std::endl;
            frames = 0; 
            start_time = std::chrono::steady_clock::now();
        }
    }

    delete window;
    delete camera;
    delete renderer;

    glfwTerminate();

    return 0;
}