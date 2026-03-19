#include <stdio.h>

struct MyStruct {
    int a;
    char b;
    double c;
};

char (*XXX)[sizeof( struct MyStruct )] = 1;

int main() {
    return 0;
}
