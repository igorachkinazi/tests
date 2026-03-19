#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Vertex {
public:
  int id;
  map<int, int> connectedTo;

          //Empty constructor.
  Vertex() {
  }

          //Constructor that defines the key of the vertex.
  Vertex(int key) {
          id = key;
  }

          //Adds a neighbor to this vertex with the specified ID and weight.
  void addNeighbor(int nbr, int weight = 0) {
          connectedTo[nbr] = weight;
  }
          //Returns a vector (e.g, list) of vertices connected to this one.
  vector<int> getConnections() {
          vector<int> keys;
          // Use of iterator to find all keys
          for (map<int, int>::iterator it = connectedTo.begin();
                   it != connectedTo.end();
                   ++it) {
                  keys.push_back(it->first);
          }
          return keys;
  }

          //Returns the ID of this vertex.
  int getId() {
          return id;
  }

          //Returns the weight of the connection between this vertex and the specified neighbor.
  int getWeight(int nbr) {
          return connectedTo[nbr];
  }

          //Output stream overload operator for printing to the screen.
  friend ostream &operator<<(ostream &, Vertex &);
};

ostream &operator<<(ostream &stream, Vertex &vert) {
  vector<int> connects = vert.getConnections();
  for (unsigned int i = 0; i < connects.size(); i++) {
          stream << "( " << vert.id << " , " << connects[i] << " , " << vert.getWeight(connects[i]) << " ) \n";
  }

  return stream;
}

class Graph {
public:
  map<int, Vertex> vertList;
  int numVertices;

          //Empty constructor.
  Graph() {
          numVertices = 0;
  }

          //Adds the specified vertex and returns a copy of it.
  Vertex addVertex(int key) {
          numVertices++;
          Vertex newVertex = Vertex(key);
          this->vertList[key] = newVertex;
          return newVertex;
  }

          //Returns the vertex with the specified ID.
          //Will return NULl if the vertex doesn't exist.
  Vertex *getVertex(int n) {
          for (map<int, Vertex>::iterator it = vertList.begin();
                   it != vertList.end();
                   ++it) {
                  if (it->first == n) {
                          // Forced to use pntr due to possibility of returning NULL
                          Vertex *vpntr = &vertList[n];
                          return vpntr;
                  }
          }
          return NULL;
  }
          //Returns a boolean indicating if an index with the specified ID exists.
  bool contains(int n) {
          for (map<int, Vertex>::iterator it = vertList.begin();
                   it != vertList.end();
                   ++it) {
                  if (it->first == n) {
                          return true;
                  }
          }
          return false;
  }

          //Adds an edge between vertices F and T with a weight equivalent to cost.
  void addEdge(int f, int t, int cost = 0) {
          if (!this->contains(f)) {
                  cout << f << " was not found, adding!" << endl;
                  this->addVertex(f);
          }
          if (!this->contains(t)) {
                  cout << t << " was not found, adding!" << endl;
          }
          vertList[f].addNeighbor(t, cost);
  }

          //Returns a vector (e.g, list) of all vertices in this graph.
  vector<int> getVertices() {
          vector<int> verts;

          for (map<int, Vertex>::iterator it = vertList.begin();
                   it != vertList.end();
                   ++it) {
                  verts.push_back(it->first);
          }
          return verts;
  }

  void  transpose() {
      vector<int> vertex_ids = getVertices();
      vector<vector<int>> transposed_adj(numVertices);
      vector<vector<int>> transposed_weight(numVertices);
      int i;

      for(i = 0; i < numVertices; i++) {
          Vertex *v = getVertex(vertex_ids[i]);
          transposed_adj[i] = v->getConnections();
          for(int j = 0; j < transposed_adj[i].size(); j++)
              transposed_weight[i].push_back(v->getWeight(transposed_adj[i][j]));
      }

      int num = numVertices;

      numVertices = 0;
      vertList.clear();

      for ( i = 0; i < num; i++) {
          for (int j = 0; j < transposed_adj[i].size(); j++) {
              addEdge(transposed_adj[i][j], vertex_ids[i], transposed_weight[i][j]);
          }
      }

}

          //Overloaded Output stream operator for printing to the screen
  friend ostream &operator<<(ostream &, Graph &);
};

ostream &operator<<(ostream &stream, Graph &grph) {
  for (unsigned int i = 0; i < grph.vertList.size(); i++) {
          stream << grph.vertList[i];
  }

  return stream;
}

int main() {
  Graph g;

  for (int i = 0; i < 6; i++) {
          g.addVertex(i);
  }

  g.addEdge(0, 1, 5);
  g.addEdge(0, 5, 2);
  g.addEdge(1, 2, 4);
  g.addEdge(2, 3, 9);
  g.addEdge(3, 4, 7);
  g.addEdge(3, 5, 3);
  g.addEdge(4, 0, 1);
  g.addEdge(5, 4, 8);
  g.addEdge(5, 2, 1);

  cout << g << endl;

  g.transpose();

  cout << endl << g << endl;

  return 0;
}

