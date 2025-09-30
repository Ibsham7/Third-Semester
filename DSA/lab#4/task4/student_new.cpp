#include <iostream>
#include "student.h"
using namespace std;


struct StackNode {
    int data;
    StackNode* next;
    StackNode(int value) : data(value), next(nullptr) {}
};

class Stack {
private:
    StackNode* top;  
    int size;        

public:
    // Constructor
    Stack() {
        top = nullptr;
        size = 0;
    }

    // Destructor 
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    //pushing to top of stack same as add at head
    void push(int data) {
        // Create a new node
        StackNode* newNode = new StackNode(data);
        newNode->next = top;
        top = newNode;
        size++;
    }

  
    int pop() {
        if (isEmpty()) {
            cout << "Stack is empty! Cannot pop." << endl;
            return -1; 
        }

        int data = top->data;

        StackNode* temp = top;
        top = top->next;
        delete temp;
        size--;

        return data;
    }

    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty! Cannot peek." << endl;
            return -1; 
        }

        return top->data;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    int getSize() {
        return size;
    }

    void printStack() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }

        cout << "Stack elements (top to bottom): ";
        StackNode* current = top;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    cout << "=== Stack Implementation Test ===\n" << endl;

    Stack intStack;
    cout << "Testing integer stack:" << endl;
    cout << "Is empty: " << (intStack.isEmpty() ? "Yes" : "No") << endl;

    cout << "Pushing: 10, 20, 30" << endl;
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    intStack.printStack();

    cout << "Size: " << intStack.getSize() << endl;
    cout << "Peek: " << intStack.peek() << endl;
    cout << "Pop: " << intStack.pop() << endl;
    intStack.printStack();

    cout << "Is empty: " << (intStack.isEmpty() ? "Yes" : "No") << endl;

    return 0;
}