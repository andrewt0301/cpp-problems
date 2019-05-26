//
// Created by Andrei Tatarnikov on 2019-05-25.
//

#ifndef TUTORIALS_REDBLACKTREE_H
#define TUTORIALS_REDBLACKTREE_H

template <typename T>
class RedBlackTree
{
public:

    enum Color
    {
        RED,
        BLACK
    };

    struct Node;
    static Node* const NIL;

    struct Node
    {
        Node* p     = NIL;
        Node* left  = NIL;
        Node* right = NIL;
        Color color = BLACK;
        T     key;
    };

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
        return min(_root);
    }

    static Node* min(Node* node)
    {
        while (node->left != NIL)
            node = node->left;
        return node;
    }

    static Node* successor(Node* node)
    {
        if (node->right != NIL)
            return min(node->right);

        Node* parent = node->p;
        while (parent != NIL && node == parent->right)
        {
            node = parent;
            parent = node->p;
        }

        return parent;
    }

    Node* max() const
    {
        return max(_root);
    }

    static Node* max(Node* node)
    {
        while (node->right != NIL)
            node = node->right;
        return node;
    }

    static Node* predecessor(Node* node)
    {
        if (node->left != NIL)
            return max(node->left);

        Node* parent = node->p;
        while (parent != NIL && node == parent->left)
        {
            node = parent;
            parent = node->p;
        }

        return parent;
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

    void insert(T key)
    {
        Node* node = new Node();
        node->key = key;

        insert(node);
        _size++;
    }

    void insert(Node* newNode)
    {
        Node* parent = NIL;
        Node* node = _root;

        while (node != NIL)
        {
            parent = node;
            if (newNode->key < node->key)
                node = node->left;
            else
                node = node->right;
        }

        newNode->p = parent;
        if (parent == NIL)
            _root = newNode;
        else if (newNode->key < parent->key)
            parent->left = newNode;
        else
            parent->right = newNode;
    }

    void transplant(Node* oldNode, Node* newNode)
    {
        if (oldNode->p == NIL)
            _root = newNode;
        else if (oldNode == oldNode->p->left)
            oldNode->p->left = newNode;
        else
            oldNode->p->right = newNode;

        if (newNode != NIL)
            newNode->p = oldNode->p;
    }

    void remove(T key)
    {
        Node* node = search(key);
        if (node != NIL)
        {
            remove(node);
            delete node;
            _size--;
        }
    }

    void remove(Node* node)
    {
        if (node->left == NIL)
            transplant(node, node->right);
        else if (node->right == NIL)
            transplant(node, node->left);
        else
        {
            Node* sucessor = min(node->right);
            if (sucessor->p != node)
            {
                transplant(sucessor, sucessor->right);
                sucessor->right = node->right;
                sucessor->right->p = sucessor;
            }
            transplant(node, sucessor);
            sucessor->left = node->left;
            sucessor->left->p = sucessor;
        }
    }

    void leftRotate(Node* x)
    {
        Node* y = x->right;
        x->right = y->left;

        if (y->left != NIL)
            y->left->p = x;

        y->p = x->p;
        if (x->p == NIL)
            _root = y;
        else if (x == x->left)
            x->p->left = y;
        else
            x->p->right = y;

        y->left = x;
        x->p = y;
    }

    void rightRotate(Node* x)
    {
        Node* y = x->left;
        x->left = y->right;

        if (y->right != NIL)
            y->right->p = x;

        y->p = x->p;
        if (x->p == NIL)
            _root = y;
        else if (x == x->left)
            x->p->left = y;
        else
            x->p->right = y;

        y->right = x;
        x->p = y;
    }

    void insertRB(T key)
    {
        Node* node = new Node();

        node->key = key;
        node->color = RED;

        insert(node);
        fixupInsertRB(node);

        _size++;
    }

    void fixupInsertRB(Node* z)
    {
        while (z->p->color == RED)
        {
            // If parent is left child.
            if (z->p == z->p->p->left)
            {
                // Uncle.
                Node* y = z->p->p->right;

                // Case 1.
                if (y->color == RED)
                {
                    z->p->color = BLACK;
                    y->color = BLACK;
                    z->p->p->color = RED;
                    z = z->p->p;
                }
                // Case 2.
                else if (z == z->p->right)
                {
                    z = z->p;
                    leftRotate(z);
                }
                // Case 3.
                z->p->color = BLACK;
                z->p->p->color = RED;
                rightRotate(z->p->p);
            }
            // If parent is right child.
            else
            {
                // Uncle.
                Node* y = z->p->p->left;

                // Case 4.
                if (y->color == RED)
                {
                    z->p->color = BLACK;
                    y->color = BLACK;
                    z->p->p->color = RED;
                    z = z->p->p;
                }
                // Case 5.
                else if (z == z->p->left)
                {
                    z = z->p;
                    rightRotate(z);
                }
                // Case 6.
                z->p->color = BLACK;
                z->p->p->color = RED;
                leftRotate(z->p->p);
            }
        }
        _root->color = BLACK;
    }

    void removeRB(Node* node)
    {
        Color origColor = node->color;
        Node* trans = NIL;

        if (node->left == NIL)
        {
            trans = node->right;
            transplant(node, trans);
        }
        else if (node->right == NIL)
        {
            trans = node->left;
            transplant(node, trans);
        }
        else
        {
            Node* successor = min(node->right);

            origColor = successor->color;
            trans = successor->right;

            if (successor->p == node)
            {
                trans->p = successor;
            }
            else
            {
                transplant(successor, trans);
                successor->right = node->right;
                successor->right->p = successor;
            }

            transplant(node, successor);
            successor->left = node->left;
            successor->left->p = successor;
            successor->color = node->color;
        }

        if (origColor == BLACK)
            fixupInsertRB(trans);
    }

    void fixupRemoveRB(Node* x)
    {
        while (x != _root && x->color == BLACK)
        {
            if (x == x->p->left)
            {
                Node* w = x->p->right;

                // Case 1.
                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->p->color = RED;
                    leftRotate(x->p);
                    w = x->p->right;
                }

                // Case 2.
                if (w->left->color == BLACK && w->right->color == BLACK)
                {
                    w->color = RED;
                    x = x->p;
                }
                // Case 3.
                else if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->p->right;
                }
                // Case 4.
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->p);
                x = _root;
            }
            else
            {
                Node* w = x->p->left;

                // Case 4.
                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->p->color = RED;
                    rightRotate(x->p);
                    w = x->p->left;
                }

                // Case 5.
                if (w->right->color == BLACK && w->left->color == BLACK)
                {
                    w->color = RED;
                    x = x->p;
                }
                // Case 3.
                else if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->p->left;
                }
                // Case 4.
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->p);
                x = _root;
            }
        }
        x->color = BLACK;
    }

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

    void printAsRBTree(std::ostream& out)
    {
        printAsRBTree(out, _root, 0);
    }

    static void printAsRBTree(std::ostream& out, Node* node, size_t depth)
    {
        if (node == NIL)
            return;

        printAsRBTree(out, node->right, depth + 1);

        out << "\r\n";
        for (size_t i = 0; i < depth; ++i)
            out << "     ";

        out << node->key;
        out << "(";
        out << (node->color == RED ? 'R' : 'B');
        out << ")";

        printAsRBTree(out, node->left,  depth + 1);
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
    Node*  _root = NIL;
    size_t _size = 0;
};

template <typename T>
typename RedBlackTree<T>::Node* const RedBlackTree<T>::NIL = new typename RedBlackTree<T>::Node();

#endif //TUTORIALS_REDBLACKTREE_H
