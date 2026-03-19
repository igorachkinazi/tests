#include <iostream>

using namespace std;

int callNum(int num) {
    if (num == 1) {
        return 1;
    }
    return  num *  callNum(num - 1);
}

int main() {
    int num;
    cout << "Enter your number : ";
    cin >> num;
    int result = callNum(num);
    cout << result  << endl;
   
    
}
