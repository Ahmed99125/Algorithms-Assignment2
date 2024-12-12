#include <iostream>
using namespace std;



template <typename T>
class RedBlackTree
{
private:
    class Node
    {
    public:
        T data;
        Node *parent = nullptr;
        Node *leftChild = nullptr;
        Node *rightChild = nullptr;
        int color; // 0 for Red and 1 for Black

        Node(T &value, int col = 0) : data(value), color(col) {} // Default color is Red (0)

        Node *getSibling()
        {
            if (isleftChild())
                return parent->rightChild;
            else
                return parent->leftChild;
        }

        bool isleftChild()
        {
            if (parent->leftChild == this)
                return true;
            else
                return false;
        }

        bool hasBlackChildren()
        {
            bool leftChildBlack;
            if (leftChild == nullptr || leftChild->color == 1)
                leftChildBlack = true;
            else
                leftChildBlack = false;

            bool rightChildBlack;
            if (rightChild == nullptr || rightChild->color == 1)
                rightChildBlack = true;
            else
                rightChildBlack = false;

            return leftChildBlack && rightChildBlack;
        }
    };

    Node *root = nullptr;

    void rotateleft(Node *node)
    {
        Node *newRoot = node->rightChild;
        Node *newrightChild = newRoot->leftChild;

        if (node->parent == nullptr)
            root = newRoot;
        else if (node->isleftChild())
            node->parent->leftChild = newRoot;
        else
            node->parent->rightChild = newRoot;
        newRoot->leftChild = node;
        newRoot->parent = node->parent;
        node->parent = newRoot;
        node->rightChild = newrightChild;
        if (newrightChild != nullptr)
            newrightChild->parent = node;
    }

    void rotateright(Node *node)
    {
        Node *newRoot = node->leftChild;
        Node *newleftChild = newRoot->rightChild;

        if (node->parent == nullptr)
            root = newRoot;
        else if (node->isleftChild())
            node->parent->leftChild = newRoot;
        else
            node->parent->rightChild = newRoot;
        newRoot->rightChild = node;
        newRoot->parent = node->parent;
        node->parent = newRoot;
        node->leftChild = newleftChild;
        if (newleftChild != nullptr)
            newleftChild->parent = node;
    }

    Node *getNode(Node *node, T &value)
    {
        if (node == nullptr)
            return nullptr;
        if (value < node->data)
        {
            return getNode(node->leftChild, value);
        }
        if (node->data < value)
        {
            return getNode(node->rightChild, value);
        }
        return node;
    }

    Node *getParent(Node *node, T &value)
    {
        if (value < node->data)
        {
            if (node->leftChild == nullptr)
                return node;
            return getParent(node->leftChild, value);
        }
        if (node->rightChild != nullptr)
        {
            return getParent(node->rightChild, value);
        }
        return node;
    }

    Node *insertNode(T &value)
    {
        Node *newNode = new Node(value);

        if (root == nullptr)
        {
            root = newNode;
            return root;
        }
        Node *parent = getParent(root, value);
        newNode->parent = parent;
        if (value < parent->data)
            parent->leftChild = newNode;
        else
            parent->rightChild = newNode;
        return newNode;
    }

    void handleColorsAndRotations(Node *node)
    {
        if (node == root || node->parent->color == 1) // 1 is Black
        {
            root->color = 1; // Color the root Black
            return;
        }
        Node *parent = node->parent;
        Node *grandParent = parent->parent;
        Node *uncle = parent->isleftChild() ? grandParent->rightChild : grandParent->leftChild;

        if (uncle && uncle->color == 0) // 0 is Red
        {
            parent->color = 1;      // Color parent Black
            uncle->color = 1;       // Color uncle Black
            grandParent->color = 0; // Color grandparent Red
            handleColorsAndRotations(grandParent);
            return;
        }
        if (parent->isleftChild())
        {
            if (!node->isleftChild())
            {
                rotateleft(parent);
                swap(node, parent);
            }
            rotateright(grandParent);
        }
        else
        {
            if (node->isleftChild())
            {
                rotateright(parent);
                swap(node, parent);
            }
            rotateleft(grandParent);
        }
        parent->color = 1;      // Color parent Black
        grandParent->color = 0; // Color grandparent Red
    }

