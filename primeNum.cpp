#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

bool isPrime(int n);
void printInternalDivisors(int n);

int main() {
    cout << "Hello from primeNum!" <<endl;
    cout << "Enter a number: ";
    int num;
    cin >> num;
    if (isPrime(num)) {
        cout << num << " is a prime number." << endl;
    } else {
        cout << num << " is not a prime number." << endl;
        cout << "Divisors of " << num << " (excluding 1 and itself): ";
        printInternalDivisors(num);
        cout << endl;
    }

    return 0;
}

// Print all divisors of n except 1 and n itself.
void printInternalDivisors(int n) {
    if (n <= 3) {
        cout << "(none)";
        return;
    }

    
    int limit = n / 2; // No need to check beyond n/2;

    bool first = true; // To handle comma placement
    for (int i = 2; i <= limit; i++) {
        if (n % i == 0) {
            if (!first) {
                cout << ", ";
            }
            cout << i;
            first = false;
        }
    }
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

