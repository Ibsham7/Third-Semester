#include <iostream>


using namespace std;

template <typename T>
struct Node
{
    T data;
    Node<T>* next;
};

template <typename T>
class LinkedList
{
private:
    Node<T>* head;

public:
    LinkedList();

    void addAtFront(const T& n);
    void printList();
};



template <typename T>
LinkedList<T>::LinkedList()
{
    head = nullptr;
}

template <typename T>
void LinkedList<T>::addAtFront(const T& n)
{
    Node<T>* temp = new Node<T>;
    temp->data = n;
    temp->next = head;
    head = temp;
}

template <typename T>
void LinkedList<T>::printList()
{
    Node<T>* temp = head;
    while (temp != nullptr)
    {
        cout << "\t" << temp->data;
        temp = temp->next;
    }
    cout << endl;
}
