#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


void test1(int size, int num){
    unordered_map<int, int> y;
    for (int i = 0; i < size; i++){
       y[i] = i;
    }
    clock_t begin_t1 = clock();
    for (int i = 0; i < num; i++){
       y.erase(i);
    }
    clock_t end_t1 = clock();
    double elapsed_secs = double(end_t1 - begin_t1) /CLOCKS_PER_SEC;
    cout << fixed << endl;
    cout << "erase " << num << " elements from hash table " << size << " size " << elapsed_secs << " seconds" << endl;

    vector<int> vect;
    for (int i = 0; i < size; i++){
        vect.push_back(i);
    }
    begin_t1 = clock();
    for (int i = 0; i < num; i++){
       auto it = vect.begin();
       vect.erase(it);
    }
    end_t1 = clock();
    elapsed_secs = double(end_t1 - begin_t1) /CLOCKS_PER_SEC;
    cout << "erase " << num << " elements from vector " << size << " size " << elapsed_secs << " seconds" << endl;
}

int main(){
    for(int a = 1000; a <= 5000; a += 1000)
       test1(a, 500);

    return 0;
}

