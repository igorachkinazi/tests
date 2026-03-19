// fibonacci.cpp, calculate Fibonacci number in given position using recursive function
#include <iostream>
using namespace std;


int calculate_fibonacci(int num){
    if(num <= 2)
        return 1;
    return calculate_fibonacci(num - 1) + calculate_fibonacci(num - 2);
}

int main(){

    int number;
    int result;
    cout << "Enter positive number " << endl;
    cin >> number;
    if(number < 1) {
        cout << "Please enter positive number" << endl;
        return 1;
    }

    if(number < 2) 
        result = 1;
    else
        result = calculate_fibonacci(number);

    cout << "Fibonacci sequence element of " << number << " is " << result << endl;

    return 0;
}

