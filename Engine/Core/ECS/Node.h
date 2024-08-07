#ifndef NODE_H
#define NODE_H

#include "ECS/UUID.h"
#include <string>
#include <vector>

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
        std::string name {"Node"};

        Node *m_Parent{nullptr};
        std::vector<Node *> m_Children{};
    };
}

#endif // !NODE_H