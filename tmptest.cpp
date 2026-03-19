#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v;
    
    for (int i = 0; i < 5; i++){
        v.push_back(i+1);
    }

    // Remove the element at index 2
    v.erase(v.begin() + 2);

    for (auto i : v)
        cout << i << " ";
    cout << endl;
    return 0;
}
