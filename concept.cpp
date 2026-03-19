#include <iostream>
#include <vector>
using namespace std;

// O(n^2)
void sortFunc(vector<int>& v) {
    for (int i = 0; i < v.size() - 1; i++) {
        for (int j = 0; j < v.size() - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                int tmp = v[j];
                v[j] = v[j+1];
                v[j+1] = tmp;
            }
        }
    }
}

// O(n)
void printVector(vector<int>& v) {
    for(int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

int main() {
    vector<int> vec = { 4, 6, 7, 12, 41, 55, 13, 1, 9 };
    printVector(vec);
    sortFunc(vec);
    printVector(vec);
    return 0;
}
