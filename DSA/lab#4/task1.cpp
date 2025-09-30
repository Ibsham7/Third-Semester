
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class CircularLinkedList {
    Node* tail; // tail->next is head
    size_t count;
public:
    CircularLinkedList() : tail(nullptr), count(0) {}
    ~CircularLinkedList() { clear(); }

    CircularLinkedList(const CircularLinkedList&) = delete;
    CircularLinkedList& operator=(const CircularLinkedList&) = delete;

    bool empty() const { return tail == nullptr; }
    size_t size() const { return count; }

    void push_front(int val) {
        Node* node = new Node(val);
        if (!tail) {
            tail = node;
            tail->next = tail;
        } else {
            node->next = tail->next;
            tail->next = node;
        }
        ++count;
    }

    void push_back(int val) {
        push_front(val);
        tail = tail->next; // move tail to new node
    }

    // insert at position idx (0-based). idx == size -> append.
    void insert_at(size_t idx, int val) {
        if (idx > count) throw std::out_of_range("insert_at: index out of range");
        if (idx == 0) {
            push_front(val);
            return;
        }
        if (idx == count) {
            push_back(val);
            return;
        }
        Node* cur = tail->next; // head
        for (size_t i = 0; i < idx - 1; ++i) cur = cur->next;
        Node* node = new Node(val);
        node->next = cur->next;
        cur->next = node;
        ++count;
    }


    void pop_front() {
        if (empty()) throw std::out_of_range("pop_front: list is empty");
        Node* head = tail->next;
        if (head == tail) { // only one element
            delete head;
            tail = nullptr;
        } else {
            tail->next = head->next;
            delete head;
        }
        --count;
    }


void clear() {
    while (!empty()) pop_front();
}

void print() const {
    if (empty()) {
        cout << "(empty)";
        return;
    }
    Node* cur = tail->next; // head
    for (size_t i = 0; i < count; ++i) {
        cout << cur->data;
        if (i + 1 < count) cout << " ";
        cur = cur->next;
    }
}
};

int main() {


return 0;
}