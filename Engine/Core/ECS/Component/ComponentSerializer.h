#ifndef COMPONENT_SERIALIZER_H
#define COMPONENT_SERIALIZER_H

#include "Component.h"
#include <functional>
#include <unordered_map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace Airwave
{
    class ComponentSerializer
    {
    public:
        using SerializerFunc = std::function<void(const Component&, json&)>;
        using DeserializerFunc = std::function<void(Component&, const json&)>;

        static void RegisterComponentType(
            const std::string& typeName,
            SerializerFunc serializer,
            DeserializerFunc deserializer
        )
        {
            s_SerializerMap[typeName] = serializer;
            s_DeserializerMap[typeName] = deserializer;
        }

        static json Serialize(const Component& component)
        {
            json j;
            auto typeName = component.GetTypeName();
            auto it = s_SerializerMap.find(typeName);
            if (it != s_SerializerMap.end())
            {
                it->second(component, j);
            }
            return j;
        }

        static void Deserialize(Component& component, const json& j)
        {
            auto typeName = component.GetTypeName();
            auto it = s_DeserializerMap.find(typeName);
            if (it != s_DeserializerMap.end())
            {
                it->second(component, j);
            }
        }

        static void RegisterComponentTypes();

    private:
        static std::unordered_map<std::string, SerializerFunc> s_SerializerMap;
        static std::unordered_map<std::string, DeserializerFunc> s_DeserializerMap;
    };
}

#endif // COMPONENT_SERIALIZER_H
