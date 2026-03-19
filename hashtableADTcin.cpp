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
    friend istream& operator >> (istream &in,  MyHash<K, V> &ht)
    {
        string name;
        int age;
        cout << "Enter name ";
        in >> name;
        cout << "Enter age ";
        in >> age;
        ht.insert(name, age);
        return in;
    }
};

int main() {
    MyHash<string, int> myHash;
    cin >> myHash;
    cin >> myHash;
    cin >> myHash;

    cout << endl << "My hash table now is: " << endl << myHash << endl; 

    return 0;
}
