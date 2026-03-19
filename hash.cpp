#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


void test1(int size){
    unordered_map<int, int> y;
    clock_t begin_t1 = clock();
    for (int i = 0; i < size; i++){
       y[i] = i;
    }
    clock_t end_t1 = clock();
    double elapsed_secs = double(end_t1 - begin_t1) /CLOCKS_PER_SEC;
    cout << fixed << endl;
    cout << "insert " << size << " elements into hash table " << elapsed_secs << " seconds" << endl;

    begin_t1 = clock();
    int tmp;
    for (int i = 0; i < size; i++){
       tmp = y[i];
    }
    end_t1 = clock();
    elapsed_secs = double(end_t1 - begin_t1) /CLOCKS_PER_SEC;
    cout << "find " << size << " elements into hash table " << elapsed_secs << " seconds" << endl;
}

int main(){
    for(int a = 1000; a <= 5000; a += 1000)
       test1(a);

    return 0;
}

