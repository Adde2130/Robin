#version 450 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in float v_TexIndex;
in vec3 v_Color;

uniform sampler2D u_Textures[1];

void main(){
    int index = int(v_TexIndex);
    if(index > 0)
        color = texture(u_Textures[index - 1], v_TexCoord) * vec4(1,1,1,1); //* vec4(v_TexCoord,1,1);
    else 
        color = vec4(v_Color, 1);
}