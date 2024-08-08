#ifndef SCENE_H
#define SCENE_H

#include "ECS/UUID.h"
#include "entt/entity/registry.hpp"

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