//
// Created by Tatarnikov_A on 06.06.2019.
//

#include "BFS.h"
#include "DFS.h"
#include "ShortestPath.h"
#include "GraphMap.h"
#include "GraphMultimap.h"
#include "SCC.h"
#include "TopologicalSort.h"

#include <iostream>
#include <string>

void printBfsVertex(Node<int>* node, BfsVertex<int>* vertex)
{
    std::cout << node->tag;

    std::cout << ": dist=" << vertex->distance;
    std::cout << ", prev=";

    if (vertex->prev != nullptr)
        std::cout << vertex->prev->tag;
    else
        std::cout << "nullptr";

    std::cout << std::endl;
}

void printDfsVertex(Node<int>* node, DfsVertex<int>* vertex)
{
    std::cout << node->tag;

    std::cout << ": d=" << vertex->d;
    std::cout << ": f=" << vertex->f;
    std::cout << ", prev=";

    if (vertex->prev != nullptr)
        std::cout << vertex->prev->tag;
    else
        std::cout << "nullptr";

    std::cout << std::endl;
}

void printShortestPath(Node<int> *node, PathVertex<int> *vertex)
{
    std::cout << node->tag;
    std::cout << " dist=" << vertex->dist;
    std::cout << " prev=";

    if (vertex->prev != nullptr)
        std::cout << vertex->prev->tag;
    else
        std::cout << "nullptr";

    std::cout << std::endl;
}

template <typename TGraph>
void testBfsDfs()
{
    using  Graph = TGraph;
    using      T = typename TGraph::type;
    using   Node = Node<T>;

    Graph graph;

    Node* node1 = graph.addNode(1);
    Node* node2 = graph.addNode(2);
    Node* node3 = graph.addNode(3);
    Node* node4 = graph.addNode(4);
    Node* node5 = graph.addNode(5);
    Node* node6 = graph.addNode(6);
    Node* node7 = graph.addNode(7);
    Node* node8 = graph.addNode(8);

    graph.addEdge(node1, node2);
    graph.addEdge(node1, node3);
    graph.addEdge(node3, node4);
    graph.addEdge(node4, node5);
    graph.addEdge(node5, node8);
    graph.addEdge(node6, node7);
    graph.addEdge(node7, node2);
    graph.addEdge(node8, node6);

    std::cout << graph;
    std::cout << std::endl << "*************** Remove *************" << std::endl;

    graph.removeEdge(node7, node2);
    graph.removeNode(node7);

    std::cout << graph;

    std::cout << std::endl << "*************** BFS ***************:" << std::endl;
    std::map<Node*, BfsVertex<int>> bfsPaths = bfs(graph, node1, printBfsVertex);

    std::cout << std::endl << "***************" << std::endl;
    for (auto& p : bfsPaths)
        printBfsVertex(p.first, &p.second);

    std::cout << std::endl << "*************** DFS ***************:" << std::endl;
    std::map<Node*, DfsVertex<int>> dfsPaths = dfs(graph, node1, printDfsVertex);

    std::cout << std::endl << "***************" << std::endl;
    for (auto& p : dfsPaths)
        printDfsVertex(p.first, &p.second);

    std::cout << std::endl << "*************************************" << std::endl;
}

template <typename TGraph>
void testShortestPaths()
{
    using  Graph = TGraph;
    using      T = typename TGraph::type;
    using   Node = Node<T>;
    using Vertex = PathVertex<T>;

    Graph graph;

    Node* node1 = graph.addNode(1);
    Node* node2 = graph.addNode(2);
    Node* node3 = graph.addNode(3);
    Node* node4 = graph.addNode(4);
    Node* node5 = graph.addNode(5);

    graph.addEdge(node1, node2, 3);
    graph.addEdge(node1, node3, 6);
    graph.addEdge(node3, node4, 4);
    graph.addEdge(node4, node5, 1);
    graph.addEdge(node5, node2, 0);

    std::cout << graph;

    std::cout << std::endl << "********* Dag Shortest Path **********:" << std::endl;

    std::map<Node*, Vertex> paths2 = dagShortestPath(graph, node1);

    for (auto& p : paths2)
        printShortestPath(p.first, &p.second);

    std::cout << std::endl << "************** Dijkstra **************:" << std::endl;

    std::map<Node*, Vertex> paths = dijkstra(graph, node1);

    for (auto& p : paths)
        printShortestPath(p.first, &p.second);
}

template <typename TGraph>
void testTopologicalSort()
{
    using Graph  = TGraph;
    using T      = typename TGraph::type;
    using Node   = Node<T>;
    using Vertex = DfsVertex<T>;

    Graph graph;

    Node* shirt       = graph.addNode("shirt");
    Node* tie         = graph.addNode("tie");
    Node* jacket      = graph.addNode("jacket");
    Node* belt        = graph.addNode("belt");
    Node* watch       = graph.addNode("watch");
    Node* undershorts = graph.addNode("undershorts");
    Node* pants       = graph.addNode("pants");
    Node* shoes       = graph.addNode("shoes");
    Node* socks       = graph.addNode("socks");

    graph.addEdge(shirt,       tie    );
    graph.addEdge(tie,         jacket );
    graph.addEdge(shirt,       belt   );
    graph.addEdge(belt,        jacket );
    graph.addEdge(pants,       belt   );
    graph.addEdge(pants,       shoes  );
    graph.addEdge(undershorts, pants  );
    graph.addEdge(undershorts, shoes  );
    graph.addEdge(socks,       shoes  );

    std::cout << std::endl << "******** Topological Sort ***********" << std::endl;
    std::cout << graph;
    std::cout << std::endl << "*************************************" << std::endl;

    std::list<std::pair<Node*, Vertex>> path = topologicalSort(graph);
    for (const std::pair<Node*, Vertex>& p : path)
    {
        std::cout << p.first->tag;
        std::cout << " (" << p.second.d << '/' << p.second.f << ')';
        std::cout << std::endl;
    }
}

template <typename TGraph>
void testSCC()
{
    using Graph  = TGraph;
    using T      = typename TGraph::type;
    using Node   = Node<T>;

    Graph graph;

    Node* node1 = graph.addNode(1);
    Node* node2 = graph.addNode(2);
    Node* node3 = graph.addNode(3);
    Node* node4 = graph.addNode(4);
    Node* node5 = graph.addNode(5);
    Node* node6 = graph.addNode(6);

    graph.addEdge(node1, node2);
    graph.addEdge(node2, node3);
    graph.addEdge(node3, node4);
    graph.addEdge(node4, node2);
    graph.addEdge(node4, node5);
    graph.addEdge(node5, node6);
    graph.addEdge(node6, node5);

    std::cout << std::endl << "*************************************" << std::endl;

    std::cout << graph;

    std::cout << std::endl << "**************** SCC ****************:" << std::endl;

    std::vector<std::vector<Node*>> connected = scc(graph);
    for (const std::vector<Node*>& nodes : connected)
    {
        std::cout << std::endl;
        for (Node* node : nodes)
        {
            std::cout << node->tag << " ";
        }
    }
}

int main()
{
    testBfsDfs<GraphMultimap<int>>();
    testBfsDfs<GraphMap<int>>();

    testShortestPaths<GraphMultimap<int>>();

    testTopologicalSort<GraphMultimap<std::string>>();
    testTopologicalSort<GraphMap<std::string>>();

    testSCC<GraphMultimap<int>>();
    testSCC<GraphMap<int>>();

    return 0;
}
