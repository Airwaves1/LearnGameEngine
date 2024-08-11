#version 450 core

in vec3 v_WorldPosition;
in vec3 v_Normal;
in vec4 v_Color;
in vec2 v_TexCoord;

out vec4 FragColor;

uniform sampler2D u_Texture_0;
uniform sampler2D u_Texture_1;
void main() {
    vec4 outColor = vec4(0.0, 0.0, 0.0, 1.0);

    vec4 texColor_1 = texture(u_Texture_0, v_TexCoord);
    vec4 texColor_2 = texture(u_Texture_1, v_TexCoord);

    outColor.rgb = mix(texColor_1.rgb, texColor_2.rgb, 0.5);
    // outColor = texColor_1;
    FragColor = outColor;
}