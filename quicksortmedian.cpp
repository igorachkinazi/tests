#include <iostream>
#include <vector>

using namespace std;

bool usemedian = false;

int median(int a, int b, int c) {
    if((a <= b && b <= c) || (c <= b && b <= a)) // If b is between a and c
        return b;
    if((b <= a && a <=c) || (c <= a && a <= b)) // if a is between b and c
        return a;
    return c;
}

int partition(vector<int>& vec, int first, int last) {
    if(usemedian && last - first > 1) {
        int medindex = (first+last)/2;
        int medval = median(vec[first], vec[medindex], vec[last]);
        if(medval == vec[medindex])
           swap(vec[first],vec[medindex]);
        else if (medval == vec[last])
            swap(vec[first],vec[last]);
    }
    int pivot = vec[first];
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
    if(usemedian)
       cout << "Quick sort with median of three";
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

    usemedian = false;
    runsort(myVector); 
    usemedian = true;
    runsort(myVector);

    return 0;
}
