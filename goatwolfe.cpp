#include <iostream>
#include <stack>
#include <set>
#include <tuple>

using namespace std;

// A farmer needs to carry goat, wolf and cabbage to the other side of the river
// Farmer in a boat can carry only single item with him
// Cannot leave wolf with goat, or goat with cabbage

// This river bank state in numbers of (goat, wolf, cabbage, boat)
typedef tuple<bool, bool, bool, bool> this_side;

// Function to check if items are safe
bool isSafe(bool g, bool w, bool c, bool b) {
    return (g && !w && !c) || (!g && w && c) || (g && w && b) || (!g && !w && !b) || (g && c && b) || (!g && !c && !b);
}

// Function to generate the next possible states
set<this_side> getNextStates(bool g, bool w, bool cbool boat) {
    set<this_side> nextStates;
    bool boat = true;
    // Potential moves, only one item can move
    bool moves[3][3] = {{true, false, false}, {false, true, false}, {false, false, true}};

    for(auto move :  moves) {
        if( (!g && move[0]) || (!w && move[1]) || 
        bool newG = g
        if (isSafe(newG, newW, newC, newB)) {
            nextStates.insert({newG, newW, newC, !boat});
        }
    }
    return nextStates;
}

// G  W  C  B
// 0  1  1  0
// 0  1  1  1
// 0  0  1  0
// 1  0  1  1
// 1  0  0  0
// 1  0  0  1
// 0  0  0  0


