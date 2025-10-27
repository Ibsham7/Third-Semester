#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;
    int height;
    Node(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree
{
public:
    Node* root;

    AVLTree() : root(nullptr) {}

    void insert(int val) {
        root = insertNode(root, val);
    }

    void inOrder() {
        inOrderTraversal(root);
    }

private:
  
    Node* insertNode(Node* node, int val) {
        if (node == nullptr) {
            return new Node(val);
        }
        if (val < node->data) {
            node->left = insertNode(node->left, val);
        } else {
            node->right = insertNode(node->right, val);
        }
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        return balanceTree(node);
    }

    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        return x;
    }

    // Function to perform left rotation
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        return y;
    }

    Node* balanceTree(Node* node) {
        int balance = getBalance(node);
        if (!node) return node;
        else if (balance > 1 || balance < -1) {
            return node;
        }
        // LL case
        else if (balance > 1 && getBalance(node->left) >= 0) {
            return rightRotate(node);
        }
        // RR case
        else if (balance < -1 && getBalance(node->right) <= 0) {
            return leftRotate(node);
        }
        // LR case
        else if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // RL case
        else if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }
    void inOrderTraversal(Node* node) {
        if (node) {
            inOrderTraversal(node->left);
            cout << node->data << " ";
            inOrderTraversal(node->right);
        }
    }
};

int main() { 

return 0 ;}