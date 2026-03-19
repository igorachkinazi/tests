#include <iostream>

using namespace std;

void add(int &  x, int y) {
    x = x + y;
    cout << " Inside add x =  "  << x <<endl;
}

int main () {
    int x = 3;
    int y = 5;
    add(x,  y);
    cout << " Inside main  x =  "  << x <<endl;
    return 0;
}
