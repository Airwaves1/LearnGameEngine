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
        
        entt::registry m_Registry;
    };

} // namespace  Airwave

#endif // !SCENE_H