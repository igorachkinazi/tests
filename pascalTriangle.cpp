// pascalTriangle.cpp, print Pascal triangle for given number of rows
#include <iostream>
using namespace std;


int getValue(int n, int k)
{
    int res = 1;
    if (k > n - k)
    k = n - k;
    for (int i = 0; i < k; ++i)
    {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

int main(){

    int number;
    int i, j;
    cout << "Enter number of rows" << endl;
    cin >> number;

    cout << endl << "Pascal triangle:" << endl;

    for (i = 0; i < number; i++)
    {
        for (j = 0; j < number - i; j++)
            cout << "  ";
        for (j = 0; j <= i; j++) {
            std::cout.width(4);
            cout << getValue(i, j);
        }
        cout << endl;
    }

    return 0;
}

