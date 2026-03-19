#include <iostream>

#include <unordered_map>

using namespace std;

class Element {
public:
    int value;
    string key;
    Element* next;

    Element (string name, int age) {
        value = age;
        key = name;
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
    void add (string key, int value) {
        Element* tmp = new Element(key, value);
        if (head == nullptr) {
            head = tmp;
            tail = tmp;
        }
        else {
            tail->next = tmp;
            tail = tmp;
        }
    }
    void del (string  name) {
        Element* prev = nullptr;
        for (Element* tmp = head; tmp != nullptr; tmp = tmp->next) {
            if (tmp->key  == name) {
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
    int find (string name) {
        for (Element* tmp = head; tmp != nullptr; tmp = tmp->next) {
            if (tmp->key  == name) {
                return tmp->value;
            }
        }
        return 0;
    }

    friend ostream& operator << (ostream& os, LinkedList& obj) {
        bool isEmpty = true;
        for (Element*  tmp = obj.head; tmp != nullptr; tmp = tmp->next) {
            os << tmp->key << " : " <<  tmp->value << " ";
            isEmpty = false;
        }
        if (isEmpty == false) {
             os << endl;
        }
        return os;
    }
 };



class Myhash {
    LinkedList  table [10];
    int hashFunc (string key) {
       return  key [0] % 10;
    }
public:
    void insert (string  key, int  value) {
        int  index = hashFunc(key);
        table [index].add (key, value);
    }
    void del (string key) {
        int index = hashFunc(key);
        table [index].del (key);
    }
    int find (string key) {
        int index = hashFunc(key);
        return table[index].find(key);
    }
    int operator[](string key) {
        return find(key);
    }
    
    friend ostream& operator << (ostream& os, Myhash& obj) {
        for (auto elem: obj.table) {
            os << elem;
        }

        return os;
    }
};

int main () {
    Myhash  hash1;
    hash1.insert("Max" , 17);
    hash1.insert ("Dennis", 25);
    hash1.insert("Papa" , 54);
    cout << hash1;
    hash1.del ("Dennis");
    cout << endl << hash1;
    cout << hash1["Katya"] << endl;
    return 0;
}
