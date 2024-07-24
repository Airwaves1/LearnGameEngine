#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Airwave
{
    class Camera
    {
    public:
        Camera() = default;
        virtual ~Camera() = default;

    public:
        const glm::vec3 &GetPosition() const { return m_Position; }
        inline void SetPosition(const glm::vec3 &position)
        {
            m_Position = position;
            RecalculateViewMatrix();
        }

        const glm::vec3 &GetRotation() const { return m_Rotation; }
        inline void SetRotation(const glm::vec3 &rotation)
        {
            m_Rotation = rotation;
            RecalculateViewMatrix();
        }

        const glm::mat4 &GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4 &GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4 &GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

    protected:
        virtual void Update() = 0;
        virtual void RecalculateViewMatrix() = 0;

    protected:
        glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
        glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
        glm::mat4 m_ViewProjectionMatrix = glm::mat4(1.0f);

        glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
        glm::vec3 m_Rotation = {0.0f, 0.0f, 0.0f};
    };
} // namespace Airwave

#endif // CAMERA_H