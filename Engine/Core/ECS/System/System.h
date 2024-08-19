#ifndef SYSTEM_H
#define SYSTEM_H

#include "ECS/UUID.h"
namespace Airwave
{
    class System
    {
    public:
        std::string GetName() const { return m_Name; }
        virtual void OnUpdate(float deltaTime) {}

    private:
        std::string m_Name;
        UUID m_UUID;
    };

    class RenderSystem : public System
    {
    };
}

#endif // !SYSTEM_H