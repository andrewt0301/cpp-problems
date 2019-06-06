//
// Created by Tatarnikov_A on 06.06.2019.
//

#ifndef TUTORIALS_GRAPHMAP_H
#define TUTORIALS_GRAPHMAP_H

#include "Node.h"

#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <vector>

template <typename T>
class GraphMap {
private:
    using Node = Node<T>;
    using  Set = std::set<Node*>;
    using  Map = std::map<Node*, Set>;

    Map _nodes;

public:
    GraphMap() = default;

    ~GraphMap()
    {
        for (typename Map::const_iterator it = _nodes.begin(); it != _nodes.end(); ++it)
            delete it->first;
    }

    GraphMap(const GraphMap&) = delete;
    GraphMap& operator=(const GraphMap&) = delete;

    Node* addNode(const T& tag)
    {
        Node* node = new Node(tag);
        _nodes.insert({node, Set()});
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

    template <typename TVisitor>
    void bfs(Node* s, TVisitor visitor)
    {
        struct Vertex
        {
            Color  color = Color::WHITE;
            int distance = -1;
            Node*   prev = nullptr;
        };

        std::map<Node*, Vertex> vertices;
        for (typename Map::const_iterator it = _nodes.begin(); it != _nodes.end(); ++it)
            vertices.insert({it->first, Vertex()});

        Vertex& sV  = vertices[s];
        sV.color    = Color::GRAY;
        sV.distance = 0;
        sV.prev     = nullptr;

        std::queue<Node*> queue;
        queue.push(s);

        while (!queue.empty())
        {
            Node* u = queue.front();
            queue.pop();
            Vertex& uV  = vertices[u];

            visitor(u, uV.distance, uV.prev);

            for (Node* v : _nodes[u])
            {
                Vertex& vV  = vertices[v];
                if (vV.color == Color::WHITE)
                {
                    vV.color = Color::GRAY;
                    vV.distance = uV.distance + 1;
                    vV.prev = u;

                    queue.push(v);
                }
            }

            uV.color = Color::BLACK;
        }
    }

    template <typename TVisitor>
    void dfs(Node* src, TVisitor visitor)
    {
        // TODO
    }

    friend std::ostream& operator<<(std::ostream& out, const GraphMap& graph)
    {
        const Map& nodes = graph._nodes;
        for (typename Map::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
        {
            out << it->first->tag << ": ";
            bool start = true;
            for (Node* node : it->second)
            {
                if (start)
                    start = false;
                else
                    out << ", ";
                out << node->tag;
            }

            out << std::endl;
        }

        return out;
    }
};


#endif //TUTORIALS_GRAPHMAP_H
