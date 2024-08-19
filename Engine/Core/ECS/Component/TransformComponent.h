#pragma once

#include "Component.h"
#include "ECS/System/System.h"
#include <glm/glm.hpp>
#include <memory>
#include "Utils/Log.h"
#include "ECS/Entity.h"

namespace Airwave
{
    class TransformComponent : public Component
    {
    public:
        TransformComponent(glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f))
            : position(position), rotation(rotation), scale(scale) {}

        std::string GetTypeName() const override
        {
            return "TransformComponent";
        }

        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 rotation = glm::vec3(0.0f);
        glm::vec3 scale = glm::vec3(1.0f);
    };

    class TransformSystem : public System
    {
    public:
        void OnUpdate(float deltaTime, std::shared_ptr<Scene> scene) override
        {
            auto &registry = scene->GetEcsRegistry();
            auto view = registry.view<TransformComponent>(); // 获取所有包含 TransformComponent 的实体
            // 检查视图中实体数量
            if (view.empty())
            {
                LOG_WARN("No entities with TransformComponent found.");
            }
            else
            {
                for (auto entity : view)
                {
                    auto &transform = view.get<TransformComponent>(entity);
                    transform.position.x += 1.0f * deltaTime;
                    LOG_INFO("TransformSystem: entity {0} position.x: {1}", scene->GetEntity(entity)->GetName(), transform.position.x);
                }
            }
        }
    };

} // namespace Airwave
