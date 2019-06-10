//
// Created by Tatarnikov_A on 06.06.2019.
//

#ifndef TUTORIALS_GRAPHMAP_H
#define TUTORIALS_GRAPHMAP_H

#include <iostream>
#include <map>
#include <set>
#include <queue>

#include "Node.h"

template <typename T>
class GraphMap {
private:
    using  Node = Node<T>;
    using Nodes = std::set<Node*>;
    using   Map = std::map<Node*, Nodes>;

    Map _nodes;

public:
    using type = T;

    class NodeIterator
    {
    private:
        typename Map::const_iterator _it;
    public:
        explicit NodeIterator(typename Map::const_iterator it) : _it{it}{}

        Node* operator*()
        {
            return _it->first;
        }

        bool operator==(const NodeIterator& other)
        {
            return this->_it == other._it;
        }

        bool operator!=(const NodeIterator& other)
        {
            return !(*this == other);
        }

        NodeIterator& operator++()
        {
            ++_it;
            return *this;
        }
    };

    using EdgeIterator = typename Nodes::iterator;

    GraphMap() = default;

    ~GraphMap()
    {
        for (typename Map::const_iterator it = _nodes.begin(); it != _nodes.end(); ++it)
        {
            Node* node = it->first;
            delete node;
        }
    }

    GraphMap(const GraphMap&) = delete;
    GraphMap& operator=(const GraphMap&) = delete;

    std::pair<NodeIterator, NodeIterator> getNodes() const
    {
        return {NodeIterator{_nodes.begin()}, NodeIterator{_nodes.end()}};
    }

    std::pair<EdgeIterator, EdgeIterator> getEdges(Node *node) const
    {
        const Nodes& adjacent = _nodes.at(node);
        return {adjacent.begin(), adjacent.end()};
    }

    Node* addNode(const T& tag)
    {
        Node* node = new Node(tag);
        _nodes.insert({node, Nodes()});
        return node;
    }

    void removeNode(Node* node)
    {
        delete node;
        _nodes.erase(node);
    }

    void addEdge(Node* src, Node* dest)
    {
        _nodes[src].insert(dest);
    }

    void removeEdge(Node* src, Node* dest)
    {
        _nodes[src].erase(dest);
    }

    friend std::ostream& operator<<(std::ostream& out, const GraphMap& graph)
    {
        const Map& nodes = graph._nodes;
        for (typename Map::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
        {
            out << it->first->tag << ':';

            for (Node* node : it->second)
                out << ' ' << node->tag;

            out << std::endl;
        }

        return out;
    }
};


#endif //TUTORIALS_GRAPHMAP_H
