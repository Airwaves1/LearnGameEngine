#pragma once

#include "Component.h"
#include <nlohmann/json.hpp>
#include <unordered_map>

namespace Airwave
{
    class ComponentSerializer
    {
    public:
        // 序列化组件到JSON
        template <typename T>
        static nlohmann::json Serialize(const T &component)
        {
            nlohmann::json j;
            // 假设每个组件都有一个名称和类型
            j["type"] = component.GetTypeName();
            // 调用具体组件的序列化方法
            component.Serialize(j["data"]);
            return j;
        }

        // 从JSON反序列化组件
        template <typename T>
        static void Deserialize(T &component, const nlohmann::json &jsonData)
        {
            // 调用具体组件的反序列化方法
            component.Deserialize(jsonData["data"]);
        }

        // 注册组件类型和对应的序列化函数
        static void RegisterComponentType(const std::string &typeName,
                                          std::function<void(const Component &, nlohmann::json &)> serializeFunc,
                                          std::function<void(Component &, const nlohmann::json &)> deserializeFunc)
        {
            s_SerializeFunctions[typeName] = serializeFunc;
            s_DeserializeFunctions[typeName] = deserializeFunc;
        }

        // 根据类型名称序列化组件
        static nlohmann::json Serialize(const Component &component)
        {
            auto it = s_SerializeFunctions.find(component.GetTypeName());
            if (it != s_SerializeFunctions.end())
            {
                nlohmann::json j;
                it->second(component, j);
                return j;
            }
            throw std::runtime_error("Unsupported component type");
        }

        // 根据类型名称反序列化组件
        static void Deserialize(Component &component, const nlohmann::json &jsonData)
        {
            auto it = s_DeserializeFunctions.find(component.GetTypeName());
            if (it != s_DeserializeFunctions.end())
            {
                it->second(component, jsonData);
            }
            else
            {
                throw std::runtime_error("Unsupported component type");
            }
        }

    private:
        static std::unordered_map<std::string, std::function<void(const Component &, nlohmann::json &)>> s_SerializeFunctions;
        static std::unordered_map<std::string, std::function<void(Component &, const nlohmann::json &)>> s_DeserializeFunctions;
    };
}
