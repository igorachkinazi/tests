// Comparison of 3 sorting algorithms on list of 500 integers
// Bubble sort took about 1200 microseconds
// Selection sort took about 570 microseconds
// Insertion sort took 400 microseconds, which is the fastest


#include <iostream>
#include <vector>
#include<cstdlib>
#include <algorithm>

using namespace std;

vector<int> bubbleSort(vector<int> avector) { //the vector for bubble sort
  for (int passnum = avector.size()-1; passnum > 0; passnum -= 1) {
      for (int i = 0; i < passnum; i++) {
          if (avector[i] > avector[i+1]) {
              int temp = avector[i];
              avector[i] = avector[i+1];
              avector[i+1] = temp;
          }
      }
  }
  return avector;
}

vector<int> selectionSort(vector<int> avector) {
    for (int fillslot = (avector.size() - 1); fillslot >= 0; fillslot--) {
        int positionOfMax = 0;
        for (int location = 1; location < fillslot + 1; location++) {
            if (avector[location] > avector[positionOfMax]) {
                positionOfMax = location;
            }
        }

        int temp = avector[fillslot];
        avector[fillslot] = avector[positionOfMax];
        avector[positionOfMax] = temp;
    }
    return avector;
}

vector<int> insertionSort(vector<int> avector) {
    for (unsigned int index=1; index<avector.size(); index++) {

        int currentvalue = avector[index];
        int position = index;

        while (position>0 && avector[position-1]>currentvalue) {
            avector[position] = avector[position-1];
            position--;
        }

        avector[position] = currentvalue;
    }

    return avector;
}

void printVector(vector<int> vec) {
    for (int element : vec )
        cout << element << " ";
    cout << endl << endl;
}

int main() {

    int size = 500;
    clock_t begin_t, end_t;
    double elapsed_micros;
    
    srand(time(0));

    vector<int> myVector(size);

    for(int i = 0, limit = 999; i < size; i++) {
        myVector[i] = rand() % limit + 1;
    }

    // Random list of integers
    printVector(myVector);

    begin_t = clock();
    bubbleSort(myVector);
    end_t = clock();
    elapsed_micros = double(end_t - begin_t) * 1000000 /CLOCKS_PER_SEC;
    cout << "Bubble sort took " << elapsed_micros << " microseconds" << endl << endl;

    begin_t = clock();
    selectionSort(myVector);
    end_t = clock();
    elapsed_micros = double(end_t - begin_t) * 1000000 /CLOCKS_PER_SEC;
    cout << "Selection sort took " << elapsed_micros << " microseconds" << endl << endl;

    begin_t = clock();
    insertionSort(myVector);
    end_t = clock();
    elapsed_micros = double(end_t - begin_t) * 1000000 /CLOCKS_PER_SEC;
    cout << "Insertion sort took " << elapsed_micros << " microseconds" << endl << endl;


    return 0;
}
