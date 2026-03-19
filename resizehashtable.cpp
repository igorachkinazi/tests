#include <iostream>
#include <string>
using namespace std;

class HashTable{
    public:
    int size=11; // initial size of hash table is prime to help with collision resolution
    int *slots; // list to hold key items
    int elemcount;
    float load_factor = 0.7;
    string *data; // list to hold data values

    HashTable() {
        elemcount = 0;
        slots = new int[size];
        data = new string[size];
    }
    int hashfunction(int key) { // implements remainder method
        return key%size;
    }

    int getElemCount() { return elemcount; }

      // Computes original hashvalue, and if slot is
      // not empty iterates until empty slot is found
    int rehash(int oldhash) {
        return (oldhash+1)%size;
    }

    void resize(int newsize) {
        int *oldslots = slots;
        string *olddata = data;
        int oldsize = size;
        size = newsize;
        slots = new int[size];
        data = new string[size];
        elemcount = 0;
        for(int i = 0; i < oldsize; i++) {
            if(oldslots[i])
                put(oldslots[i], olddata[i]);
        }
     }
 
    // Function that assumes there will eventually be
    // an empty slot unless the key is alread present in the slot
    void put(int key, string val){
        if (elemcount >= size * load_factor)
            resize(size * 2 + 1);

        int hashvalue = hashfunction(key);
        int count = 0;

        if (data[hashvalue]=="") {
            slots[hashvalue] = key;
            data[hashvalue] = val;
            elemcount++;
        } else {
            if (slots[hashvalue] == key) {
                data[hashvalue] = val;
            } else {
                int nextslot = rehash(hashvalue);

                while (data[nextslot]!="" && slots[nextslot] != key) {
                    nextslot = rehash(nextslot);

                    count++;
                    if (count>size) {
                        cout<<"TABLE FULL"<<endl;
                        return;
                    }
                }
                if (data[nextslot]=="") {
                    slots[nextslot]=key;
                    data[nextslot]=val;
                    elemcount++;
                } else {
                    data[nextslot] = val;
                }
            }
        }
    }

    // computes the initial hash value
    // if value is not in the initial slot, uses
    // rehash to locate the next position
    string get(int key) {
        int startslot = hashfunction(key);

        string val;
        bool stop=false;
        bool found=false;
        int position = startslot;
        while(data[position]!="" && !found && !stop) {
            if (slots[position]==key) {
                found = true;
                val = data[position];
            } else {
                position=rehash(position);
                if (position==startslot) {
                    stop=true;
                }
            }

        }
        return val;
    }

    friend ostream& operator<<(ostream& stream, HashTable& hash);
};



ostream& operator<<(ostream& stream, HashTable& hash) {
    for (int i=0; i<hash.size; i++) {
        if(hash.data[i] != "")
            stream<<hash.slots[i]<<": "<<hash.data[i]<<endl;
    }

    return stream;
}

int main() {
    HashTable h;

    h.put(54, "cat");
    h.put(26, "dog");
    h.put(93, "lion");
    h.put(17, "tiger");
    h.put(77, "bird");
    h.put(31, "cow");
    h.put(44, "goat");
    h.put(55, "pig");
    cout << "First version of the table:" << endl;
    cout<<h<<endl;
    cout << "Elements count is " << h.getElemCount() << endl << endl;

    h.put(20, "chicken");
    h.put(33, "bull");
    h.put(24, "stork");
    cout<<h<<endl;
    cout << "Elements count is " << h.getElemCount() << endl << endl;



    cout << "Add some more values" << endl;
    h.put(20,"chicken");
    h.put(17,"tiger");
    h.put(20,"duck");
    cout << "Elements count is " << h.getElemCount() << endl;
    cout << "Some gets:" << endl;
    cout<<h.get(20)<<endl;
    cout<<h.get(99)<<endl;

    return 0;
}

