//
// Created by Tatarnikov_A on 06.06.2019.
//

#ifndef TUTORIALS_GRAPHMULTIMAP_H
#define TUTORIALS_GRAPHMULTIMAP_H

#include "Node.h"

#include <iostream>
#include <unordered_map>

template <typename T, typename U = int>
class GraphMultimap
{
private:
    using     Node = Node<T>;
    using     Edge = Edge<T, U>;
    using    Graph = std::unordered_multimap<Node*, Edge>;
    using Iterator = typename Graph::iterator;

    Graph _graph;

public:
    using type = T;

    class NodeIterator
    {
    private:
        Iterator  _it;
        Iterator _end;
    public:
        NodeIterator(Iterator it, Iterator end) : _it{it}, _end{end} {}

        Node* operator*()
        {
            return _it->first;
        }

        bool operator==(const NodeIterator& other)
        {
            return this->_it == other._it && this->_end == other._end;
        }

        bool operator!=(const NodeIterator& other)
        {
            return !(*this == other);
        }

        NodeIterator& operator++()
        {
            Node* node = _it->first;
            while (_it != _end && _it->first == node)
               ++_it;

            return *this;
        }
    };

    class EdgeIterator
    {
    private:
        Iterator _it;
    public:
        explicit EdgeIterator(Iterator it) : _it{it}{}

        Edge& operator*()
        {
            return _it->second;
        }

        bool operator==(const EdgeIterator& other)
        {
            return this->_it == other._it;
        }

        bool operator!=(const EdgeIterator& other)
        {
            return !(*this == other);
        }

        EdgeIterator& operator++()
        {
            ++_it;
            return *this;
        }
    };

    GraphMultimap() = default;

    ~GraphMultimap()
    {
        Node* node = nullptr;
        for (Iterator it = _graph.begin(); it != _graph.end(); ++it)
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

    std::pair<NodeIterator, NodeIterator> getNodes()
    {
        Iterator begin = _graph.begin();
        Iterator   end = _graph.end();

        return {NodeIterator{begin, end}, NodeIterator{end, end}};
    }

    std::pair<EdgeIterator, EdgeIterator> getEdges(Node *node)
    {
        std::pair<Iterator, Iterator> range = _graph.equal_range(node);

        Iterator& begin = range.first;
        Iterator&   end = range.second;

        if (begin != end && begin->second == nullptr)
            ++begin;

        return {EdgeIterator{begin}, EdgeIterator{end}};
    }

    Node* addNode(const T& tag)
    {
        Node* node = new Node(tag);
        _graph.insert({node, Edge{}});
        return node;
    }

    void removeNode(Node* node)
    {
        // Delete all outgoing and incoming edges.
        Node *prevSrc = nullptr;
        for (Iterator it = _graph.begin(); it != _graph.end();)
        {
            Node* src = it->first;

            // Outgoing.
            if (src == node)
            {
                it = _graph.erase(it);
            }
            // Incoming.
            else if (it->second == node)
            {
                if (src != prevSrc)
                    it->second = Edge{};
                else
                    it = _graph.erase(it);
            }
            // Unrelated.
            else
            {
                ++it;
            }

            prevSrc = src;
        }

        // Delete node.
        delete node;
    }

    void addEdge(Node* src, Node* dest, const U& tag = 0)
    {
        Iterator it = _graph.find(src);

        Edge edge{src, dest, tag};

        if (it != _graph.end() && it->second == nullptr)
            it->second = edge;
        else
            _graph.insert({src, edge});
    }

    void removeEdge(Node* src, Node* dest)
    {
        std::pair<Iterator, Iterator> range = _graph.equal_range(src);
        for (Iterator it = range.first; it != range.second;)
        {
            if (it->second == dest)
                it = _graph.erase(it);
            else
                ++it;
        }
    }

    void transpose()
    {
        Graph graph;

        for (Iterator it = _graph.begin(); it != _graph.end(); ++it)
        {
            Edge& edge = it->second;
            Node* dest = it->first;
            Node*  src = edge.dest;

            if (graph.find(dest) == graph.end())
                graph.insert({dest, Edge{}});

            if (src != nullptr)
            {
                Iterator srcIt = graph.find(src);
                Edge newEdge{src, dest, edge.tag};

                if (srcIt != graph.end() && srcIt->second == nullptr)
                    srcIt->second = newEdge;
                else
                    graph.insert({src, newEdge});
            }
        }

        _graph.clear();
        _graph.swap(graph);
    }

    friend std::ostream& operator<<(std::ostream& out, GraphMultimap& graph)
    {
        Graph& nodes = graph._graph;

        Node* prev = nullptr;
        for (Iterator it = nodes.begin(); it != nodes.end(); ++it)
        {
            if (it->first != prev)
            {
                if (prev != nullptr)
                    out << std::endl;

                prev = it->first;
                out << prev->tag << ':';
            }

            if (it->second != nullptr)
            {
                Edge& edge = it->second;
                Node* node = edge.dest;
                out << ' ' << node->tag << '[' << edge.tag << ']';
            }

        }

        return out;
    }

};

#endif //TUTORIALS_GRAPHMULTIMAP_H
