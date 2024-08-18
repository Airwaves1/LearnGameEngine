#ifndef SCENE_H
#define SCENE_H

#include "ECS/UUID.h"
#include "entt/entity/registry.hpp"

/**
 *  Scene类用于管理一个场景，包含ECS系统中的所有实体和组件。它是实体管理的中心节点。
 *  功能:
        UUID和名称: 每个场景有一个唯一的UUID和名称。
        ECS注册表: 使用entt::registry来存储和管理实体及其组件。
        实体映射: 维护一个从entt::entity到Entity对象的映射，方便管理和访问实体。
        根节点: 包含一个根节点，用于构建场景的层级结构。
 */

namespace Airwave
{
    class Node;
    class Entity;

    class Scene
    {
    public:
    private:
        UUID m_UUID;
        std::string m_Name;

        entt::registry m_EcsRegistry;

        std::unordered_map<entt::entity, std::shared_ptr<Entity>> m_EntityMap;

        std::shared_ptr<Node> m_RootNode;

        friend class Entity;
    };

} // namespace  Airwave

#endif // !SCENE_H