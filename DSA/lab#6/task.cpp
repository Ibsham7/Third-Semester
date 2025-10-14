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

    void printLeafNodesHelper(Node* node){
        if(!node) return;
        if(!node->left && !node->right){
            cout << node->data << " ";
            return;
        }
        printLeafNodesHelper(node->left);
        printLeafNodesHelper(node->right);
    }
    int countLeafNodesHelper(Node* node){
        if(!node) return 0;
        if(!node->left && !node->right){
            return 1;
        }
        return countLeafNodesHelper(node->left) + countLeafNodesHelper(node->right);
    }
    int countInternalNodesHelper(Node* node){
        if(!node || (!node->left && !node->right)) return 0;
        return 1 + countInternalNodesHelper(node->left) + countInternalNodesHelper(node->right);
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

    void searchNode(int value, Node*& loc, Node*& ploc) {
        loc = root;
        ploc = nullptr;

        while (loc != nullptr) {
            if (value == loc->data) {
                return;
            }
            ploc = loc;
            if (value < loc->data)
                loc = loc->left;
            else
                loc = loc->right;
        }

    }

    void InsertWithoutDuplication(int value) {
        Node* loc = nullptr;
        Node* ploc = nullptr;

        searchNode(value, loc, ploc);

        if (loc != nullptr) {
            cout << "Value " << value << " already exists. No insertion made.\n";
            return;
        }
        if (ploc == nullptr) {
            root = new Node(value);
            cout << "Inserted " << value << " as root node.\n";
            return;
        }
        if (value < ploc->data) {
            ploc->left = new Node(value);
            cout << "Inserted " << value << " to the LEFT of " << ploc->data << ".\n";
        } else {
            ploc->right = new Node(value);
            cout << "Inserted " << value << " to the RIGHT of " << ploc->data << ".\n";
        }
    }
    void printSmallestValue() {
        Node* node = root;
        while (node && node->left != nullptr)
            node = node->left;
        if (node)
            cout << "Smallest value: " << node->data << "\n";
        else
            cout << "Tree is empty.\n";
    }

    void printLargestValue() {
        Node* node = root;
        while (node && node->right != nullptr)
            node = node->right;
        if (node)
            cout << "Largest value: " << node->data << "\n";
        else
            cout << "Tree is empty.\n";
    }

void printLeafNodes() {
    cout << "Leaf nodes: ";
    printLeafNodesHelper(root);
    cout << "\n";
}
void countLeafNodes() {
    int count = countLeafNodesHelper(root);
    cout << "Total number of leaf nodes: " << count << "\n";
} 
void countInternalNodes(){
    int count = countInternalNodesHelper(root);
    cout << "Total number of internal nodes: " << count << "\n";
}
void heightOfTree(){
    int height = heightOfTreeHelper(root);
    cout << "Height of the tree: " << height << "\n";
}
    int heightOfTreeHelper(Node* node){
        if(!node) return -1; // height of empty tree is -1
        int leftHeight = heightOfTreeHelper(node->left);
        int rightHeight = heightOfTreeHelper(node->right);
        return 1 + max(leftHeight, rightHeight);
    }
void depthOfTree(int value){
    int depth = depthOfTreeHelper(root, value, 0);
    if(depth != -1)
        cout << "Depth of node " << value << ": " << depth << "\n";
    else
        cout << "Value " << value << " not found in the tree.\n";

};
    int depthOfTreeHelper(Node* node, int value, int depth){
        if(!node) return -1;
        if(node->data == value) return depth;
        int leftDepth = depthOfTreeHelper(node->left, value, depth + 1);
        if(leftDepth != -1) return leftDepth;
        return depthOfTreeHelper(node->right, value, depth + 1);
    }
};

int main() {
    BinaryTree tree;
    int choice, value;

    while (true) {
        cout << "\n=====================\n";
        cout << "  Binary Search Tree Menu\n";
        cout << "=====================\n";
        cout << "1. Insert new data (no duplicates)\n";
        cout << "2. In-Order Traversal\n";
        cout << "3. Pre-Order Traversal\n";
        cout << "4. Post-Order Traversal\n";
        cout << "5. Delete an item\n";
        cout << "6. Search for an item\n";
        cout << "7. Print smallest value\n";
        cout << "8. Print largest value\n";
        cout << "9. Print leaf nodes\n";
        cout << "10. Count leaf nodes\n";
        cout << "11. Count internal nodes\n";
        cout << "12. Get height of the tree\n";
        cout << "13. Get depth of a node\n";
        cout << "14. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                tree.InsertWithoutDuplication(value);
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

            case 6: {
                cout << "Enter value to search: ";
                cin >> value;
                Node* loc = nullptr;
                Node* ploc = nullptr;
                tree.searchNode(value, loc, ploc);
                if(!loc){
                    if(ploc)
                        cout << "You can insert " << value << " under parent node " << ploc->data << ".\n";
                    else
                        cout << "Tree is empty. You can insert " << value << " as the root node.\n";
                }
                else if (loc){
                    if(ploc)
                        cout << "Value " << value << " found with parent node " << ploc->data << ".\n";
                    else
                        cout << "Value " << value << " is the root node and has no parent.\n";
                }
                break;
            }
            case 7:
                tree.printSmallestValue();
                break;

            case 8:
                tree.printLargestValue();
                break;

            case 9:
                tree.printLeafNodes();
                break;


            case 10:
                tree.countLeafNodes();
                break;
            case 11:
                tree.countInternalNodes();
                break;
            case 12:
                tree.heightOfTree();
                break;
            case 13:
                int value;
                cout << "Enter value to find depth: ";
                cin >> value;
                tree.depthOfTree(value);
                break;
            case 14:
                cout << "Exiting program.\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
