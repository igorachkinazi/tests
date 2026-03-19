#include <iostream>
#include <vector>

using namespace std;

int partitionlimit = 0;

void insertionSort(vector<int>& avector, int first, int last) {
    for (unsigned int index=first; index<=last; index++) {
        int currentvalue = avector[index];
        int position = index;

        while (position>0 && avector[position-1]>currentvalue) {
            avector[position] = avector[position-1];
            position--;
        }
        avector[position] = currentvalue;
    }
}

int partition(vector<int>& vec, int first, int last) {
    int pivot = vec[first]; // Choose the first element as the pivot
    int i = first + 1; // Pointer for elements smaller than pivot

    for (int j = i; j <= last; j++) {
        if (vec[j] < pivot) {
            swap(vec[i], vec[j]);
            i++;
        }
    }
    swap(vec[first], vec[i - 1]); // Place the pivot in its final position
    return i - 1; // Return the pivot index

}

//recursive function that quicksorts through a given vector
void quickSort(vector<int> &avector, int first, int last) {
  int splitpoint;

   if(partitionlimit && last-first < partitionlimit) {
        insertionSort(avector, first, last);
        return;
    }
    if (first<last) {
       splitpoint = partition(avector,first,last);

    quickSort(avector,first,splitpoint);
    quickSort(avector,splitpoint+1,last);

  }
}

void printVector(vector<int> vec) {
    for (int element : vec )
        cout << element << " ";
    cout << endl << endl;
}


void runsort(vector<int> vec) {
    clock_t begin_t, end_t;
    double elapsed_micros;

    begin_t = clock();
    quickSort(vec,0,vec.size()-1);
    end_t = clock();
    elapsed_micros = double(end_t - begin_t) * 1000000 /CLOCKS_PER_SEC;
    if(partitionlimit)
       cout << "Quick sort with partition limit " << partitionlimit;
    else
       cout << "Quick sort standard";
    cout << " took " << elapsed_micros << " microseconds" << endl << endl;
}

int main() {

    int size = 500;
    
    srand(time(0));

    vector<int> myVector(size);

    for(int i = 0, limit = 999; i < size; i++) {
        myVector[i] = rand() % limit + 1;
    }

    runsort(myVector); // No partition set
    
    for(partitionlimit = 50; partitionlimit >=10 ; partitionlimit -= 5)
       runsort(myVector);

    return 0;
}
