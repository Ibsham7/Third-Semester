#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class List {
private:
    Node* head;

public:
    List() {
        head = nullptr;
    }

    void insertAtHead(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }


    void insertAtPosition(int value, int position) {
        int count = countNodes();

        if(count < position){
            cout<<"invalid position"<<endl;
            return;
        }
        Node* newNode = new Node(value);

        if (position <= 1 || head == nullptr) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* temp = head;
        int currentPosition = 1;

        while (temp->next != nullptr && currentPosition < position - 1) {
            temp = temp->next;
            currentPosition++;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    void displayList() {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        Node* temp = head;
        cout << "Linked List: ";
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    void deleteLastNode() {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return;
        }
        Node* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }

    int countNodes() {
        int count = 0;
        Node* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }
};

int main() {
    List linkedList;
    int choice, value, position;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert Node at Head\n";
        cout << "2. Insert Node at Position\n";
        cout << "3. Display List\n";
        cout << "4. Delete Last Node\n";
        cout << "5. Count Nodes\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert at head: ";
                cin >> value;
                linkedList.insertAtHead(value);
                break;
            case 2:
                cout << "Enter value to insert at valid position: ";
                cin >> value;
                cout << "Enter position (1-based): ";
                cin >> position;
                linkedList.insertAtPosition(value, position);
                break;
            case 3:
                linkedList.displayList();
                break;
            case 4:
                linkedList.deleteLastNode();
                cout << "Last node deleted (if existed)." << endl;
                break;
            case 5:
                cout << "Number of nodes: " << linkedList.countNodes() << endl;
                break;
            case 6:
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
