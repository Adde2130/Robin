#include "Input.h"
#include <vector>

std::shared_ptr<Window> _p_window;
std::shared_ptr<EventHandler> _ph_events;

double _mouse_x = -1;
double _mouse_y = -1;
double _mouse_dx = 0;
double _mouse_dy = 0;

void set_input_window(std::shared_ptr<Window> p_window) { _p_window = p_window; }
void set_event_handler(std::shared_ptr<EventHandler> ph_events) { _ph_events = ph_events; }

bool key_pressed (const char key) { return glfwGetKey(_p_window->get_glfw_window(), key) == GLFW_PRESS;}
bool key_released(const char key) { return glfwGetKey(_p_window->get_glfw_window(), key) == GLFW_RELEASE; }

double mouse_x() { return _mouse_x; }
double mouse_y() { return _mouse_y; }
double mouse_dx() { return _mouse_dx; }
double mouse_dy() { return _mouse_dy; }

void update() {
    _mouse_dx = 0;
    _mouse_dy = 0;
}

void mouse_callback(GLFWwindow* glfw_window, double xpos, double ypos){
    if(_mouse_x != -1)
        _mouse_dx = xpos - _mouse_x;
    if(_mouse_y != -1)
        _mouse_dy = ypos - _mouse_y;

    _mouse_x = xpos;
    _mouse_y = ypos;

    _ph_events->dispatch(MouseMoveEvent(_mouse_x, _mouse_y, _mouse_dx, _mouse_dy));
}

void keyboard_callback(GLFWwindow *glfw_window, int key, int scancode, int action, int mods) {
    _ph_events->dispatch(KeyboardEvent(key, action, mods));
}