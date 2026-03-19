#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void heapify(vector<int>& vec, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && vec[left] > vec[largest]) {
        largest = left;
    }

    if (right < n && vec[right] > vec[largest]) {
        largest = right;
    }

    if (largest != i) {
        int tmp = vec[largest];
        vec[largest] = vec[i];
        vec[i] = tmp;
        heapify(vec, n, largest);
    }
}

void buildHeap(vector<int>& vec) {
    int n = vec.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(vec, n, i);
    }
}

void heapSort(vector<int>& vec) {
    int n = vec.size();
    buildHeap(vec);

    for (int i = n - 1; i > 0; i--) {
        int tmp = vec[0];
        vec[0] = vec[i];
        vec[i] = tmp;
        heapify(vec, i, 0);
    }
}

int main() {
    vector<int> vec = {9, 5, 6, 2, 3};
    heapSort(vec);

    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}
