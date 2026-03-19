// factorial.cpp, calculate factorial of a number using recursive function
#include <iostream>
using namespace std;


int calculate_factorial(int num){
    if(num == 1)
        return 1;
    return num * calculate_factorial(num - 1);
}

int main(){

    int number;
    cout << "Enter number" << endl;
    cin >> number;

    cout << "Factorial of " << number << " is " << calculate_factorial(number) << endl;

    return 0;
}

