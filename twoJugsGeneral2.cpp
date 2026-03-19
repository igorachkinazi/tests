#include <iostream>
#include <queue>
#include <set>
#include <tuple>
#include <map>

using namespace std;

int main() {
    int jug1_capacity = 7, jug2_capacity = 4, target = 2;


    queue<pair<int, int>> q; // Queue to store states (jug1_amount, jug2_amount)
    set<pair<int, int>> visited; // Set to track visited states
    map<pair<int,int>, pair<int,int>> parent; // Map to track parent of each state
    map<pair<int,int>, string> action; // Map to track action to reach each state

    q.push({0, 0}); // Start with both jugs empty
    visited.insert({0, 0});
    parent[{0,0}] = {-1,-1};
    action[{0,0}] = "Initial state";

    while (!q.empty()) {
        pair<int, int> current_state = q.front();
        q.pop();

        int jug1_amount = current_state.first;
        int jug2_amount = current_state.second;

        if (jug1_amount == target || jug2_amount == target) {
            vector<pair<int, int>> path;
            vector<string> actions;
            pair<int,int> temp = current_state;
            while(temp != make_pair(-1,-1)){
                path.push_back(temp);
                actions.push_back(action[temp]);
                temp = parent[temp];
            }
            for(int i = path.size()-1; i >= 0; i--){
                cout << actions[i] << ": (" << path[i].first << ", " << path[i].second << ")" << endl;
            }
            return 0;
        }

        // 1. Fill jug 1
        if (visited.find({jug1_capacity, jug2_amount}) == visited.end()) {
          q.push({jug1_capacity, jug2_amount});
          visited.insert({jug1_capacity, jug2_amount});
          parent[{jug1_capacity, jug2_amount}] = current_state;
          action[{jug1_capacity, jug2_amount}] = "Fill jug 1";
        }

        // 2. Fill jug 2
        if (visited.find({jug1_amount, jug2_capacity}) == visited.end()){
          q.push({jug1_amount, jug2_capacity});
          visited.insert({jug1_amount, jug2_capacity});
          parent[{jug1_amount, jug2_capacity}] = current_state;
          action[{jug1_amount, jug2_capacity}] = "Fill jug 2";
        }

        // 3. Empty jug 1
        if (visited.find({0, jug2_amount}) == visited.end()){
          q.push({0, jug2_amount});
          visited.insert({0, jug2_amount});
          parent[{0, jug2_amount}] = current_state;
          action[{0, jug2_amount}] = "Empty jug 1";
        }

        // 4. Empty jug 2
        if (visited.find({jug1_amount, 0}) == visited.end()){
          q.push({jug1_amount, 0});
          visited.insert({jug1_amount, 0});
          parent[{jug1_amount, 0}] = current_state;
          action[{jug1_amount, 0}] = "Empty jug 2";
        }

        // 5. Pour jug 1 to jug 2
        int pour1_2 = min(jug1_amount, jug2_capacity - jug2_amount);
        if (visited.find({jug1_amount - pour1_2, jug2_amount + pour1_2}) == visited.end()){
          q.push({jug1_amount - pour1_2, jug2_amount + pour1_2});
          visited.insert({jug1_amount - pour1_2, jug2_amount + pour1_2});
          parent[{jug1_amount - pour1_2, jug2_amount + pour1_2}] = current_state;
          action[{jug1_amount - pour1_2, jug2_amount + pour1_2}] = "Pour jug 1 to jug 2";
        }

        // 6. Pour jug 2 to jug 1
        int pour2_1 = min(jug2_amount, jug1_capacity - jug1_amount);
        if (visited.find({jug1_amount + pour2_1, jug2_amount - pour2_1}) == visited.end()){
          q.push({jug1_amount + pour2_1, jug2_amount - pour2_1});
          visited.insert({jug1_amount + pour2_1, jug2_amount - pour2_1});
          parent[{jug1_amount + pour2_1, jug2_amount - pour2_1}] = current_state;
          action[{jug1_amount + pour2_1, jug2_amount - pour2_1}] = "Pour jug 2 to jug 1";
        }
    }

    cout << "Cannot do" << endl;
    return 0;
}

