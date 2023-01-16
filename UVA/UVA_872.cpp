#include <bits/stdc++.h>
#define MAX 1000
using namespace std;
// Base code for Topological Order https://www.geeksforgeeks.org/all-topological-sorts-of-a-directed-acyclic-graph/

/*
General Idea: For this problem we can represent the input as a graph and using the following algorithm to generate all of the possible Topological Orderings of the graph

Time Complexity: O(V*(V+E))
*/

vector<int> nodesAux;
vector<int> ans;
bool flag2;
bool visitedAux[MAX];
list<int> *adjAux;

void dfs(int v) {
    //cout << "Entered: " << (char)(v + 65)<< endl;
    visitedAux[v] = true;
    for (int u : adjAux[v]) {
        if (!visitedAux[u])
            dfs(u);
    }
    ans.push_back(v);
}

class Graph{
    int n;
    set<int> nodes;
    list<int> *adj;
    vector<int> nivel;
    void ordemAux(vector<int>& res, bool visisted[]);

    public:
    Graph(int n);

    void addNode(int a, int b);
    void ordem();
};

Graph::Graph(int n){
    this->n = n;
    adj = new list<int>[n];
    for(int i = 0; i < n; i++) nivel.push_back(0);
}

void Graph::addNode(int a, int b){
    nodes.insert(a);
    nodes.insert(b);
    adj[a].push_back(b);
    //cout << "Inserted: " << (char)(a+65) << " and " << (char)(b + 65) << " ADJ ++ " << (char)(a+65) << " -> " << (char)(b+65) << endl;
    if(a != b)nivel[b]++;
}

void Graph::ordemAux(vector<int>& res, bool visited[]){
    bool flag = false;
 
    for (auto it = nodes.begin(); it != nodes.end(); it++)
    {
        //cout << "Entrei\n";
        int i = *it;
        //cout << "i: " << (char)(i+'A') << " Nivel: " << nivel[i] << endl;
        //  If indegree is 0 and not yet visited then
        //  only choose that vertex
        if (nivel[i] == 0 && !visited[i])
        {
            //  reducing indegree of adjacent vertices
            list<int>:: iterator j;
            for (j = adj[i].begin(); j != adj[i].end(); j++)
                nivel[*j]--;
 
            //  including in result
            res.push_back(i);
            visited[i] = true;
            ordemAux(res, visited);
 
            // resetting visited, res and indegree for
            // backtracking
            visited[i] = false;
            res.erase(res.end() - 1);
            for (j = adj[i].begin(); j != adj[i].end(); j++)
                nivel[*j]++;
 
            flag = true;
        }
    }
 
    //  We reach here if all vertices are visited.
    //  So we print the solution here
    //cout << "Flag = " << flag << endl;
    if (!flag)
    {
        if(res.size() != 0){
         flag2 = false;
        
        long unsigned int i;
        for (i = 0; i < res.size() - 1; i++)
            cout << (char)(res[i]+'A') << " ";
        cout << (char)(res[i] + 'A');
        cout << endl;
    }
    }
}

void Graph::ordem(){
    bool *visited = new bool[n];
    for(int i = 0; i < n; i++){
        visited[i] = false;
    }
    vector<int> res;
    ordemAux(res, visited);
}

void printnodes(){
    cout << "NODES (Size: " << nodesAux.size() <<"):\n";
    for(auto it = nodesAux.begin(); it != nodesAux.end(); it++){
        cout << *it<< " ";
    }
    cout << endl;
}

void printans(){
    cout << "ANS (Size: " << ans.size() <<"):\n"; 
    for(auto it = ans.begin(); it != ans.end(); it++){
        cout << *it<< " ";
    }
    cout << endl;
}

void printAdj(){
    for(auto it = nodesAux.begin(); it != nodesAux.end(); it++){
        cout << "Adj de: " << *it << endl;
        for(auto i = adjAux[*it].begin(); i!= adjAux[*it].end(); i++){
            cout << *i << " ";
        }
        cout << endl;
    }
}

int main(){
    int cases;
    cin >> cases;
    while(cases--){
        flag2 = true;
        nodesAux.clear();
        adjAux = new list<int>[MAX];
        ans.clear();
        string line;
        getline(cin , line); // Read empty line
        getline(cin, line);
        if(line.size() == 0){
        //cout << "Line1 " << line << endl;
        getline(cin, line);
        //cout << "Line2 " << line << endl;
        }
        for(long unsigned int i =0 ; i < line.length(); i++){
            //cout << line[i] << " \n";
            if(line[i] >= 'A' && line[i] <= 'Z') nodesAux.push_back((int)(line[i] - 65));
            //cout << line[i] << endl;
        }
        //cout << endl;
        //cout << "Nodes size: " << nodesAux.size() << endl;
        Graph g(MAX);
        for(long unsigned int i = 0; i < nodesAux.size(); i++) g.addNode(nodesAux[i], nodesAux[i]);
        getline(cin, line);
        char delimiter = ' ';
        size_t pos = 0;
        string token = line;
        while ((pos = line.find(delimiter)) != string::npos) {
            token = line.substr(0, pos);
            g.addNode((int)token[0]-'A', (int)token[2]-'A');
            adjAux[(int)(line[0] - 'A')].push_back((int)(line[2] - 'A'));
            line.erase(0, pos+1);
        }
        g.addNode((int)line[0] - 'A', (int)line[2]-'A');
        adjAux[(int)(line[0] - 'A')].push_back((int)(line[2] - 'A'));
        for(int i = 0; i<  MAX; i++) visitedAux[i] = false;
        //printAdj();
        for(auto it = nodesAux.begin(); it != nodesAux.end(); it++) 
            if(!visitedAux[*it]) dfs(*it);
        //printnodes();
        //printans();
        if(ans.size() != nodesAux.size()){
            if(cases == 0) cout << "NO\n";
            else cout << "NO\n\n";
        }else{ 
            g.ordem();
            //cout << "FLAG2: " << flag2 << endl;
            if(flag2){
                if(cases == 0) cout << "NO\n";
                else cout << "NO\n\n";
            }else if(cases != 0){
                cout << endl;
            }
        }
    }
    return 0;

}
