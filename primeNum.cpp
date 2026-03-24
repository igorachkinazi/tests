#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int n);

int main() {
    cout << "Hello from primeNum!" <<endl;
    cout << "Enter a number: ";
    int num;
    cin >> num;
    if (isPrime(num)) {
        cout << num << " is a prime number." << endl;
    } else {
        cout << num << " is not a prime number." << endl;
    }
    return 0;
}
// Write a C++ function that checks if a given number is prime or not. The function should take an integer as input and return a boolean value indicating whether the number is prime.
bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

