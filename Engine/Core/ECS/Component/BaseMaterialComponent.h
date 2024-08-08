#ifndef BASE_MATERIAL_COMPONENT_H
#define BASE_MATERIAL_COMPONENT_H

#include "ECS/Component/Component.h"

namespace Airwave
{
    enum class BaseMaterialColor
    {
        COLOR_TYPE_NORMAL,
        COLOR_TYPE_TEXCOORD
    };

    class BaseMaterialComponent : public Component
    {
    public:
        BaseMaterialColor colorType;
    };

} // namespace Airwave

#endif // ! BASE_MATERIAL_COMPONENT_H