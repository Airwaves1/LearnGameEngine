#ifndef ENTITY_H
#define ENTITY_H

#include "ECS/Node.h"
#include "ECS/Scene.h"

/**
 * Entity类继承自Node，并封装了与ECS系统交互的功能。每个Entity代表一个场景中的实体，并能够管理其组件。
 * 功能:
        组件操作: 提供添加、获取、移除组件的功能。支持检查是否存在某个组件或某些组件。
        与场景交互: Entity持有对Scene的指针，通过该指针与entt::registry进行交互。
 */

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

        // 判断是否包含某个组件
        template <typename T>
        bool HasComponent()
        {
            return m_Scene->m_EcsRegistry.any_of<T>(m_EcsEntity);
        }

        // 判断是否包含任意一个组件
        template <typename... T>
        bool HasAnyComponent()
        {
            return m_Scene->m_EcsRegistry.any_of<T...>(m_EcsEntity);
        }

        // 判断是否包含所有组件
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