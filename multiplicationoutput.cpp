#include <iostream>

using namespace std;

int main() {

    int a;
    int b;
    cout << "Enter first 3-digit number to multiply - ";
    cin >> a;
    cout << "Enter second 3-digit number to multiply - ";
    cin >> b;
    if(a < 100 || a > 999 || b < 100 || b > 999) {
        cout << "Please enter correct numbers next time" << endl;
        return 0;
    }
    cout << "       " << a << endl;
    cout << "     X " << b << endl;
    cout << "  --------" << endl;
    cout << "       " << a * (b%10) << endl;
    cout << "     " << a * ((b%100)/10) << endl;
    cout << "    " << a * (b/100) << endl;
    cout << "  --------" << endl;
    cout << "    " << a * b << endl;


    return 0;
}
