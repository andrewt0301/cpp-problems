//
// Created by Tatarnikov_A on 11.06.2019.
//

#ifndef TUTORIALS_SCC_H
#define TUTORIALS_SCC_H

#include <algorithm>

template <
    typename TGraph,
    typename T = typename TGraph::type
>
void scc(TGraph& graph)
{
    using Graph  = TGraph;
    using Node   = Node<T>;
    using Vertex = DfsVertex<T>;
    using Pair   = std::pair<Node*, Vertex>;

   // std::map<Node*, Vertex> paths =
    dfs(graph, [](Node* n, Vertex* v) {
        std::cout << n->tag << std::endl;
    });

    //std::vector<Pair> vertices(paths.begin(), paths.end());
   /* std::sort(vertices.begin(), vertices.end(), [](const Pair& p1, const Pair& p2)
    {
        //return p1.second.f > p2.second.f;
        return false;
    });*/

    // TODO
}

#endif //TUTORIALS_SCC_H
