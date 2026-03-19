#include <iostream>
#include <stack>
#include <set>
#include <tuple>

using namespace std;

// This river bank state in numbers of (missioners, cannibals, boat)
typedef tuple<int, int, bool> state_t;

// Function to check if a state is valid
bool isValid(int m, int c) {
    return (m >= 0 && m <= 3 && c >= 0 && c <= 3) && (m == 0 || m >= c);
}

// Function to generate the next possible states
set<state_t> getNextStates(int m, int c, bool boat) {
    set<state_t> nextStates;
    int moves[5][2] = {{1, 0}, {2, 0}, {0, 1}, {0, 2}, {1, 1}};

    for (auto move : moves) {
        int newM = m + (boat ? -move[0] : move[0]);
        int newC = c + (boat ? -move[1] : move[1]);
        if (isValid(newM, newC) && isValid(3 - newM, 3 - newC)) {
            nextStates.insert({newM, newC, !boat});
        }
    }
    return nextStates;
}

bool dfs(int m, int c, bool boat, set<state_t>& visited, stack<state_t>& history) {
    if (m == 0 && c == 0) {
        return true; // Goal state reached
    }

    state_t currentState = {m, c, boat};
    if (visited.count(currentState)) {
        return false; // Already visited
    }
    visited.insert(currentState);

    set<state_t> nextStates = getNextStates(m, c, boat);
    for (auto nextState : nextStates) {
        if (dfs(get<0>(nextState), get<1>(nextState), get<2>(nextState), visited, history)) {
            history.push(currentState);
            return true;
        }
    }
    return false;
}

int main() {
    set<state_t> visited;
    stack<state_t> history;
    dfs(3, 3, true, visited, history);
    cout << "Numbers represents (missioners, cannibals, boat) on this river bank:" << endl;
    while(!history.empty()) {
        state_t s = history.top();
        history.pop();
        cout << "(" << get<0>(s) << ", " << get<1>(s) << ", " << get<2>(s) << ") -> ";
    }
    cout << "(0, 0, 0)" << endl;
    return 0;
}


