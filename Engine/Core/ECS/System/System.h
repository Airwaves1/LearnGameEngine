#ifndef SYSTEM_H
#define SYSTEM_H

#include <entt/entt.hpp>
#include "ECS/Scene.h"
namespace Airwave
{
    class System
    {
    public:
        std::string GetName() const { return m_Name; }
        void SetName(const std::string &name) { m_Name = name; }

        virtual void OnUpdate(float deltaTime,std::shared_ptr<Scene> scene) = 0;

    private:
        std::string m_Name{"System"};
    };

}

#endif // !SYSTEM_H