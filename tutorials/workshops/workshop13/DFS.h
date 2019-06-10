//
// Created by Andrei Tatarnikov on 2019-06-09.
//

#ifndef TUTORIALS_DFS_H
#define TUTORIALS_DFS_H

#include <map>

#include "Node.h"

template <typename T>
struct DfsVertex
{
    Color   color = Color::WHITE;
    Node<T>* prev = nullptr;
    int         d = -1;
    int         f = -1;
};

template <typename TGraph, typename TVisitor, typename T>
std::map<Node<T>*, DfsVertex<T>> dfs(TGraph& graph, Node<T>* u, TVisitor visitor)
{
    using Node = Node<T>;
    using Vertex = DfsVertex<T>;

    using NodeIterator = typename TGraph::NodeIterator;
    using EdgeIterator = typename TGraph::EdgeIterator;

    std::pair<NodeIterator, NodeIterator> nodeRange = graph.getNodes();

    std::map<Node*, Vertex> vertices;
    for (NodeIterator it = nodeRange.first; it != nodeRange.second; ++it)
        vertices.insert({*it, Vertex()});

    Vertex &uV = vertices.at(u);
    dfsVisit(graph, vertices, u, uV, 0, visitor);

    return vertices;
}

template <
    typename TGraph,
    typename TVisitor,
    typename T = typename TGraph::type
>
std::map<Node<T>*, DfsVertex<T>> dfs(TGraph& graph, TVisitor visitor)
{
    using   Node = Node<T>;
    using Vertex = DfsVertex<T>;

    using NodeIterator = typename TGraph::NodeIterator;
    using EdgeIterator = typename TGraph::EdgeIterator;

    std::pair<NodeIterator, NodeIterator> nodeRange = graph.getNodes();

    std::map<Node*, Vertex> vertices;
    for (NodeIterator it = nodeRange.first; it != nodeRange.second; ++it)
        vertices.insert({*it, Vertex()});

    int time = 0;
    for (NodeIterator it = nodeRange.first; it != nodeRange.second; ++it)
    {
        Node* u = *it;
        Vertex& uV = vertices.at(u);

        if (uV.color == Color::WHITE)
            time = dfsVisit(graph, vertices, u, uV, time, visitor);
    }

    return vertices;
}

template <typename T, typename TGraph, typename TVisitor>
int dfsVisit(
        TGraph& graph,
        std::map<Node<T>*, DfsVertex<T>>& vertices,
        Node<T>* u,
        DfsVertex<T> &uV,
        int time,
        TVisitor visitor
    )
{
    using Node = Node<T>;
    using Vertex = DfsVertex<T>;

    using NodeIterator = typename TGraph::NodeIterator;
    using EdgeIterator = typename TGraph::EdgeIterator;

    uV.d = ++time;
    uV.color = Color::GRAY;

    std::pair<EdgeIterator, EdgeIterator> edgeRange = graph.getEdges(u);
    for (EdgeIterator it = edgeRange.first; it != edgeRange.second; ++it)
    {
        Node *v = *it;
        Vertex &vV = vertices.at(v);

        if (vV.color == Color::WHITE)
        {
            vV.prev = u;
            time = dfsVisit(graph, vertices, v, vV, time, visitor);
        }
    }

    uV.color = Color::BLACK;
    uV.f = ++time;

    visitor(u, &uV);

    return time;
}

#endif //TUTORIALS_DFS_H
