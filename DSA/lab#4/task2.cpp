
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
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
            // First node in the list
            tail = node;
            tail->next = tail;  // Points to itself
            tail->prev = tail;  // Points to itself
        } else {
            // Insert before current head (tail->next)
            Node* head = tail->next;
            node->next = head;
            node->prev = tail;
            head->prev = node;
            tail->next = node;
        }
        ++count;
    }

    void push_back(int val) {
        push_front(val);
        tail = tail->next; 
    }

    // 0 based index
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
        Node* nextNode = cur->next;
        node->next = nextNode;
        node->prev = cur;
        cur->next = node;
        nextNode->prev = node;
        ++count;
    }


    void pop_front() {
        if (empty()){
            cout<<"list is empty "<<endl;
            return;
        }
        Node* head = tail->next;
        if (head == tail) { // only one element
            delete head;
            tail = nullptr;
        } else {
            Node* newHead = head->next;
            tail->next = newHead;
            newHead->prev = tail;
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
    void Swap(Node* a , Node* b){
        int temp = a->data;
        a->data = b->data;
        b->data = temp;
    }


void ZigZagFormat() {
    if (empty() || count < 2) return;

    bool changed = true;
    while (changed) {
        changed = false;
        Node* current = tail->next; // Start from head

        for (size_t i = 0; i < count - 1; ++i) {
            Node* nextNode = current->next;

            if (i % 2 == 0) {
                // Even index: should be smaller than next
                if (current->data > nextNode->data) {
                    Swap(current, nextNode);
                    changed = true;
                }
            } else {
                // Odd index: should be larger than next
                if (current->data < nextNode->data) {
                    Swap(current, nextNode);
                    changed = true;
                }
            }

            current = nextNode;
        }
    }
    print();
}

    bool IsPalindrome(){
        if (empty() || count == 1) return true;

        Node* left = tail->next; 
        Node* right = tail;      

        for (int i = 0; i < count / 2; ++i) {
            if (left->data != right->data) {
                return false;
            }
            left = left->next;
            right = right->prev;
        }

        return true;
    } 
};



    int main() {
        CircularLinkedList list;
        while (true) {
            cout << "\nMenu:\n"
                 << "1) Push front\n"
                 << "2) Push back\n"
                 << "3) Insert at (0-based)\n"
                 << "4) Pop front\n"
                 << "5) Clear\n"
                 << "6) Print\n"
                 << "7) ZigZag format\n"
                 << "8) Size\n"
                 << "9) Check palindrome\n"
                 << "10) Exit\n"
                 << "Choose an option: ";
            int choice;
            if (!(cin >> choice)) {
                cout << "Invalid input. Try again.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            if (choice == 10) break;

            switch (choice) {
                case 1: {
                    cout << "Value to push at front: ";
                    int v; if (!(cin >> v)) { cout << "Invalid value.\n"; cin.clear(); cin.ignore(10000,'\n'); break; }
                    list.push_front(v);
                    cout << "Pushed " << v << " at front.\n";
                    break;
                }
                case 2: {
                    cout << "Value to push at back: ";
                    int v; if (!(cin >> v)) { cout << "Invalid value.\n"; cin.clear(); cin.ignore(10000,'\n'); break; }
                    list.push_back(v);
                    cout << "Pushed " << v << " at back.\n";
                    break;
                }
                case 3: {
                    cout << "Index (0-based): ";
                    long long idx; if (!(cin >> idx) || idx < 0) { cout << "Invalid index.\n"; cin.clear(); cin.ignore(10000,'\n'); break; }
                    cout << "Value: ";
                    int v; if (!(cin >> v)) { cout << "Invalid value.\n"; cin.clear(); cin.ignore(10000,'\n'); break; }
                    if (static_cast<size_t>(idx) > list.size()) {
                        cout << "Index out of range. Current size: " << list.size() << "\n";
                        break;
                    }
                    try {
                        list.insert_at(static_cast<size_t>(idx), v);
                        cout << "Inserted " << v << " at index " << idx << ".\n";
                    } catch (const std::exception& e) {
                        cout << "Error: " << e.what() << "\n";
                    }
                    break;
                }
                case 4: {
                    list.pop_front();
                    cout << "Popped front (if any).\n";
                    break;
                }
                case 5: {
                    list.clear();
                    cout << "List cleared.\n";
                    break;
                }
                case 6: {
                    cout << "List: ";
                    list.print();
                    cout << "\n";
                    break;
                }
                case 7: {
                    list.ZigZagFormat();
                    cout << "Applied ZigZag format.\n";
                    break;
                }
                case 8: {
                    cout << "Size: " << list.size() << "\n";
                    break;
                }
                case 9: {
                    bool isPal = list.IsPalindrome();
                    cout << "List is " << (isPal ? "" : "not ") << "a palindrome.\n";
                    break;
                }
                default:
                    cout << "Unknown option. Try again.\n";
            }
        }

        return 0;
    }
