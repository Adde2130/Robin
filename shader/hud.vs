#version 450 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in float a_TexIndex;
layout(location = 3) in vec3 a_Color;

uniform mat4 projection;

out vec2 v_TexCoord;
out float v_TexIndex;
out vec3 v_Color;

void main(){
    gl_Position = projection * position;
    v_TexCoord = a_TexCoord;
    v_TexIndex = a_TexIndex;
    v_Color = a_Color;
}