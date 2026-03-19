#include <iostream>
#include <vector>

using namespace std;

int main() {
  int data []= {42, 83, 21, 57, 3, 7, 22, 26, 30, 12, 37, 64, 34, 25, 11, 90};
  int size = sizeof(data) / sizeof(int);
  int temp;

  for (int i = 0; i < size - 1; ++i) {
    for (int j = 0; j < size - i - 1; ++j) {
      if (data[j] > data[j + 1]) {
        temp = data[j], data[j] = data[j + 1], data[j + 1] = temp;
      }
    }
  }
    
  cout << "Sorted array: " << endl;
  for (int value : data) {
    cout << value << " ";
  }
  cout << endl;
  return 0;
}

