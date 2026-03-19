#include <iostream>

using namespace std;

int main() {
  int data []= {42, 83, 21, 57, 3, 7, 22, 26, 30, 12, 37, 64, 34, 25, 11, 90};
  int size = sizeof(data) / sizeof(int);
  int temp;
  bool swapped = true;
  int start = 0;
  int end = size - 1;
  int i;

  while (swapped) {
      swapped = false;
      for (i = start; i < end; ++i) {
          if (data[i] > data[i + 1]) {
              temp = data[i], data[i] = data[i+1], data[i+1] = temp;
              swapped = true;
          }
      }

      if (!swapped)
          break;
      swapped = false;
      --end;

      for (i = end - 1; i >= start; --i) {
          if (data[i] > data[i + 1]) {
              temp = data[i], data[i] = data[i+1], data[i+1] = temp;
              swapped = true;
          }
      }
      ++start;
  }
 
  cout << "Sorted array: " << endl;
  for (int value : data) {
    cout << value << " ";
  }
  cout << endl;
  return 0;
}

