// #include "Camera/OrthographicCamera.h"

// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include "OrthographicCamera.h"

// namespace Airwave
// {
//     OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
//     {
//         m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
//         RecalculateViewMatrix();
//     }

//     void OrthographicCamera::Update()
//     {
//     }

//     void OrthographicCamera::RecalculateViewMatrix()
//     {
//         glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
//                               glm::rotate(glm::mat4(1.0f), m_Rotation.x, glm::vec3(1.0,0.0,0.0)) *
//                               glm::rotate(glm::mat4(1.0f), m_Rotation.y, glm::vec3(0.0,1.0,0.0)) *
//                               glm::rotate(glm::mat4(1.0f), m_Rotation.z, glm::vec3(0.0,0.0,1.0));


//         m_ViewMatrix = glm::inverse(transform);
//         m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
//     }

// } // namespace Airwave