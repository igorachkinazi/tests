// twoJugs.cpp, using 2 jugs 3 and 4 gallons each (unmarked) get 2 gallons of water in 4 gallons jug
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


int main(){

    int jug1Vol, jug1Water = 0;
    int jug2Vol, jug2Water = 0;

    srand(std::time(0));

    // Generate volume of jugs
    if(rand() % 2) {
        jug1Vol = 3;
        jug2Vol = 4;
    }
    else {
        jug1Vol = 4;
        jug2Vol = 3;
    }
    cout << "Fill jug1" << endl;
    jug1Water = jug1Vol;
    cout << "Jug 1 volume: " << jug1Vol << " gallons, filled with " << jug1Water << " gallons of water" << endl;
    cout << "Jug 2 volume: " << jug2Vol << " gallons, filled with " << jug2Water << " gallons of water" << endl;

    cout << "Pour jug1 into jug2" << endl;
    if(jug1Water > jug2Vol) {
        jug2Water = jug2Vol;
        jug1Water -= jug2Vol;
    }
    else {
        jug2Water = jug1Water;
        jug1Water = 0;
    }

    cout << "Jug 1 volume: " << jug1Vol << " gallons, filled with " << jug1Water << " gallons of water" << endl; 
    cout << "Jug 2 volume: " << jug2Vol << " gallons, filled with " << jug2Water << " gallons of water" << endl;

    if(jug1Water) {
        cout << "Dump water from jug1" << endl << "Pour jug2 back to jug1" << endl;
        jug1Water = jug2Water;
        jug2Water = 0;
        cout << "Jug 1 volume: " << jug1Vol << " gallons, filled with " << jug1Water << " gallons of water" << endl;
        cout << "Jug 2 volume: " << jug2Vol << " gallons, filled with " << jug2Water << " gallons of water" << endl;
    }

    cout << "Fill empty jug with water" << endl;
    if(jug1Water == 0)
        jug1Water = jug1Vol;
    else if(jug2Water == 0)
        jug2Water = jug2Vol;

    cout << "Jug 1 volume: " << jug1Vol << " gallons, filled with " << jug1Water << " gallons of water" << endl;
    cout << "Jug 2 volume: " << jug2Vol << " gallons, filled with " << jug2Water << " gallons of water" << endl;
    
    cout << "Pour full jug into other jug" << endl;
    if(jug1Water == jug1Vol)
        jug1Water -= jug2Vol - jug2Water;
    else if(jug2Water == jug2Vol)
        jug2Water -= jug1Vol - jug1Water;

    cout << "Now we have one jug with 2 gallons of water" << endl;

    cout << "Jug 1 volume: " << jug1Vol << " gallons, filled with " << jug1Water << " gallons of water" << endl;
    cout << "Jug 2 volume: " << jug2Vol << " gallons, filled with " << jug2Water << " gallons of water" << endl;

    return 0;
}

