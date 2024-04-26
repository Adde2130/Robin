#version 450 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 a_Color;

uniform mat4 view;
uniform mat4 projection;

out vec4 v_Color;

void main(){
    v_Color = a_Color;
    gl_Position = projection * view * position;
}