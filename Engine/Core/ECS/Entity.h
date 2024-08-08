#ifndef ENTITY_H
#define ENTITY_H

#include "ECS/Node.h"
#include "ECS/Scene.h"

namespace Airwave
{
    class Entity : public Node
    {
    public:
        Entity(const entt::entity &ecsEntity, Scene *scene) : m_EcsEntity(ecsEntity), m_Scene(scene) {}
        ~Entity() override = default;

        // 添加组件
        template <typename T, typename... Args>
        T &AddComponent(Args &&...args)
        {
            return m_Scene->m_EcsRegistry.emplace<T>(m_EcsEntity, std::forward<Args>(args)...);
        }

        // 获取组件
        template <typename T>
        T &GetComponent()
        {
            assert(HasComponent<T>() && "Entity does not have component!");
            return m_Scene->m_EcsRegistry.get<T>(m_EcsEntity);
        }

        // 移除组件
        template <typename T>
        void RemoveComponent()
        {
            assert(HasComponent<T>() && "Entity does not have component!");
            m_Scene->m_EcsRegistry.remove<T>(m_EcsEntity);
        }

        // 判断是否有组件
        // 1.判断是否包含某个组件
        // 2.判断是否包含任意一个组件
        // 3. 判断是否包含所有组件
        template <typename T>
        bool HasComponent()
        {
            return m_Scene->m_EcsRegistry.any_of<T>(m_EcsEntity);
        }

        template <typename... T>
        bool HasAnyComponent()
        {
            return m_Scene->m_EcsRegistry.any_of<T...>(m_EcsEntity);
        }

        template <typename... T>
        bool HasAllComponent()
        {
            return m_Scene->m_EcsRegistry.all_of<T...>(m_EcsEntity);
        }

    private:
        entt::entity m_EcsEntity;
        Scene *m_Scene;
    };

}

#endif // !ENTITY_H