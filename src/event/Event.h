#pragma once

#include <memory>

enum EventType {
    E_KEYBOARD,
    E_MOUSE_MOVE,
    E_UPDATE,
};

struct Event {
    Event(EventType type) : type(type) {}
    const EventType type;
};

class KeyboardEvent: public Event {
public:
    KeyboardEvent(int key, int action, int mods) : Event(E_KEYBOARD), key(key), action(action), mods(mods) {}
    int key;
    int action;
    int mods;
};

class MouseMoveEvent: public Event {
public:
    MouseMoveEvent(double x, double y, double dx, double dy) : Event(E_MOUSE_MOVE), x(x), y(y), dx(dx), dy(dy) {}
    double x;
    double y;
    double dx;
    double dy;
};

class UpdateEvent: public Event {
public:
    UpdateEvent(float dt) : Event(E_UPDATE), dt(dt) {}
    float dt;
};