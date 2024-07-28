#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec2 v_TexCoord;

void main() {

    vec4 position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
    gl_Position = position;

    v_TexCoord = a_TexCoord;
}