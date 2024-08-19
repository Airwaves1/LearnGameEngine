#ifndef NODE_H
#define NODE_H

#include "ECS/UUID.h"
#include <string>
#include <vector>
#include <memory>

/**
 * 用于实现一个树形结构，代表场景中的层级关系。每个Node可以有父节点和多个子节点，适用于组织和管理复杂的对象层次结构。
 * 支持设置和获取父节点，添加、移除子节点，检查是否有父节点或子节点
 * Node有一个名称属性，可以设置和获取
 */

namespace Airwave
{
    class Node : public std::enable_shared_from_this<Node>
    {
    public:
        Node();
        virtual ~Node();

        UUID GetUUID() const { return m_UUID; }
        std::string GetName() const;
        void SetName(const std::string &name) { this->name = name; }

        std::shared_ptr<Node> GetParent();
        void SetParent( const std::shared_ptr<Node> &parent);
        bool HasParent();

        const std::vector<std::shared_ptr<Node>> &GetChildren() const;
        void AddChild(const std::shared_ptr<Node>& child);
        void RemoveChild(const std::shared_ptr<Node>& child);
        bool HasChildren();

    private:
        UUID m_UUID;
        std::string name{"Node"};

        std::weak_ptr<Node> m_Parent{};
        std::vector<std::shared_ptr<Node>> m_Children{};
    };
}

#endif // !NODE_H