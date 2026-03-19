#include <iostream>
#include <vector>
using namespace std;


void test1(int size, int num){
    vector<int> vect;
    vect.reserve(size);
    clock_t begin_t1 = clock();
    for (int i = size - num; i < size; i++){
        vect[i] = i;
    }
    clock_t end_t1 = clock();
    double elapsed_secs = double(end_t1 - begin_t1) /CLOCKS_PER_SEC;
    cout << fixed << endl;
    cout << "access " << num << " elements by index in " << size << " size vector " << elapsed_secs << " seconds" << endl;
}

int main(){

    for(int a = 1000; a <= 5000; a += 1000)
       test1(a, 500);

    return 0;
}

