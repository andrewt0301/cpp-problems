//
// Created by Andrei Tatarnikov on 2019-06-09.
//

#ifndef TUTORIALS_BFS_H
#define TUTORIALS_BFS_H

#include <queue>
#include <unordered_map>

#include "Node.h"

template <typename T>
struct BfsVertex
{
    Color     color = Color::WHITE;
    int    distance = -1;
    Node<T>*   prev = nullptr;
};

template <typename T, typename TGraph, typename TVisitor>
std::unordered_map<Node<T>*, BfsVertex<T>> bfs(TGraph& graph, Node<T>* s, TVisitor visitor)
{
    using   Node = Node<T>;
    using Vertex = BfsVertex<T>;

    using NodeIterator = typename TGraph::NodeIterator;
    using EdgeIterator = typename TGraph::EdgeIterator;

    std::unordered_map<Node*, Vertex> vertices;

    std::pair<NodeIterator, NodeIterator> nodeRange = graph.getNodes();
    for (NodeIterator it = nodeRange.first; it != nodeRange.second; ++it)
        vertices.insert({*it, Vertex()});

    Vertex& sV  = vertices.at(s);

    sV.color    = Color::GRAY;
    sV.distance = 0;
    sV.prev     = nullptr;

    std::queue<Node*> queue;
    queue.push(s);

    while (!queue.empty())
    {
        Node    *u = queue.front();
        Vertex &uV = vertices[u];

        queue.pop();

        visitor(u, &uV);

        std::pair<EdgeIterator, EdgeIterator> edgeRange = graph.getEdges(u);
        for (EdgeIterator it = edgeRange.first; it != edgeRange.second; ++it)
        {
            Node *v = *it;
            Vertex &vV = vertices.at(v);

            if (vV.color == Color::WHITE)
            {
                vV.color    = Color::GRAY;
                vV.distance = uV.distance + 1;
                vV.prev     = u;

                queue.push(v);
            }
        }

        uV.color = Color::BLACK;
    }

    return vertices;
}

#endif //TUTORIALS_BFS_H
