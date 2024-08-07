#version 450 core

in vec3 v_WorldPosition;
in vec3 v_Normal;
in vec4 v_Color;
in vec2 v_TexCoord;

out vec4 FragColor;

uniform sampler2D u_Texture;
uniform vec4 u_Color;

void main() {
    // 纹理颜色
    vec4 texColor = texture(u_Texture, v_TexCoord);

    // 法线
    vec3 normal = normalize(v_Normal);

    // 计算最终颜色
    vec4 finalColor = texColor * u_Color * v_Color;

    // 输出颜色
    FragColor = finalColor;        
}