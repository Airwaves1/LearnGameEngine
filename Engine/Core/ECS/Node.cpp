#include "ECS/Node.h"

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
            delete child;
        }
    }

    std::string Node::GetName() const
    {
        return name;
    }

    void Node::SetParent(Node *parent) { m_Parent = parent; }

    bool Node::HasParent()
    {
        return m_Parent != nullptr;
    }

    void Node::AddChild(Node *child)
    {
        if (child->HasParent())
        {
            child->GetParent()->RemoveChild(child);
        }
        m_Children.push_back(child);
        child->SetParent(this);
    }

    void Node::RemoveChild(Node *child)
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