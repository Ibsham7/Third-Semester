#include <iostream>
using namespace std;

class ArrayStack {
private:
    char* arr;
    size_t capacity;
    size_t topIndex;

public:
    ArrayStack(size_t cap) : capacity(cap), topIndex(-1) {
        arr = new char[capacity];
    }

    ~ArrayStack() {
        delete[] arr;
    }

    void push(char value) {
        if (topIndex + 1 < capacity) {
            arr[++topIndex] = value;
        } else {
            cerr << "Stack overflow\n";
        }
    }

    char pop() {
        if (topIndex >= 0) {
            return arr[topIndex--];
        } else {
            cerr << "Stack underflow\n";
            return '\0'; 
        }
    }

    char peek() const {
        if (topIndex >= 0) {
            return arr[topIndex];
        } else {
            cerr << "Stack is empty\n";
            return '\0';  
        }
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    bool isFull() const {
        return topIndex + 1 == capacity;
    }

    size_t size() const {
        return topIndex + 1;
    }
};


int main() { 
    string expression;
    cout<< "ENTER EXPRESSION :"<<endl;
    getline(cin, expression);

    ArrayStack stack(expression.length());

    for (char ch : expression) {
        if (ch == '(' || ch == '{' || ch == '[') {
            stack.push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (stack.isEmpty()) {
                cout << "Unbalanced expression\n";
                return 0;
            }
            char top = stack.pop();
            if ((ch == ')' && top != '(') ||
                (ch == '}' && top != '{') ||
                (ch == ']' && top != '[')) {
                cout << "Unbalanced expression\n";
                return 0;
            }
        }
    }

    if (!stack.isEmpty()) {
        cout << "Unbalanced expression\n";
    } else {
        cout << "Balanced expression\n";
    }

    return 0;
}