#include <iostream>
#include <list>
#include<cstdlib>
#include <algorithm>

using namespace std;

int main() {

    int size = 4000;
    // Generate ordered list
    srand(time(0));

    list<int> myList;

    for(int i = 0, limit = 50, elem = 1; i < size; i++) {
        elem = elem + (rand() % limit);
        myList.push_back(elem);
        elem += 1;
    }

    // Print list
    //for (int element : myList )
    //    cout << element << " ";
    //cout << endl << endl;

    for(int i = 0; i < 10; i++) {
        // pick random element to search after
        int randPosition = rand() % size;
        int pos = 0;
        int value = 0;
        for (auto it = myList.begin(); it != myList.end(); it++, pos++) {
           if(pos == randPosition)
               value = *it;
        }
        cout << "Looking for value " << value << endl;
        clock_t begin_t1 = clock();
        for (auto it = myList.begin(); it != myList.end(); it++, pos++) {
           if(*it == value)
               break;
        }
        clock_t end_t1 = clock();
        double elapsed_micros = double(end_t1 - begin_t1) * 1000000 /CLOCKS_PER_SEC;
        cout << "Sequential search took " << elapsed_micros << " microseconds" << endl;
        begin_t1 = clock();
        binary_search(myList.begin(), myList.end(), value);
        end_t1 = clock();
        elapsed_micros = double(end_t1 - begin_t1) * 1000000 / CLOCKS_PER_SEC;
        cout << "Binary search took " << elapsed_micros << " microseconds" << endl << endl;
    }

    return 0;
}
