#include <bits/stdc++.h>
#define MAX 1005
#define INF 1e9
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

/*
General Idea: Represent the matrix as a graph and use Dijsktra to find the shortest path (Mininum cost) between the top left corner
and the bottom right corner

Time Complexity: O(E*log(V))
*/

using namespace std;
int graph[MAX][MAX], rows, cols;

typedef pair<int, int> iPair;

class Graph {
    int V; // No. of vertices
  
    // In a weighted graph, we need to store vertex
    // and weight pair for every edge
    list<pair<int, int> >* adj;
  
public:
    Graph(int V); // Constructor
  
    // function to add an edge to graph
    void addEdge(int u, int v, int w, int w2);
  
    // prints shortest path from s
    void shortestPath(int s);
};
  
// Allocates memory for adjacency list
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<iPair>[V];
}
  
void Graph::addEdge(int u, int v, int w, int w2)
{
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w2));
}
  
void Graph::shortestPath(int src)
{
    priority_queue<iPair, vector<iPair>, greater<iPair> >
        pq;
  
    vector<int> dist(V, INF);

    pq.push(make_pair(0, src));
    dist[src] = 0;
  

    while (!pq.empty()) {

        int u = pq.top().second;
        pq.pop();
  

        list<pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {
            int v = (*i).first;
            int weight = (*i).second;
  
            // If there is shorted path to v through u.
            if (dist[v] > dist[u] + weight) {
                // Updating distance of v
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
  
    cout << dist[rows*cols-1] + graph[0][0] << endl;
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int cases;
    cin >> cases;
    while(cases--){
        cin >> rows;
        cin >> cols;
        vector<int> d;
        memset(graph, 0, sizeof(graph));
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                cin >> graph[i][j];
            }
        }
        Graph g(rows*cols + 5);
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(i != 0) g.addEdge(i*cols + j, (i-1)*cols + j, graph[i-1][j], graph[i][j]);
                if(i != rows-1) g.addEdge(i*cols + j, (i+1)*cols + j, graph[i+1][j], graph[i][j]);
                if(j != 0) g.addEdge(i*cols + j, i*cols + j-1, graph[i][j-1], graph[i][j]);
                if(j != cols-1) g.addEdge(i*cols + j, i*cols + j+1, graph[i][j+1], graph[i][j]); 
            }
        }
        g.shortestPath(0);
    }
}