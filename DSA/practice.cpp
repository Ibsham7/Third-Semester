#include <iostream>
using namespace std;

struct node{
    int data ; 
    node* next;
    node(int value){
        data = value ; 
        next = nullptr ;
}
};

class linkedList {
    private:
    node* head ;

    public:
    linkedList(){
        head = nullptr;
    }

    void addAtHead (node * newNode){
        newNode->next = head;
        head = newNode;
    }

    void printList (){
        node* temp = head;

        while(temp->next != nullptr){
            cout<<temp->data<<"-->";
            temp = temp->next;
        }
        cout<<"NULL"<<endl;
    }
    
    
    void deleteNode(){
        if(head == nullptr){
            cout<<"list is empty"<<endl;
            return ;
        }
        if(head->next == nullptr){
            delete head ;
            head = nullptr ;
            return ;
        }
        node* temp = head ;
        while(temp->next->next != nullptr){
            temp = temp->next ;
        }
        delete temp->next ;
        temp->next = nullptr ;
    }
};

int main() { 

return 0 ;}