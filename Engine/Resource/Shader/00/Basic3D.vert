#version 450 core

layout(location=0)      in vec3 a_Position;
layout(location=1)      in vec2 a_TexCoord;
layout(location=2)      in vec3 a_Normal;

out vec3 v_WorldPosition;
out vec3 v_Normal;
out vec2 v_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

void main() {
    // 计算变换后的世界位置
    vec4 worldPosition = u_Model * vec4(a_Position, 1.0);
    
    // 顶点位置变换到裁剪空间
    gl_Position = u_ViewProjection * worldPosition;
    
    // 法线矩阵：逆转置模型矩阵
    mat3 normalMatrix = transpose(inverse(mat3(u_Model)));
    
    // 计算变换后的法线
    v_Normal = normalize(normalMatrix * a_Normal);
     
    // 传递其他变量
    v_WorldPosition = worldPosition.xyz;
    v_TexCoord = a_TexCoord;
}
