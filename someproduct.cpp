// Someproduct.cpp
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool haveSameDigits(int a, int b, int product) {

    // Convert numbers to strings
    string str_a = to_string(a);
    string str_b = to_string(b);
    string str_product = to_string(product);

    // Combine the digits of a and b
    string combined = str_a + str_b;

    // Sort the strings
    sort(combined.begin(), combined.end());
    sort(str_product.begin(), str_product.end());

    // Check if the sorted strings are equal
    return combined == str_product;
}

int main() {

    for (int a = 10; a < 100; ++a) { // a is a two-digit number
        for (int b = a; b < 100; ++b) { // b starts from a to avoid duplicates
            int product = a * b;

            if (product >= 1000 && product < 10000) { // Check if product is four-digit
                if (haveSameDigits(a, b, product)) {
                    cout << a << " * " << b << " = " << product << endl;
                }
            }
        }
    }
    return 0;
}


