#include <iostream>
#include <unordered_map>

using namespace std;

template <typename K, typename V>
class MyHash {
private:
    std::unordered_map<K, V> table;

public:
    void insert(const K& key, const V& value) { table[key] = value; }

    friend ostream& operator<<(ostream& os, MyHash<K, V>& ht) {
        for (auto elem : ht.table) {
            os << elem.first << ":" << elem.second << " " << endl;
        }
        return os;
    }
};

int main() {
    MyHash<string, int> myHash;
    myHash.insert("John", 17);
    myHash.insert("Bob", 12);
    myHash.insert("Megan", 8);

    cout << myHash << endl; 

    return 0;
}
