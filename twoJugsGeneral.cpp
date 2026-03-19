#include <bits/stdc++.h>
using namespace std;

// Function to find the minimum operations to obtain d litres
// in one jug
int minSteps(int m, int n, int d)
{
    // Check if the target is achievable
    if (d > max(m, n)) return -1; 
     
    // Queue for BFS: each state is (jug1, jug2, steps)
    queue<vector<int>> q;

    // For tracking the visited states
    vector<vector<bool>> visited(m + 1, 
                                 vector<bool>(n + 1, false));

    // Start with both jugs empty
    q.push({0, 0, 0});  // (jug1, jug2, steps)
    visited[0][0] = true;

    while (!q.empty()){
      
        auto curr = q.front();
        q.pop();

        int jug1 = curr[0];
        int jug2 = curr[1];
        int steps = curr[2];

        // If we have found the solution
        if (jug1 == d || jug2 == d) return steps;

        // All Possible operations are:

        // 1: Fill jug1
        if (!visited[m][jug2]){
            visited[m][jug2] = true;
            q.push({m, jug2, steps + 1});
        }

        // 2: Fill jug2
        if (!visited[jug1][n]){
            visited[jug1][n] = true;
            q.push({jug1, n, steps + 1});
        }

        // 3: Empty jug1
        if (!visited[0][jug2]){
            visited[0][jug2] = true;
            q.push({0, jug2, steps + 1});
        }

        // 4: Empty jug2
        if (!visited[jug1][0]){
            visited[jug1][0] = true;
            q.push({jug1, 0, steps + 1});
        }

        // 5: Pour jug1 into jug2
        int pour1to2 = min(jug1, n - jug2);
        if (!visited[jug1 - pour1to2][jug2 + pour1to2]){
            visited[jug1 - pour1to2][jug2 + pour1to2] = true;
            q.push({jug1 - pour1to2, jug2 + pour1to2,
                                                steps + 1});
        }

        // 6: Pour jug2 into jug1
        int pour2to1 = min(jug2, m - jug1);
        if (!visited[jug1 + pour2to1][jug2 - pour2to1]){
            visited[jug1 + pour2to1][jug2 - pour2to1] = true;
            q.push({jug1 + pour2to1, jug2 - pour2to1,
                                                steps + 1});
        }
    }

    // If no solution is found
    return -1;
}

int main(){ 
  
    int m = 7, n = 4, d = 2;
    cout << "With jug1 " << m << " gallons, jug2 " << n << " gallons get " << d << " gallons of water:\n";
    cout << minSteps(m, n, d);
    return 0;
}

