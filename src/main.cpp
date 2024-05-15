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
#include "Input.h"
#include "ComponentHandler.h"

#define RGB(r, g, b) (r / 255.0f), (g / 255.0f), (b / 255.0f)

const Vec4f COLOR_DARK      = { 45.9f / 255, 48.0f  / 255, 61.0f / 255, 1 };
const Vec4f COLOR_RED       = { 1          , 119.0f / 255, 121.0f / 255, 1 };
const Vec4f COLOR_YELLOW    = { 1, 238.0f / 255, 139.0f / 255, 1};
const Vec4f COLOR_GREEN     = { 123.0f / 255, 1, 113.0f / 255, 1};
const Vec4f COLOR_OTHER_GREEN = { 50.0f / 255, 168.0f / 255, 82.0f / 255, 1};
const Vec4f COLOR_PINK      = { 1, 143.0f / 255, 1, 1 };
const Vec4f COLOR_BLUE      = { 133.0f / 255, 182.0f / 255, 1, 1};
const Vec4f COLOR_BLUE_DARK = { 77.0f / 255, 134.0f / 255, 219.0f / 220, 1};
const Vec4f COLOR_PURPLE    = { RGB(137, 105, 255), 1 };

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

bool move_relative = false;

std::shared_ptr<Camera> p_camera;
std::shared_ptr<Window> p_window;

Renderer* renderer;

void window_inputs(int key, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(p_window->get_glfw_window(), true);
    if(key == GLFW_KEY_F4 && action == GLFW_PRESS) {
        if(p_window->is_fullscreen())
            p_camera->fov = clampf(p_camera->fov, 1, 45);
        else
            p_camera->fov += 45.0f;
        p_window->toggle_fullscreen();
        renderer->set_window_dimensions(p_window->get_width(), p_window->get_height());
    }

    if(key == GLFW_KEY_TAB && action == GLFW_PRESS)
        move_relative = !move_relative;
}

void framebuffer_size_callback(GLFWwindow* glfw_window, int width, int height) {
    glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* glfw_window, double xoffset, double yoffset) {
    p_camera->fov -= yoffset * 3;
    if(p_window->is_fullscreen())
        p_camera->fov = clampf(p_camera->fov, 1, 90);
    else
        p_camera->fov = clampf(p_camera->fov, 1, 45);
}

int main() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    p_window = std::make_shared<Window>("Robin", WINDOW_WIDTH, WINDOW_HEIGHT, false, 240);
    p_window->set_mouse_callback(mouse_callback);
    p_window->set_keyboard_callback(keyboard_callback);
    p_window->set_framebuffer_size_callback(framebuffer_size_callback);
    p_window->set_scroll_callback(scroll_callback);

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

    set_input_window(p_window); 

    renderer = new Renderer(p_window->get_width(), p_window->get_height());
    renderer->set_clear_color(COLOR_DARK);

    Cube cube(TransformComponent(0.0f, 0.0f, 5.0f, 2.5f, 0.5f, 0.5f), COLOR_RED);
    cube.render(*renderer);

    Cube cube2(TransformComponent(3.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f), COLOR_GREEN);
    cube2.render(*renderer);

    Cube cube3(TransformComponent(10.0f, -1.0f, -2.0f, 1.0f, 0.5f, 3.0f), COLOR_PINK);
    cube3.render(*renderer);

    ComponentHandler<float> h_player;

    for(int i = 0; i < 24; i++) {
        for(int j = 0; j < 24; j++) {
            Cube temp_cube(TransformComponent(i - 8, -2, j - 8, 1, 1, 1), ((j + i) % 2) ? COLOR_YELLOW : COLOR_BLUE);
            temp_cube.render(*renderer);
        }
    }
    
    Player player(0.0f, 0.0f, 0.0f);
    player.add_render_component(*renderer);

    h_player.add(player.c_frame_update);
    
    UpdateComponent<int, int, int> c_window_input;
    c_window_input.update = &window_inputs;

    subscribe_keyboard_event(c_window_input);

    p_camera = player.get_camera();

    constexpr std::chrono::milliseconds one_second(1000);
    auto last_time = std::chrono::steady_clock::now();
    double elapsed_time = 0;
    unsigned int frames = 0;

    while (!p_window->should_close()) {
        auto current_time = std::chrono::steady_clock::now();
        float frame_time = std::chrono::duration_cast<std::chrono::duration<float>>(current_time - last_time).count();
        last_time = current_time;
        elapsed_time += frame_time;
        frames++;

        glfwPollEvents();

        h_player.update(frame_time);
        // update(frame_time);

        renderer->draw(p_camera.get());

        glfwSwapBuffers(p_window->get_glfw_window());

        if (elapsed_time >= 1) {
            std::cout << "Frames per second: " << frames << std::endl;

            frames = 0;
            elapsed_time = 0;
        }
    }

    delete renderer;

    glfwTerminate();

    return 0;
}