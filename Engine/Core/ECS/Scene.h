#ifndef SCENE_H
#define SCENE_H

#include "ECS/UUID.h"
#include "entt/entity/registry.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>


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
    class System;

    class Scene : public std::enable_shared_from_this<Scene>
    {
    public:
        Scene(const std::string &name = "Scene");

        ~Scene() = default;

        // 获取和设置场景名称
        std::string GetName() const { return m_Name; }
        void SetName(const std::string &name) { m_Name = name; }

        // 获取场景的UUID
        UUID GetUUID() const { return m_UUID; }

        std::shared_ptr<Node> GetRootNode() const { return m_RootNode; }

        // 添加和移除实体
        std::shared_ptr<Entity> CreateEntity(const std::string &name = "Entity");
        void RemoveEntity(std::shared_ptr<Entity> entity);

        // 获取实体
        std::shared_ptr<Entity> GetEntity(entt::entity entityHandle) const;

        // 添加和移除系统
        void AddSystem(std::shared_ptr<System> system);
        void RemoveSystem(std::shared_ptr<System> system);

        // 更新系统
        void OnUpdate(float deltaTime);

        // 获取ECS注册表
        entt::registry &GetEcsRegistry() { return m_EcsRegistry; }

        

        // 保存和加载场景
        bool Save(const std::string &filepath);
        bool Load(const std::string &filepath);

    private:
        // 事件系统
        void HandleEvent();

    private:
        UUID m_UUID;
        std::string m_Name;

        entt::registry m_EcsRegistry; // ECS注册表

        std::unordered_map<entt::entity, std::shared_ptr<Entity>> m_EntityMap;
        std::unordered_set<std::shared_ptr<System>> m_SystemSet;

        std::shared_ptr<Node> m_RootNode;

        friend class Entity;
    };

} // namespace  Airwave

#endif // !SCENE_H