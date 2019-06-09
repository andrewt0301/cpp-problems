//
// Created by Tatarnikov_A on 06.06.2019.
//

#ifndef TUTORIALS_GRAPHMULTIMAP_H
#define TUTORIALS_GRAPHMULTIMAP_H

#include "Node.h"

#include <iostream>
#include <map>

template <typename T>
class GraphMultimap
{
private:
    using     Node = Node<T>;
    using Multimap = std::multimap<Node*, Node*>;

    using       iterator = typename Multimap::iterator;
    using const_iterator = typename Multimap::const_iterator;

    Multimap _nodes;

public:

    class NodeIterator
    {
    private:
        iterator  _it;
        iterator _end;
    public:
        NodeIterator(iterator it, iterator end) : _it{it}, _end{end} {}

        Node* operator*()
        {
            return _it->first;
        }

        Node* operator->()
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
        iterator _it;
    public:
        EdgeIterator(iterator it) : _it{it}{}

        Node* operator*()
        {
            return _it->second;
        }

        Node* operator->()
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
        for (iterator it = _nodes.begin(); it != _nodes.end(); ++it)
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

    std::pair<EdgeIterator, EdgeIterator> getAdjacent(Node *node)
    {
        std::pair<iterator, iterator> range = _nodes.equal_range(node);

        iterator begin = range.first;
        iterator   end = range.second;

        return {EdgeIterator{begin}, EdgeIterator{end}};
    }

    std::pair<NodeIterator, NodeIterator> getNodes()
    {
        iterator begin = _nodes.begin();
        iterator   end = _nodes.end();

        return {NodeIterator{begin, end}, NodeIterator{end, end}};
    }

    Node* addNode(const T& tag)
    {
        Node* node = new Node(tag);
        _nodes.insert({node, nullptr});
        return node;
    }

    void removeNode(Node* node)
    {
        std::pair<iterator, iterator> range = getAdjacent(node);
        _nodes.erase(range.first, range.second);
        delete node;
    }

    void addEdge(Node* src, Node* dest)
    {
        iterator it = _nodes.find(src);
        if (it != _nodes.end() && it->second == nullptr)
            it ->second = dest;
        else
            _nodes.insert({src, dest});
    }

    void removeEdge(Node* src, Node* dest)
    {
        std::pair<iterator, iterator> range = _nodes.equal_range(src);
        for (iterator it = range.first; it != range.second;)
        {
            if (it->second == dest)
                it = _nodes.erase(it);
            else
                ++it;
        }
    }

    template <typename TVisitor>
    void bfs(Node* src, TVisitor visitor)
    {
        // TODO
    }

    template <typename TVisitor>
    void dfs(Node* src, TVisitor visitor)
    {
        // TODO
    }

    friend std::ostream& operator<<(std::ostream& out, const GraphMultimap& graph)
    {
        const Multimap& nodes = graph._nodes;

        Node* node = nullptr;
        for (const_iterator it = nodes.begin(); it != nodes.end(); ++it)
        {
            if (it->first != node)
            {
                if (node != nullptr)
                    out << std::endl;

                node = it->first;
                out << node->tag << ':';
            }

            if (it->second != nullptr)
                out << " " << it->second->tag;

        }

        return out;
    }

};

template <typename T, typename TVisitor>
void bfs(const GraphMultimap<T>& graph, Node<T>* src, TVisitor visitor)
{
    // TODO
}


#endif //TUTORIALS_GRAPHMULTIMAP_H
