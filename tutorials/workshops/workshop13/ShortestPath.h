//
// Created by Andrei Tatarnikov on 2019-06-09.
//

#ifndef TUTORIALS_SHORTESTPATH_H
#define TUTORIALS_SHORTESTPATH_H

#include <algorithm>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <queue>

#include "Node.h"
#include "TopologicalSort.h"

template <typename T>
struct PathVertex
{
    int      dist = std::numeric_limits<T>::max();
    Node<T>* prev = nullptr;
};

template <typename T>
bool relax(const Edge<T, int>& edge, std::map<Node<T>*, PathVertex<T>>& vertices)
{
    using Node   = Node<T>;
    using Vertex = PathVertex<T>;

    Node* u = edge.src;
    Node* v = edge.dest;

    Vertex& uV = vertices.at(u);
    Vertex& vV = vertices.at(v);

    if (vV.dist > uV.dist + edge.tag)
    {
        vV.dist = uV.dist + edge.tag;
        vV.prev = u;

        return true;
    }

    return false;
}

template <typename TGraph, typename T = typename TGraph::type>
std::map<Node<T>*, PathVertex<T>> initializeSingleSource(TGraph& graph, Node<T>* s)
{
    using         Node = Node<T>;
    using       Vertex = PathVertex<T>;
    using     Vertices = std::map<Node*,  Vertex>;
    using NodeIterator = typename TGraph::NodeIterator;

    Vertices vertices;

    std::pair<NodeIterator, NodeIterator> nodeRange = graph.getNodes();
    for (NodeIterator it = nodeRange.first; it != nodeRange.second; ++it)
        vertices.insert({*it, Vertex()});

    Vertex& sV = vertices.at(s);
    sV.dist = 0;

    return vertices;
}

template <typename TGraph, typename T = typename TGraph::type>
std::map<Node<T>*, PathVertex<T>> dagShortestPath(TGraph& graph, Node<T>* s)
{
    using         Node = Node<T>;
    using      DfsNode = std::pair<Node*, DfsVertex<T>>;
    using     Vertices = std::map<Node*,  PathVertex<T>>;
    using EdgeIterator = typename TGraph::EdgeIterator;

    Vertices vertices = initializeSingleSource(graph, s);

    std::list<DfsNode> sortedNodes = topologicalSort(graph);
    for (const DfsNode& node : sortedNodes)
    {
        Node* u = node.first;

        std::pair<EdgeIterator, EdgeIterator> edgeRange = graph.getEdges(u);
        for (EdgeIterator it = edgeRange.first; it != edgeRange.second; ++it)
            relax(*it, vertices);
    }

    return vertices;
}

template <typename TGraph, typename T = typename TGraph::type>
std::map<Node<T>*, PathVertex<T>> dijkstra(TGraph& graph, Node<T>* s)
{
    using     Node = Node<T>;
    using     Edge = Edge<T, int>;
    using   Vertex = PathVertex<T>;
    using Vertices = std::map<Node*,  Vertex>;
    using     Pair = std::pair<Node*, Vertex>;
    using    Queue = std::list<Node*>;

    using NodeIterator = typename TGraph::NodeIterator;
    using EdgeIterator = typename TGraph::EdgeIterator;

    Vertices vertices = initializeSingleSource(graph, s);

    // Q = G.V
    Queue queue;
    //for (typename Vertices::iterator it = vertices.begin(); it != vertices.end(); ++it)
     //   queue.push_back(Pair{it->first, &it->second});
    std::pair<NodeIterator, NodeIterator> nodeRange = graph.getNodes();
    for (NodeIterator it = nodeRange.first; it != nodeRange.second; ++it)
        queue.push_back(*it);

    struct MinDist
    {
        Vertices& _vs;

        explicit MinDist(Vertices& vs) : _vs{vs} {}

        bool operator()(Node* n1, Node* n2)
        {
            Vertex& v1 = _vs.at(n1);
            Vertex& v2 = _vs.at(n2);
            return v1.dist < v2.dist;
        }
    };

    while (!queue.empty())
    {
        // Extract-Min
        typename Queue::iterator minIt = min_element(queue.begin(), queue.end(), MinDist(vertices));

        Node *u = *minIt;
        queue.erase(minIt);

        std::pair<EdgeIterator, EdgeIterator> edgeRange = graph.getEdges(u);
        for (EdgeIterator it = edgeRange.first; it != edgeRange.second; ++it)
            relax(*it, vertices);
    }

    return vertices;
}

#endif //TUTORIALS_SHORTESTPATH_H
