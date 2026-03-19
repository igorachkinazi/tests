//#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// Recursive function for DFS traversal
bool dfsRec(vector<vector<int>> &adj, vector<bool> &visited, int s, vector<int> &res)
{
    if(s == 5)
        return true;

    visited[s] = true;

    //res.push_back(s);

    // Recursively visit all adjacent vertices
    // that are not visited yet
    for (int i : adj[s]) {
        if (visited[i] == false) {
            bool ret = dfsRec(adj, visited, i, res);
            if(ret) {
                res.push_back(i);
                return true;
            }
        }
    }
    return false;
}

// Main DFS function that initializes the visited array
// and call DFSRec
vector<int> DFS(vector<vector<int>> &adj)
{
    vector<bool> visited(adj.size(), false);
    vector<int> res;
    if(dfsRec(adj, visited, 0, res))
        res.push_back(0);
    return res;
}

// To add an edge in an undirected graph
void addEdge(vector<vector<int>> &adj, int s, int t)
{
    adj[s].push_back(t);
    adj[t].push_back(s);
}

int main()
{
    int V = 6;
    vector<vector<int>> adj(V);

    // Add edges
    vector<vector<int>> edges = {{0, 2}, {2, 4}, {0, 3}, {0, 1}, {3, 5}};
    for (auto &e : edges)
        addEdge(adj, e[0], e[1]);

    // Starting vertex for DFS
    vector<int> res = DFS(adj); // Perform DFS starting from the source verte 0;

    reverse(res.begin(), res.end());
    for (int i = 0; i < res.size(); i++)
        cout << res[i] << " ";

    cout << endl;
}

