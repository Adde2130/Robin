#pragma once

#include <unordered_map>
#include "Component.h"

class Entity {
public:
    Entity();
    virtual ~Entity() {}
    void c_add(const Component& component);
    void c_rem(const ComponentType& c_t);
    
    Component& c_get(const ComponentType& c_t);
private:
    std::unordered_map<ComponentType, Component> components;
};