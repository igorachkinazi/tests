// queues.cpp
// comparison of vector based and linked list based queues
// addition to the queue is about the same, vector queue is a bit faster
// dequeue time is much faster for linked list queue
//
#include <iostream>
#include <vector>

using namespace std;

class Elem {
public:
    int number;
    Elem* next;
    Elem(int num) : number(num) { next = nullptr; }
};

class LLQueue {
private:
    Elem* head;
    Elem* tail;
    int   size;

public:
    LLQueue() { 
        head = nullptr;
        tail = nullptr;
        size = 0 ; 
    }
    bool empty() { return head == nullptr; }
    int length() { return size; }
    void enqueue(int number) {
        Elem* elem = new Elem(number);
        if(empty()) 
            head = tail = elem;
        else {
            tail->next = elem;
            tail = elem;
        }
        size++;
    }
    int dequeue() {
        if(empty()) {
            cout << "Error! queue is empty" << endl;
            return -1;
        }
        Elem *elem = head;
        int number = elem->number;
        head = head->next;
        size--;
        if(empty())
            tail = nullptr;
        delete elem;
        return number;
    }
};

void linkedlist_queue_test(int num) {
    LLQueue llqueue;
    int i;

    clock_t begin_t1 = clock();
    for ( i = 0; i < 1000; i ++ )
       llqueue.enqueue(i+1);
    clock_t end_t1 = clock();
    double elapsed_secs = double(end_t1 - begin_t1) /CLOCKS_PER_SEC * 1000;
    cout << "Linked list add " << num << " elements " << elapsed_secs << " milliseconds" << endl;
    
    begin_t1 = clock();
    while(!llqueue.empty()) 
        llqueue.dequeue();
    end_t1 = clock();
    elapsed_secs = double(end_t1 - begin_t1) /CLOCKS_PER_SEC * 1000;
    cout << "Linked list dequeue " << num << " elements " << elapsed_secs << " milliseconds" << endl << endl;

}

void vector_queue_test(int num)
{
    vector<int> queue;
    int i;

    clock_t begin_t1 = clock();
    for ( i = 0; i < 1000; i ++ )
        queue.push_back(i+1);
    clock_t end_t1 = clock();
    double elapsed_secs = double(end_t1 - begin_t1) /CLOCKS_PER_SEC * 1000;
    cout << "Vector queue add " << num << " elements " << elapsed_secs << " milliseconds" << endl;

    begin_t1 = clock();
    while(queue.size())
       queue.erase(queue.begin());
    end_t1 = clock();
    elapsed_secs = double(end_t1 - begin_t1) /CLOCKS_PER_SEC * 1000;
    cout << "Vector queue dequeue " << num << " elements " << elapsed_secs << " milliseconds" << endl << endl;
}

int main() {
    linkedlist_queue_test(1000);
    vector_queue_test(1000);
    return 0;
}

