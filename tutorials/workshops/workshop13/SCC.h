//
// Created by Tatarnikov_A on 11.06.2019.
//

#ifndef TUTORIALS_SCC_H
#define TUTORIALS_SCC_H

#include <algorithm>
#include <vector>

template <
    typename TGraph,
    typename T = typename TGraph::type
>
std::vector<Node<T>*> getDfsSortedNodes(TGraph& graph)
{
    using Node   = Node<T>;
    using Vertex = DfsVertex<T>;
    using Pair   = std::pair<Node*, Vertex>;

    std::map<Node*, Vertex> paths = dfs(graph, [](Node*, Vertex*) {});

    std::vector<Pair> vertices(paths.begin(), paths.end());

    std::sort(vertices.begin(), vertices.end(), [](const Pair& p1, const Pair& p2)
    {
        return p1.second.f > p2.second.f;
    });

    std::vector<Node*> nodes(vertices.size());
    std::transform(vertices.begin(), vertices.end(), nodes.begin(), [](const Pair& p) { return p.first; });

    return nodes;
}

template <
    typename TGraph,
    typename T = typename TGraph::type
>
std::vector<std::vector<Node<T>*>> scc(TGraph& graph)
{
    using Node   = Node<T>;
    using Nodes  = std::vector<Node*>;
    using Vertex = DfsVertex<T>;

    using NodeIterator = typename TGraph::NodeIterator;
    using EdgeIterator = typename TGraph::EdgeIterator;

    Nodes nodes = getDfsSortedNodes(graph);
    graph.transpose();

    std::map<Node*, Vertex> vertices;
    for (Node* node : nodes)
        vertices.insert({node, Vertex()});

    std::vector<Nodes> connected;

    int time = 0;
    for (Node* u : nodes)
    {
        Vertex& uV = vertices.at(u);

        if (uV.color == Color::WHITE)
        {
            Nodes comps;

            time = dfsVisit(graph, vertices, u, uV, time, [&comps](Node* node, Vertex* vertex)
            {
                comps.push_back(node);
            });

            if (comps.size() > 1)
                connected.push_back(comps);
        }
    }

    return connected;
}

#endif //TUTORIALS_SCC_H
