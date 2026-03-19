#include <iostream>
#include <vector>
#include <queue>
#include <map>


using namespace std;


class Point {
public:
    int row;
    int col;

    Point (int r, int c) {
        row = r;
        col = c;
    }
    Point () {
        row = 0;
        col = 0;
    }
    
    bool operator== (Point & p) {
        if (row == p.row && col == p.col) {
            return true;
        }
        return false;
    }
    
    bool operator< (const Point & p) const  {
        if (row < p.row) {
            return true;
        }
        else if (row == p.row && col < p.col) {
            return true;
        }
        return false;
    }
};

vector<string> createMaze() {
    vector<string> maze;
    maze.push_back("+++++++++++++++++++++++");
    maze.push_back("++   +   ++ ++     +  X");
    maze.push_back("++ +   +       +++ + ++");
    maze.push_back("++ + +  ++  ++++   + ++");
    maze.push_back("++++ ++++++    +++ +  +");
    maze.push_back("++          ++  ++    +");
    maze.push_back("++++++ ++++++   +++++ +");
    maze.push_back("++     +   +++++++  + +");
    maze.push_back("++ +++++++      S +   +");
    maze.push_back("++                + +++");
    maze.push_back("+++++++++++++++++++++++");
    return maze;
}


void addEdge (map <Point,  vector <Point>> &  graph, Point p, Point c) {
    graph [p].push_back(c);
    graph [c].push_back(p);
}


vector <Point> bfs(map <Point, vector <Point>> &  graph, Point startNode, Point endNode) {
    map <Point, bool> visited;
    map <Point, Point> parent;
    queue <Point> q;

    Point root (-1, -1);

    visited [startNode] = true;
    q.push(startNode);
    parent[startNode] = root;

    while (q.empty() == false) {
        Point currentNode = q.front();
        q.pop();
        
        if (currentNode == endNode) {
            vector <Point> path;
            Point elem = endNode;
            while(!(elem == root)) {
                path.push_back(elem);
                elem = parent[elem];

            }
            return path;
        }

        for (Point i: graph[currentNode]) {
            if (! visited [i]) {
                parent [i] = currentNode;
                visited[i] = true;
                q.push(i);
            }
        }

    }
    return {};
}

void printMaze(vector <string> & maze) {
    for (string s : maze) {
        cout << s << endl;
    }
}

void find(vector <string> & maze, int & row, int & col, char target) {
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            if (maze[i][j] == target) {
                row = i;
                col = j;
                return;
            }
        }
    }
}

bool isGood(char t) {
    if (t == ' ' || t == 'X' || t == 'S') {
        return true;
    }
    return false;
}

int main() {
    map < Point, vector <Point>> myVec;

    vector <string> maze = createMaze();
    printMaze(maze);
    for (int i = 0; i < maze.size() - 1; i++) {
        for (int j = 0; j < maze[i].size() - 1; j++) {
            if (isGood(maze[i][j]) && isGood(maze[i][j + 1])) {
                addEdge(myVec, {i,j}, {i,j+1});
            }
            if (isGood(maze[i][j]) && isGood(maze[i + 1][j])) {
                addEdge(myVec, {i,j}, {i + 1,j});
            }
        } 
    }

    int row;
    int col;
    find(maze, row, col, 'S');
    Point start (row, col);
    find (maze, row, col, 'X');
    Point end (row, col);
    vector <Point> path =  bfs(myVec, start, end);
    for (int  i = path.size() - 1; i >= 0; i--) {
        maze[ path[i].row] [path[i].col] = 'O';
    }
    printMaze(maze);
    cout <<  endl;
    

    return 0;
}

