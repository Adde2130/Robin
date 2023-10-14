#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "graphics/Shader.h"
#include "debug/opengl_debug.h"
#include "graphics/VertexBuffer.h"
#include "graphics/IndexBuffer.h"
#include "graphics/VertexArray.h"
#include "graphics/VertexBufferLayout.h"
#include "graphics/Renderer.h"
#include "graphics/Texture.h"
#include "util/Math.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image.h"
#include "Model.h"
#include "Window.h"
#include "Camera.h"
#include "Surface.h"
#include <vector>

const Vec4f COLOR_DARK   = { 45.9f / 255, 48.0f  / 255, 61.0f / 255, 1 };
const Vec4f COLOR_RED    = { 1          , 119.0f / 255, 121.0f / 255, 1 };
const Vec4f COLOR_YELLOW = { 1, 238.0f / 255, 139.0f / 255, 1};
const Vec4f COLOR_GREEN  = { 123.0f / 255, 1, 113.0f / 255, 1};
const Vec4f COLOR_PINK   = { 1, 143.0f / 255, 1, 1 };
const Vec4f COLOR_BLUE   = { 133.0f / 255, 182.0f / 255, 1, 1};

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

double mouse_x = -1;
double mouse_y = -1;

bool move_relative = true;

Camera* camera;
Window* window;

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
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera->camera_pos += CAMERA_UP * camera->speed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera->camera_pos -= CAMERA_UP * camera->speed;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera->fov = clampf(camera->fov - 0.3f, 1, 45);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera->fov = clampf(camera->fov + 0.3f, 1, 45);
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

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    enable_opengl_callbacks();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    float size = 0.5f;

    float vertices[] = {
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        size, 0.0f, 0.0f, 1.0f, 0.0f,
        size, size, 0.0f, 1.0f, 1.0f,
        0.0f, size, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, size, 0.0f, 0.0f,
        size, 0.0f, size, 1.0f, 0.0f,
        size, size, size, 1.0f, 1.0f,
        0.0f, size, size, 0.0f, 1.0f
    };

    unsigned short indices[] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        0, 1, 5, 5, 4, 0,
        2, 3, 7, 7, 6, 2,
        0, 3, 7, 7, 4, 0,
        1, 2, 6, 6, 5, 1 
    };

    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(2);
    va.add_buffer(vb, layout);

    IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned short));

    Shader shader("shader/solid_color.vs", "shader/solid_color.fs");

    Model cube(va, ib, shader);

    cube.get_shader().bind();
    cube.get_shader().set_uniform("u_Color", COLOR_RED);

    Renderer renderer;
    renderer.set_clear_color(COLOR_DARK);

    float angle = 0.0f;

    std::vector<Surface*> surfaces;
    for(int i = 0; i < 32; i++)
        for(int j = 0; j < 32; j++)
            surfaces.push_back(new Surface(i - 16, -1, j - 16, 1, 1));

    while (!window->should_close()) {
        glfwPollEvents();

        update(window->get_glfw_window(), camera);

        renderer.clear();
        glm::mat4 view = camera->get_view_matrix();
        glm::mat4 projection = camera->get_projection_matrix((float)window->get_width() / (float)window->get_height());
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(size / 2, size / 2, size / 2));

        model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-size / 2, -size / 2, -size / 2));

        cube.get_shader().bind();
        cube.get_shader().set_uniform("model", model);
        cube.get_shader().set_uniform("view", view);
        cube.get_shader().set_uniform("projection", projection);

        renderer.draw(cube);

        for(int i = 0; i < 1024; i++) {
            surfaces[i]->shader->bind();
            surfaces[i]->shader->set_uniform("model", surfaces[i]->model);
            surfaces[i]->shader->set_uniform("view", camera->get_view_matrix());
            surfaces[i]->shader->set_uniform("projection", camera->get_projection_matrix((float)window->get_width() / (float)window->get_height()));
            surfaces[i]->shader->set_uniform("u_Color", (i + i / 32) % 2 ? COLOR_YELLOW : COLOR_BLUE);
            surfaces[i]->va->bind();
            surfaces[i]->ib->bind();
            renderer.draw(surfaces[i]->va, surfaces[i]->ib, surfaces[i]->shader);
        }

        angle += 0.01f;

        glfwSwapBuffers(window->get_glfw_window());
    }

    delete window;
    delete camera;

    glfwTerminate();

    return 0;
}