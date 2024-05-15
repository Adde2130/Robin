#include "Input.h"
#include <vector>

ComponentHandler<double, double, double, double> mouse_events;
ComponentHandler<int, int, int> key_events;

std::shared_ptr<Window> p_input_window;

double _mouse_x = -1;
double _mouse_y = -1;
double _mouse_dx = 0;
double _mouse_dy = 0;

void set_input_window(std::shared_ptr<Window> p_window) { p_input_window = p_window; }

bool key_pressed (const char key) { return glfwGetKey(p_input_window->get_glfw_window(), key) == GLFW_PRESS;}
bool key_released(const char key) { return glfwGetKey(p_input_window->get_glfw_window(), key) == GLFW_RELEASE; }

double mouse_x() { return _mouse_x; }
double mouse_y() { return _mouse_y; }
double mouse_dx() { return _mouse_dx; }
double mouse_dy() { return _mouse_dy; }

void update() {
    _mouse_dx = 0;
    _mouse_dy = 0;
}

void subscribe_mouse_event(UpdateComponent<double, double, double, double>& c_update) {
    mouse_events.add(c_update);
}

void subscribe_keyboard_event(UpdateComponent<int, int, int>& c_update) {
    key_events.add(c_update);
}

void mouse_callback(GLFWwindow* glfw_window, double xpos, double ypos){
    if(_mouse_x != -1)
        _mouse_dx = xpos - _mouse_x;
    if(_mouse_y != -1)
        _mouse_dy = ypos - _mouse_y;

    _mouse_x = xpos;
    _mouse_y = ypos;

    mouse_events.update(_mouse_x, _mouse_y, _mouse_dx, _mouse_dy);
}

void keyboard_callback(GLFWwindow *glfw_window, int key, int scancode, int action, int mods) {
    key_events.update(key, action, mods);
}