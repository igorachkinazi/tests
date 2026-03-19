#include <iostream>
#include <cmath>
using namespace std;

void callNum(int num, int base) {
    if (num == 0) {
        return;
    }
    int  remainder = num % base;
    callNum(num / base, base);
    cout << remainder;
}

int main() {
    string origNum;
    int num = 0;
    int base;
    int newBase;
    cout << "Enter your number : ";
    cin >> origNum;
    cout << "Enter the base: ";
    cin >> base;
    cout << "Enter new base: ";
    cin >> newBase;
    int numDigits = origNum.length();
    for (int i = 0; i < numDigits; i++) {
        int digit;
        char c = origNum[i];
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        }
        else {
            digit = c -'a' + 10;
        }

        num = num +  pow(base, numDigits - i - 1) * digit;

    }

    callNum(num,newBase);
    cout << endl;    
   
    
}
