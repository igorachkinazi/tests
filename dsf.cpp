#include <iostream>
#include <vector>

using namespace std;




void addEdge (vector <vector <int>> &  graph, int p, int c) {
    graph [p].push_back(c);
    graph [c].push_back(p);
}


bool dfsRecord(vector <vector <int>> &  graph, vector <bool> &  visited, vector <int> &  result, int num) {
    if (num == 7) {
        result.push_back(num);
        return true;
    }
    visited [num] = true;
    // result.push_back(num);
    for (int i: graph[num]) {
        if (! visited [i]) {
            bool res = dfsRecord(graph, visited, result, i);
            if (res == true) {
                result.push_back(num);
                return true;
            }

        }

    }
    return false;
}



vector <int> dfs (vector <vector <int>> &  graph) {
    vector <bool> visited(graph.size(), false);
    vector <int> result;
    dfsRecord(graph, visited, result, 0);
    return result;
}

int main() {
    int size = 8;
    vector <vector <int>> myVec(size);
    vector <vector <int>> edges = {{ 0 , 1}, {0 , 4} , {1 , 2} , {1 , 3} , { 3 , 5}, {3 , 7} , {4 , 6}};
    for (auto e : edges) {
        addEdge(myVec, e[0], e[1]);
    }
    for (int i = 0; i < myVec.size(); i++) {
        for (int j = 0; j < myVec[i].size(); j++) {
            cout << myVec[i][j] << " ";
        }
        cout << endl;
    }
    vector <int> result = dfs(myVec);
    cout << "result" << endl;
    for (int i = result.size() - 1; i >= 0; i--) {
        cout << result[i] << " " ;
    }
    cout << endl;

    return 0;
}
