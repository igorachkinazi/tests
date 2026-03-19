#include <iostream>

using namespace std;

class Element {
public:
    int value;
    Element* next;

    Element (int num) {
        value = num;
        next = nullptr;
    }

};


class LinkedList {
public:
    Element* head;
    Element* tail;

    LinkedList() {
        head = nullptr;
        tail = nullptr;
    }
    void add (int num) {
        Element* tmp = new Element (num);
        if (head == nullptr) {
            head = tmp;
            tail = tmp;
        }
        else {
            tail->next = tmp;
            tail = tmp;
        }
    }
    void del (int num) {
        Element* prev = nullptr;
        for (Element* tmp = head; tmp != nullptr; tmp = tmp->next) {
            if (tmp->value == num) {
                if (tmp == head) {
                    head = tmp->next;
                    if (head == nullptr) {
                        tail = nullptr;
                    }
                    delete tmp;
                }
                else {
                    if (tail == tmp) {
                        tail = prev;
                    }
                    prev->next = tmp->next;
                    delete tmp;
                }
                return;
            }
            prev = tmp;
                    
        }
    }
    friend ostream& operator << (ostream& os, LinkedList& obj) {
        for (Element*  tmp = obj.head; tmp != nullptr; tmp = tmp->next) {
            os << tmp->value << " ";;
        }
        os << endl;
        return os;
    }
 };


int main () {
    Element x(2);
    LinkedList ll;
    ll.add(5);
    ll.add(3);
    ll.add(9);
    cout << ll;
    ll.del(9);
    ll.del(5);
    ll.del(3);
    cout << ll;
    ll.add(7);
    cout << ll;
    return 0;
}