    Node *transplant(Node *node)
    {
        if (!node->leftChild && !node->rightChild)
            return node;
        if (!node->leftChild)
        {
            node->data = node->rightChild->data;
            return node->rightChild;
        }
        Node *current = node->leftChild;
        while (current->rightChild)
        {
            current = current->rightChild;
        }
        node->data = current->data;
        if (current->leftChild)
        {
            current->data = current->leftChild->data;
            return current->leftChild;
        }
        return current;
    }

    Node *getFarNephew(Node *sib)
    {
        if (sib->isleftChild())
            return sib->leftChild;
        else
            return sib->rightChild;
    }

    void balanceTree(Node *node)
    {
        if (node == root)
        {
            return;
        }
        Node *sib = node->getSibling();
        if (sib->color == 0) // 0 is Red
        {
            node->parent->color = 0; // Color parent Red
            sib->color = 1;          // Color sib Black
            if (node->isleftChild())
            {
                rotateleft(node->parent);
            }
            else
            {
                rotateright(node->parent);
            }
            balanceTree(node);
            return;
        }
        if (sib->color == 1 && sib->hasBlackChildren())
        {
            sib->color = 0;               // Color sib Red
            if (node->parent->color == 0) // If parent is Red
            {
                node->parent->color = 1; // Color parent Black
            }
            else
            {
                balanceTree(node->parent);
            }
            return;
        }
        Node *farNephew = getFarNephew(sib);
        if (!farNephew || farNephew->color == 1) // If far nephew is Black
        {
            sib->color = 0; // Color sib Red
            if (sib->isleftChild())
            {
                sib->rightChild->color = 1; // Color rightChild child Black
                rotateleft(sib);
            }
            else
            {
                sib->leftChild->color = 1; // Color leftChild child Black
                rotateright(sib);
            }
            farNephew = sib;
            sib = node->getSibling();
        }
        if (node->parent->color == 0) // If parent is Red
        {
            sib->color = 0;          // Color sib Red
            node->parent->color = 1; // Color parent Black
        }
        if (node->isleftChild())
        {
            rotateleft(node->parent);
        }
        else
        {
            rotateright(node->parent);
        }
        farNephew->color = 1; // Color far nephew Black
    }

    void fixUP(Node *node)
    {
        if (node == root)
        {
            delete root;
            root = nullptr;
            return;
        }
        if (node->color == 1) // If node is Black
        {
            balanceTree(node);
        }
        if (node->isleftChild())
            node->parent->leftChild = nullptr;
        else
            node->parent->rightChild = nullptr;
        delete node;
    }

    void print(Node *node, int depth = 0)
    {
        if (node == nullptr)return;


        string spaces ="";
        for(int i =0 ; i< depth; i++){
            spaces += "  ";
        }
        cout << spaces << node->data << "(" << (node->color == 0 ? "Red" : "Black")<< ") \n";
        print(node->leftChild, depth + 1);
        print(node->rightChild, depth + 1);
    }

public:
    void insert(T &value)
    {
        Node *newNode = insertNode(value);
        handleColorsAndRotations(newNode);
    }

    void remove(T &value)
    {
        Node *node = getNode(root, value);
        if (node == nullptr)
            return;
        Node *replacement = transplant(node);
        fixUP(replacement);
    }

    void prentTree()
    {
        print(root);
        cout<< "\n------ end print ---------\n \n";
    }
};

int main()
{
    RedBlackTree<int> tree;
    for (int i = 1; i <= 10; i++)
    {
        tree.insert(i);
    }
    tree.prentTree();
    for (int i = 1; i <= 5; i++)
    {
        tree.remove(i);
    }
    tree.prentTree();
    return 0;
}
