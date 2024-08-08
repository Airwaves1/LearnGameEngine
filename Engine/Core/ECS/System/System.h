#ifndef SYSTEM_H
#define SYSTEM_H

namespace Airwave
{
    class System
    {
    public:
        virtual void OnUpdate(float deltaTime) {}
    };

    class RenderSystem : public System
    {
    };
}

#endif // !SYSTEM_H