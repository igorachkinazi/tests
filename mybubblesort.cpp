#include <iostream>
#include <vector>

using namespace std;

int main () {
    vector <int> nums = { 7, 15, 4, 13, 21, 8, 12, 10, 2, 1, 11};
    for (int j = 1; j < nums.size(); j++) {

        for (int i = 0; i < nums.size () - j; i++) {
            if (nums [i] > nums [i + 1]) {
                int tmp  = nums [i];
                nums [i] = nums [i+1];
                nums [i + 1] = tmp;
            }
        }
    }
    for (int num: nums) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
