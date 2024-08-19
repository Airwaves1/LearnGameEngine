#pragma once

#include "Component.h"
#include <glm/glm.hpp>

namespace Airwave
{
    class TransformComponent : public Component
    {
    public:
        std::string GetTypeName() const override
        {
            return "TransformComponent";
        }

        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 rotation = glm::vec3(0.0f);
        glm::vec3 scale = glm::vec3(1.0f);
    };

} // namespace Airwave
