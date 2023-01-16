#include <bits/stdc++.h>
using namespace std;
#define MAX 1005
#define INF 1e6

// Base code for Prim's minimum spanning tree: https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/

/*
General Idea: If we represent the city and streets as a graph we can apply the above Prim's Minimum spanning tree to get an connected,
undirected graph that connects all the vertices together, without any cycles and with the minimum possible total edge weight.
From there we can iterate through the MST and multiply the distances of the streets by the price to pave each unit

Time Complexity: O(V^2)
*/
int graph[MAX][MAX], n, m,p, V;

int minKey(int key[], bool mstSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
 
    return min_index;
}
 
// A utility function to print the
// constructed MST stored in parent[]
void printMST(int parent[])
{
    cout << "Edge \tWeight\n";
    for (int i = 0; i < V; i++)
        cout << parent[i] << " - " << i << " \t"
             << graph[i][parent[i]] << " \n";
}

int totalMST(int parent[]){
    int total = 0;
    for(int i = 0; i < V; i++){
        total += graph[i][parent[i]]*p;
    }
    return total;
}
 
// Function to construct and print MST for
// a graph represented using adjacency
// matrix representation
int primMST()
{
    // Array to store constructed MST
    int parent[V];
 
    // Key values used to pick minimum weight edge in cut
    int key[V];
 
    // To represent set of vertices included in MST
    bool mstSet[V];
 
    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;
 
    // Always include first 1st vertex in MST.
    // Make key 0 so that this vertex is picked as first
    // vertex.
    key[0] = 0;
    parent[0] = -1; // First node is always root of MST
 
    // The MST will have V vertices
    for (int count = 0; count < V; count++) {
        // Pick the minimum key vertex from the
        // set of vertices not yet included in MST
        int u = minKey(key, mstSet);
 
        // Add the picked vertex to the MST Set
        mstSet[u] = true;
 
        // Update key value and parent index of
        // the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not
        // yet included in MST
        for (int v = 0; v < V; v++)
 
            // graph[u][v] is non zero only for adjacent
            // vertices of m mstSet[v] is false for vertices
            // not yet included in MST Update the key only
            // if graph[u][v] is smaller than key[v]
            if (graph[u][v] && mstSet[v] == false
                && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
 
    // print the constructed MST
    return totalMST(parent);
}

void printGraph(){
    cout << "TEST\n";
    for(int i = 0; i < n; i++){
        for(int j = 0; j< n; j++){
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    int cases, a, b,c ;
    cin >> cases;
    while(cases--){
        cin >> p;
        cin >> n;
        V = n;
        cin >> m;
        //cout << "p, n, m: "<< p << " " << n <<  " " << m << endl;
        memset(graph, 0, sizeof(graph));
        for(int i = 0; i< m; i++){
                cin >> a >> b >> c;
                a--;
                b--;
                //cout << a << " " << b<< " ---> " << graph[a][b] << endl;
                graph[a][b] = c;
                graph[b][a] = c;
        }
        //cout << "--------------------\n";
        //printGraph();
        cout << primMST()<<endl;
    }
}