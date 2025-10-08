#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
    Node* root;

    Node* insert(Node* node, int value) {
        if (!node) return new Node(value);
        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);
        return node;
    }

    Node* findMin(Node* node) {
        while (node && node->left != nullptr)
            node = node->left;
        return node;
    }

    Node* deleteNode(Node* node, int value) {
        if (!node) return node;

        if (value < node->data)
            node->left = deleteNode(node->left, value);
        else if (value > node->data)
            node->right = deleteNode(node->right, value);
        else {
            // Case 1: No child
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            // Case 2: One child
            else if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: Two children
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }

    void inOrder(Node* node) {
        if (!node) return;
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }

    void preOrder(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    void postOrder(Node* node) {
        if (!node) return;
        postOrder(node->left);
        postOrder(node->right);
        cout << node->data << " ";
    }

public:
    BinaryTree() : root(nullptr) {}

    void insertNode(int value) {
        root = insert(root, value);
    }

    void deleteNode(int value) {
        root = deleteNode(root, value);
    }

    void inOrderWrapper() {
        cout << "In-order Traversal: ";
        inOrder(root);
        cout << "\n";
    }

    void preOrderWrapper() {
        cout << "Pre-order Traversal: ";
        preOrder(root);
        cout << "\n";
    }

    void postOrderWrapper() {
        cout << "Post-order Traversal: ";
        postOrder(root);
        cout << "\n";
    }
};

int main() {
    BinaryTree tree;
    int choice, value;

    while (true) {
        cout << "\n=====================\n";
        cout << "  Binary Search Tree Menu\n";
        cout << "=====================\n";
        cout << "1. Insert new data\n";
        cout << "2. In-Order Traversal\n";
        cout << "3. Pre-Order Traversal\n";
        cout << "4. Post-Order Traversal\n";
        cout << "5. Delete an item\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insertNode(value);
                cout << "Value inserted successfully.\n";
                break;

            case 2:
                tree.inOrderWrapper();
                break;

            case 3:
                tree.preOrderWrapper();
                break;

            case 4:
                tree.postOrderWrapper();
                break;

            case 5:
                cout << "Enter value to delete: ";
                cin >> value;
                tree.deleteNode(value);
                cout << "If value existed, it was deleted.\n";
                break;

            case 6:
                cout << "Exiting program...\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
