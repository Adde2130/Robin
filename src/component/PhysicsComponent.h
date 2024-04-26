#pragma once

class PhysicsComponent {
public:
    PhysicsComponent();
    ~PhysicsComponent();

    float vel_x;
    float vel_y;
    float vel_z;
    float mass; 
};