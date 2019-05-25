//
// Created by Andrei Tatarnikov on 2019-05-25.
//

#ifndef TUTORIALS_REDBLACKTREE_H
#define TUTORIALS_REDBLACKTREE_H

template <typename T>
class RedBlackTree {

public:

    enum Color {
        RED,
        BLACK
    };

    struct Node {
        Node* p     = nullptr;
        Node* left  = this;
        Node* right = this;
        Color color = BLACK;
        T     key;
    };

    static Node* const NIL;

    RedBlackTree() = default;

    ~RedBlackTree()
    {
        postorderWalk(_root, [](Node* node)
        {
            delete node;
        });
     }

    RedBlackTree(const RedBlackTree&) = delete;
    RedBlackTree& operator=(const RedBlackTree&) = delete;

    bool isEmpty() const
    {
        return _root == NIL;
    }

    size_t size() const
    {
        return _size;
    }

    Node* min() const
    {
        Node* node = _root;
        while (node->left != NIL)
            node = node->left;
        return node;
    }

    Node* max() const
    {
        Node* node = _root;
        while (node->right != NIL)
            node = node->right;
        return node;
    }

    Node* search(T key)
    {
        Node* node = _root;
        while (node != NIL && node->key != key)
        {
            if (key < node->key)
                node = node->left;
            else
                node = node->right;
        }
        return node;
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const RedBlackTree<U>& tree)
    {
        out << '{';
        bool first = true;
        RedBlackTree<U>::inorderWalk(tree._root, [&out, &first](Node* node)
        {
            if (!first)
                out << ", ";
            else
                first = false;
            out << node->key;
        });
        out << '}';
        return out;
    }

private:

    template<typename TAct>
    static void preorderWalk(Node* node, TAct action)
    {
        if (node != NIL)
        {
            action(node);
            preorderWalk(node->left, action);
            preorderWalk(node->right, action);
        }
    }

    template<typename TAct>
    static void inorderWalk(Node* node, TAct action)
    {
        if (node != NIL)
        {
            inorderWalk(node->left, action);
            action(node);
            inorderWalk(node->right, action);
        }
    }

    template<typename TAct>
    static void postorderWalk(Node* node, TAct action)
    {
        if (node != NIL)
        {
            postorderWalk(node->left, action);
            postorderWalk(node->right, action);
            action(node);
        }
    }

    Node*  _root = NIL;
    size_t _size = 0;
};

template <typename T>
typename RedBlackTree<T>::Node* const RedBlackTree<T>::NIL = new typename RedBlackTree<T>::Node();

#endif //TUTORIALS_REDBLACKTREE_H