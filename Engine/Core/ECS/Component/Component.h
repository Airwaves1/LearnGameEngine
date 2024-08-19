#pragma once

#include <string>

namespace Airwave
{
    /*
     * 组件的序列化由单独的组件序列化类负责
     */
    class Component
    {
    public:
        Component() = default;
        virtual ~Component() = default;

        virtual std::string GetTypeName() const = 0;
    };
}
