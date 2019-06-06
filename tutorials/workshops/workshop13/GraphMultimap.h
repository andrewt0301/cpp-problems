//
// Created by Tatarnikov_A on 06.06.2019.
//

#ifndef TUTORIALS_GRAPHMULTIMAP_H
#define TUTORIALS_GRAPHMULTIMAP_H

#include "Node.h"

#include <iostream>
#include <map>

template <typename T>
class GraphMultimap
{
private:
    using     Node = Node<T>;
    using Multimap = std::multimap<Node*, Node*>;

    using       iterator = typename Multimap::iterator;
    using const_iterator = typename Multimap::const_iterator;

    Multimap _nodes;

public:
    GraphMultimap() = default;

    ~GraphMultimap()
    {
        Node* node = nullptr;
        for (iterator it = _nodes.begin(); it != _nodes.end(); ++it)
        {
            if (it->first != node)
            {
                node = it->first;
                delete node;
            }
        }
    }

    GraphMultimap(const GraphMultimap&) = delete;
    GraphMultimap& operator=(const GraphMultimap&) = delete;

    Node* addNode(const T& tag)
    {
        Node* node = new Node(tag);
        _nodes.insert({node, node});
        return node;
    }

    void removeNode(Node* node)
    {
        delete node;
        std::pair<iterator, iterator> range = _nodes.equal_range(node);

        for (iterator it = range.first; it != range.second;)
            it = _nodes.erase(it);
    }

    void addEdge(Node* src, Node* dest)
    {
        _nodes.insert({src, dest});
    }

    void removeEdge(Node* src, Node* dest)
    {
        std::pair<iterator, iterator> range = _nodes.equal_range(src);
        for (iterator it = range.first; it != range.second;)
        {
            if (it->second == dest)
                it = _nodes.erase(it);
            else
                ++it;
        }
    }

    template <typename TVisitor>
    void bfs(Node* src, TVisitor visitor)
    {
        // TODO
    }

    template <typename TVisitor>
    void dfs(Node* src, TVisitor visitor)
    {
        // TODO
    }

    friend std::ostream& operator<<(std::ostream& out, const GraphMultimap& graph)
    {
        const Multimap& nodes = graph._nodes;

        Node* node = nullptr;
        bool start = true;

        for (const_iterator it = nodes.begin(); it != nodes.end(); ++it)
        {
            if (it->first != node)
            {
                if (node != nullptr)
                    out << std::endl;

                node = it->first;
                out << node->tag << ": ";
                start = true;
            }
            else
            {
                if (start)
                    start = false;
                else
                    out << ", ";

                out << it->second->tag;
            }
        }

        return out;
    }

};

#endif //TUTORIALS_GRAPHMULTIMAP_H
