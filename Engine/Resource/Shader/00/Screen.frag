#version 450 core

out vec4 FragColor;

in vec2 v_TexCoord;

uniform sampler2D u_ScreenTexture;

void main() 
{
    vec4 outColor = vec4(1.0);
    outColor.rgb = texture(u_ScreenTexture, v_TexCoord).rgb;
    FragColor = outColor;
}