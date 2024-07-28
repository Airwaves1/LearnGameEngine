#version 450 core

in vec2 v_TexCoord;

uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;

out vec4 FragColor;

void main() {
    vec4 texColor0 = texture(u_Texture0, v_TexCoord);
    vec4 texColor1 = texture(u_Texture1, v_TexCoord);

    FragColor = mix(texColor0, texColor1, 0.2);
}
