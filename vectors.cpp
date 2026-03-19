#include <iostream>
#include <vector>
#include <algorithm> 


using namespace std;

int main() {
    vector < int > myVec = { 5, 2, 8, 1 , 9, 4};
    cout << "unsorted vector: ";
    for (vector <int >:: iterator it = myVec.begin(); it != myVec.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
    sort (myVec.begin(), myVec.end());
    cout << "sorted vector: ";
    for (int num: myVec) {
        cout << num << " ";
    }
    cout << endl;
    vector<int>::iterator pos = myVec.begin() + 2;
    myVec.insert(pos,12);
    cout << "After insert: ";
    for (int num: myVec) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}
