#include <iostream> 

using namespace std;

template < typename T1, typename T2 >

class Pair  {
public:
    T1 first;
    T2 second;
    Pair (T1 a, T2 b) {
        first = a;
        second = b;
    }
    void show () {
        cout << " (" << first << ","  << second << ") "  << endl;
    }


};

int main () {
    Pair < string, int > pair ("John", 30);
    Pair < int, double> score (51, 9.5);
    pair.show();
    score.show();

    return 0;
}
