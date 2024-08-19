#include "ECS/Node.h"
#include <memory>

namespace Airwave
{
    Node::Node()
        : m_UUID(UUID::Generate())
    {
    }

    Node::~Node()
    {
        for (auto child : m_Children)
        {
            child->SetParent(nullptr);
        }
    }

    std::string Node::GetName() const
    {
        return name;
    }

    void Node::SetParent(const std::shared_ptr<Node> &parent)
    {
        m_Parent = parent;
    }

    std::shared_ptr<Node> Node::GetParent()
    {
        return m_Parent.lock();
    }

    bool Node::HasParent()
    {
        return !m_Parent.expired();
    }

    void Node::AddChild(const std::shared_ptr<Node> &child)
    {
        // 如果子节点已有父节点，则从原父节点中移除
        if (child->HasParent())
        {
            child->GetParent()->RemoveChild(child);
        }

        // 将子节点添加到当前节点的子节点列表
        m_Children.push_back(child);
        child->SetParent(shared_from_this()); // 设置当前节点为子节点的父节点
    }

    void Node::RemoveChild(const std::shared_ptr<Node> &child)
    {
        if (!this->HasChildren())
            return;
        for (auto it = m_Children.begin(); it != m_Children.end(); it++)
        {
            if (*it == child)
            {
                m_Children.erase(it);
                break;
            }
        }
    }

    bool Node::HasChildren()
    {
        return !m_Children.empty();
    }

}