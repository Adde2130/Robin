#include "Entity.h"

Entity::Entity() {

}

void Entity::c_add(const Component& component) {
    components.insert({component.type, component});
}

void Entity::c_rem(const ComponentType& c_t) {
    components.erase(c_t);
}

Component& Entity::c_get(const ComponentType& c_t) {
    return components.at(c_t);
}