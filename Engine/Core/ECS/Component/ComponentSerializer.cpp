#include "ComponentSerializer.h"
#include "TransformComponent.h"

namespace Airwave
{
    std::unordered_map<std::string, ComponentSerializer::SerializerFunc> ComponentSerializer::s_SerializerMap;
    std::unordered_map<std::string, ComponentSerializer::DeserializerFunc> ComponentSerializer::s_DeserializerMap;

    void ComponentSerializer::RegisterComponentTypes()
    {
        ComponentSerializer::RegisterComponentType(
            "TransformComponent",
            [](const Component &comp, json &j)
            {
                const auto &transform = static_cast<const TransformComponent &>(comp);
                j["position"] = {transform.position.x, transform.position.y, transform.position.z};
                j["rotation"] = {transform.rotation.x, transform.rotation.y, transform.rotation.z};
                j["scale"] = {transform.scale.x, transform.scale.y, transform.scale.z};
            },
            [](Component &comp, const json &j)
            {
                auto &transform = static_cast<TransformComponent &>(comp);
                auto pos = j["position"].get<std::array<float, 3>>();
                transform.position = {pos[0], pos[1], pos[2]};

                auto rot = j["rotation"].get<std::array<float, 3>>();
                transform.rotation = {rot[0], rot[1], rot[2]};

                auto scl = j["scale"].get<std::array<float, 3>>();
                transform.scale = {scl[0], scl[1], scl[2]};
            });
    }
}
