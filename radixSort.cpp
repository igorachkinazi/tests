// radixSort.cpp
// radix sort algorithm implementation
//
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void radixSort(vector<int>& arr, int key) {
  int arrSize = arr.size();
  vector<int> output(arrSize);
  vector<int> bucket_count(10); // 10 buckets
  int i;

  for (i = 0; i < 10; i++)
    bucket_count[i] = 0;

  for (i = 0; i < arrSize; i++) 
    bucket_count[(arr[i] / key) % 10]++;

  for (i = 1; i < 10; i++) 
    bucket_count[i] += bucket_count[i - 1];

  for (i = arrSize - 1; i >= 0; i--) {
    output[bucket_count[(arr[i] / key) % 10] - 1] = arr[i];
    bucket_count[(arr[i] / key) % 10]--;
  }

  for (i = 0; i < arrSize; i++) 
    arr[i] = output[i];
}


int main() {
  vector<int> arr = {221, 541, 27, 97, 772, 124, 22, 166, 16, 34};
  cout << "Array before sorting:" << endl;
  for (int num : arr) {
    cout << num << " ";
  }
  cout << endl << endl;
 
  for (int key = 1; key < 1000; key *= 10) {
    radixSort(arr, key);
  }
  
  cout << "Array after sorting:" << endl;
  for (int num : arr) {
    cout << num << " ";
  }
  cout << endl;
  
  return 0;
}
