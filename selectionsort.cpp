// Selection sort using simultaneous assignment

#include <iostream>
#include <vector>

using namespace std;

int main() {
  int data []= {42, 83, 21, 57, 3, 7, 22, 26, 30, 12, 37, 64, 34, 25, 11, 90};
  int size = sizeof(data) / sizeof(int);
  int temp, i;

  for (i = 0; i < size - 1; i++) {
      int minIndex = i;
      for (int j = i + 1; j < size; j++) {
          if (data[j] < data[minIndex]) {
              minIndex = j;
          }
      }
      if (minIndex != i) 
          temp = data[i], data[i] = data[minIndex], data[minIndex] = temp;
  }

  cout << "Sorted array: " << endl;
  for (int value : data) {
    cout << value << " ";
  }
  cout << endl;
  return 0;
}

