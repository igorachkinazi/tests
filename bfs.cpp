#include <iostream>
#include <vector>
#include <queue>
#include <map>


using namespace std;




void addEdge (map <int,  vector <int>> &  graph, int p, int c) {
    graph [p].push_back(c);
    graph [c].push_back(p);
}


vector <int> bfs(map <int, vector <int>> &  graph, int startNode, int endNode) {
    map <int, bool> visited;
    map <int, int> parent;
    queue <int> q;

    visited [startNode] = true;
    q.push(startNode);
    parent[startNode] = -1;

    while (q.empty() == false) {
        int currentNode = q.front();
        q.pop();
        
        if (currentNode == endNode) {
            vector <int> path;
            int elem = endNode;
            while(elem!= -1) {
                path.push_back(elem);
                elem = parent[elem];

            }
            return path;
        }

        for (int i: graph[currentNode]) {
            if (! visited [i]) {
                parent [i] = currentNode;
                visited[i] = true;
                q.push(i);
            }
        }

    }
    return {};
}


int main() {
    map < int, vector <int>> myVec;
    vector <vector <int>> edges = {{ 0 , 1}, {0 , 4} , {1 , 2} , {1 , 3} , { 3 , 5}, {4 , 5} , {4 , 6}, {6 , 7}};
    for (auto e : edges) {
        addEdge(myVec, e[0], e[1]);
    }
  
    vector <int> path =  bfs(myVec, 0, 5);
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << path[i] << " ";
    }
    cout <<  endl;
    

    return 0;
}
