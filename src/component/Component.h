#pragma once

enum ComponentType {
    C_COLLISION,
    C_PHYSICS,
    C_RENDER,
    C_TRANSFORM,
    C_UPDATE
};

class Component {
public:
    Component(ComponentType type) : type(type) {}
    ComponentType type;
};