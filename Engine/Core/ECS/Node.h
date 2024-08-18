#ifndef NODE_H
#define NODE_H

#include "ECS/UUID.h"
#include <string>
#include <vector>

/**
 * 用于实现一个树形结构，代表场景中的层级关系。每个Node可以有父节点和多个子节点，适用于组织和管理复杂的对象层次结构。
 * 支持设置和获取父节点，添加、移除子节点，检查是否有父节点或子节点
 * Node有一个名称属性，可以设置和获取
 */

namespace Airwave
{
    class Node
    {
    public:
        Node();
        virtual ~Node();

        UUID GetUUID() const { return m_UUID; }
        std::string GetName() const;
        void SetName(const std::string &name) { this->name = name; }

        Node *GetParent() const { return m_Parent; }
        void SetParent(Node *parent);
        bool HasParent();

        const std::vector<Node *> &GetChildren() const { return m_Children; }
        void AddChild(Node *child);
        void RemoveChild(Node *child);
        bool HasChildren();

    private:
        UUID m_UUID;
        std::string name{"Node"};

        Node *m_Parent{nullptr};
        std::vector<Node *> m_Children{};
    };
}

#endif // !NODE_H