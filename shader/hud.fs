#version 450 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in float v_TexIndex;

uniform sampler2D u_Textures[1];

void main(){
    int index = int(v_TexIndex);
    color = texture(u_Textures[index], v_TexCoord); //* vec4(v_TexCoord,1,1);
    // color = vec4(v_TexCoord, 1, 1);
}