#include <cstdio>
#include <iostream>

using namespace std;

int main() {
    int num = 0;
    int totalNum = 0;
    cout << "Enter amount of first special numbers to print - ";
    cin >> totalNum;
    for(int number = 1000; number < 10000 && num < totalNum; number++) {
        int a = number / 100;
        int b = number % 100;
        if((a + b)*(a + b) == number) {
            printf("(%2d + %02d)^2 = %d\n", a, b, number);
            num++;
        }
    }
    if(num < totalNum)
        cout << "There are not " << totalNum << " four-digit numbers with this property" << endl;
    return 0;
}


