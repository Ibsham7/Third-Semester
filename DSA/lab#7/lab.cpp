#include <iostream>
using namespace std;

struct Node {
    Node* left ;
    Node* right ; 
    int data ; 
    int height;
    Node(int val) : data(val) , left(nullptr) , right(nullptr) , height(1) {}
};



class AVL {
    private:
        Node* root;
        
     Node* insertWrapper(int val , Node* rootptr ){
        Node* temp = new Node (val);
        if (rootptr == nullptr){ 
            return temp ; 
            
        }
        
        if ( val < rootptr->data  ){
            rootptr->left = insertWrapper(val , rootptr->left);
        }
        else if ( val > rootptr->data){
            rootptr->right = insertWrapper(val , rootptr->right);
        }

            rootptr->height = 1 + max(height(rootptr->left), height(rootptr->right));

        return balanceTree(rootptr);

     }
     int calcBalance(Node* node){
        return node?height(node->left)- height(node->right) : 0 ;
     }

     int height(Node* node){
        return node?node->height:0;
     }
     
    Node* rightRotation( Node* node){
        Node* B = node->left;
        Node* temp = B->right;

        B->right = node;
        node->left = temp;

        node->height = 1 + max(height(node->left) , height(node->right));
        B->height = 1 + max(height(B->left) , height(B->right));

        return B;

     }
    Node* leftRotation( Node* node){
        Node* B = node->right;
        Node* temp = B->left;

        B->left = node;
        node->right = temp;

        node->height = 1 + max(height(node->right) , height(node->left));
        B->height = 1 + max(height(B->right) , height(B->left));

        return B;

     }


     Node* balanceTree(Node* node){
        int balance = calcBalance(node);
        if ( -1 <= balance || balance <= 1 || !node){
            return node;
        }

        else if (balance > 1 and calcBalance(node->left) >= 0){
            return rightRotation(node);
        }
        
        else if (balance > 1 and calcBalance(node->left) < 0){
            // LR
            node->left = leftRotation(node->left);
            return rightRotation(node); 
        }
    
        else if (balance < 1 and calcBalance(node->right) <= 0){
            return leftRotation(node);
        }
        
        else if (balance < 1 and calcBalance(node->right) > 0){
            //RL
            node->right = rightRotation(node->right);
            return leftRotation(node);
        }

        return node;
     }

     void inOrderWrapper(Node* root){
        if(root){
            inOrderWrapper(root->left);
            cout<<root->data<<"--";
            inOrderWrapper(root->right);
        }
    }


    Node* deleteWrapper(int value , Node* node){
       
        if(!node){
            return node;
        }
        if (value < node->data){
            node->left = deleteWrapper(value , node->left );
        }
        else if (value > node->data){
            node->right = deleteWrapper(value , node->right );
        }
        else{
            if (!node->left && !node->right ){
                delete node;
                return nullptr;
            }
            else if (! node->left){
                Node* temp = node->right;
                delete node;
                return temp;
            }
            
            else if (! node->right){
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = node->right;
                while(temp->left !=nullptr){
                    temp = temp->left;
                }
            node->data = temp->data;
            node->right = deleteWrapper(temp->data , node->right );

        }

        node->height = 1 + max(height(node->left) , height(node->right));
        return balanceTree(node);

    }
    public:
     AVL() : root(nullptr) {}
        void insert(int val){
            root = insertWrapper(val , root);
        }
        void deleteVal (int val){
            root = deleteWrapper(val , root);
        }

        void printInOrder(){
            inOrderWrapper(root);
        }



};
int main() { 

    AVL tree;
    int choice, value;

    do {
        cout << "\nAVL Tree Menu:\n";
        cout << "1. Insert a node\n";
        cout << "2. Delete a node\n";
        cout << "3. Print in-order traversal\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insert(value);
                break;

            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                tree.deleteVal(value);
                cout << "If value existed, it was deleted.\n";
                break;

            case 3:
                cout << "In-order traversal: ";
                tree.printInOrder();
                cout << "\n";
                break;

            case 4:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}