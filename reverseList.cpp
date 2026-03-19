// reverseList.cpp, reverse linked list using recursive function
#include <iostream>
using namespace std;


class Node {
public:
    int data;
    Node* next;
    Node(int val) {
        data = val;
        next = nullptr;
    }
};

Node* reverseList(Node* head) {
    if (!head || !head->next) 
        return head;

    Node* reversedHead = reverseList(head->next);

    head->next->next = head;
    head->next = nullptr;

    return reversedHead;
}

void printList(Node* head) {
    Node *n = head;
    while(n != nullptr)
    {
        cout << n->data <<" ";
        n = n->next;
    }
    cout << endl;
}

void add(Node* head, int number) {

    while(head->next)
        head = head->next;
    head->next = new Node(number);
}

int main(){

    Node *mylist = new Node(3);
    add(mylist, 5);
    add(mylist, 8);
    add(mylist,10);
    add(mylist,15);

    printList(mylist);

    Node *newList = reverseList(mylist);
    printList(newList);

    return 0;
}

