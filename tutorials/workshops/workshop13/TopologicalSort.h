//
// Created by Tatarnikov_A on 10.06.2019.
//

#ifndef TUTORIALS_TOPOLOGICALSORT_H
#define TUTORIALS_TOPOLOGICALSORT_H

#include <list>

#include "DFS.h"

template <
    typename TGraph,
    typename TNode   = Node<typename TGraph::type>,
    typename TVertex = DfsVertex<typename TGraph::type>,
    typename TPair   = std::pair<TNode*, TVertex>
>
std::list<TPair> topologicalSort(TGraph& graph)
{
    std::list<TPair> vertices;

    dfs(graph, [&vertices](TNode* node, TVertex* vertex)
    {
        vertices.push_front(TPair{node, *vertex});
    });

    return vertices;
}

#endif //TUTORIALS_TOPOLOGICALSORT_H
