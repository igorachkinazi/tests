#include <iostream>
#include <vector>
using namespace std;

// uses a vector to creat a Binar Heap
class BinHeap{

private:
    vector<int> heapvector;
    int currentSize;

public:
    // initializes the vector and an attribute currentSize
    // as 0 to allow for interger division.
    BinHeap(vector<int> heapvector){
        this->heapvector = heapvector;
        this->currentSize = 0;
    }

    // prelocates and item as far up in the
    // tree as possible to maintain
    // the Heap property
    void percUp(int i){
        while ((i / 2) > 0){
            if (this->heapvector[i] > this->heapvector[i/2]){
                int tmp = this->heapvector[i/2];
                this->heapvector[i/2] = this->heapvector[i];
                this->heapvector[i] = tmp;
            }
            i = i/2;
        }

    }

    // appends item to the end of the vector
    void insert(int k){
        this->heapvector.push_back(k);
        this->currentSize = this->currentSize + 1;
        this->percUp(this->currentSize);
    }

    // prelocates and item as far up in the
    // tree as possible to maintain
    // the Heap property
    void percDown(int i){
        while ((i*2) <= this->currentSize){
            int mc = this->maxChild(i);
            if (this->heapvector[i] < this->heapvector[mc]){
                int tmp = this->heapvector[i];
                this->heapvector[i] = this->heapvector[mc];
                this->heapvector[mc] = tmp;
            }
            i = mc;
        }
    }

    int maxChild(int i){
        if (((i*2)+1) > this->currentSize){
            return i * 2;
        }
        else{
            if (this->heapvector[i*2] > this->heapvector[(i*2)+1]){
                return i * 2;
            }
            else{
                return (i * 2) + 1;
            }
        }
    }

    // restores full complince with the heap structure
    // and heap order properties after the root is removed
    // by  taking the last item and moving it to the root position
    // and pushing the new root node down the tree to its proper postion.
    int delMax(){
        int retval = this->heapvector[1];
        this->heapvector[1] = this->heapvector[this->currentSize];
        this->currentSize = this->currentSize - 1;
        this->heapvector.pop_back();
        this->percDown(1);
        return retval;
    }

    void buildheap(vector<int> avector){
        int i = avector.size() / 2;
        this->currentSize = avector.size();
        this->heapvector.insert(this->heapvector.end(), avector.begin(), avector.end());
        while (i > 0){
            this->percDown(i);
            i = i - 1;
        }
    }

    bool isEmpty(){
        if (this->heapvector.size()>1){
            return false;
        }
        return true;
    }

    int findMax(){
        return this->heapvector[1];
    }
};

class PriorityQueue {
     BinHeap *m_bh;
public:
     PriorityQueue() {
        vector<int> vec;
        vec.push_back(0);

        m_bh = new BinHeap(vec);
     }
     void enqueue(int priority) {
        cout << "Enqueuing element with priority " << priority << endl;
        m_bh->insert(priority);
     }
     bool isEmpty() {
        return m_bh->isEmpty();
     }
     string dequeue() {
         string sVal = "Dequeuing element with priority " + to_string(m_bh->delMax());
         return sVal;
     }
};


int main(){
    PriorityQueue pq;

    pq.enqueue(2);
    pq.enqueue(7);
    pq.enqueue(6);
    pq.enqueue(5);
    pq.enqueue(3);
    pq.enqueue(9);
   
    cout << endl;
    while(!pq.isEmpty())
        cout << pq.dequeue() << endl;

    return 0;
}

