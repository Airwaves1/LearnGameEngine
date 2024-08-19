#include "Scene.h"
#include <memory>
#include <string>

#include "ECS/UUID.h"
#include "ECS/Entity.h"
#include "ECS/Entity.h"
#include "System/System.h"

#include "Utils/Log.h"

namespace Airwave
{

    Scene::Scene(const std::string &name) : m_Name(name), m_UUID(UUID::Generate())
    {
        m_RootNode = std::make_shared<Node>();
        m_RootNode->SetName(this->GetName() + "_RootNode");
    }

    std::shared_ptr<Entity> Scene::CreateEntity(const std::string &name)
    {
        // 创建一个新的实体，将其添加到注册器m_EcsRegistry中，并将其添加到实体映射表m_EntityMap中
        auto ecsEntity = m_EcsRegistry.create();
        auto entity = std::make_shared<Entity>(ecsEntity, shared_from_this());

        // 设置实体的名称
        entity->SetName(name);

        m_EntityMap[ecsEntity] = entity;

        // 添加到根节点
        m_RootNode->AddChild(entity);

        return entity;
    }

    void Scene::RemoveEntity(const std::shared_ptr<Entity> entity)
    {
        // 从entity中获取ecsEntity，然后在注册器m_EcsRegistry中销毁该实体，最后从实体映射表中移除该实体
        auto ecsEntity = entity->GetEcsEntity();
        m_EcsRegistry.destroy(ecsEntity);
        if (m_EntityMap.find(ecsEntity) != m_EntityMap.end())
        {
            m_EntityMap.erase(ecsEntity);
        }

        // 从根节点中移除
        m_RootNode->RemoveChild(entity);
    }

    std::shared_ptr<Entity> Scene::GetEntity(entt::entity entityHandle) const
    {
        // 从实体映射表中获取实体
        auto it = m_EntityMap.find(entityHandle);
        return it != m_EntityMap.end() ? it->second : nullptr;
    }

    void Scene::AddSystem(std::shared_ptr<System> system)
    {
        if (m_SystemSet.find(system) == m_SystemSet.end())
        {
            m_SystemSet.insert(system);
        }
        else
        {
            LOG_WARN("System {0} already exists in the scene {1}!", system->GetName(), m_Name);
        }
    }

    void Scene::RemoveSystem(std::shared_ptr<System> system)
    {
        if (m_SystemSet.find(system) != m_SystemSet.end())
        {
            m_SystemSet.erase(system);
        }
        else
        {
            LOG_WARN("System {0} does not exist in the scene {1}!", system->GetName(), m_Name);
        }
    }

    void Scene::Update(float deltaTime)
    {
        for (auto &system : m_SystemSet)
        {
            system->OnUpdate(deltaTime);
        }
    }

    bool Scene::Save(const std::string &filepath)
    {
        return false;
    }

    bool Scene::Load(const std::string &filepath)
    {
        return false;
    }

    void Scene::HandleEvent()
    {
    }

} // namespace Airwave
