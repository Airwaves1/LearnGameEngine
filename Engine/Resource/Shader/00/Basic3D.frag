#version 450 core

in vec3 v_WorldPosition;
in vec3 v_Normal;
in vec4 v_Color;
in vec2 v_TexCoord;

out vec4 FragColor;

// uniform vec3 u_Color;

void main() {
    vec4 outColor = vec4(0.0, 0.0, 0.0, 1.0);
    // vec4 outColor = vec4(u_Color, 1.0);
    outColor.rgb = v_Normal;
    
    FragColor = outColor;
}