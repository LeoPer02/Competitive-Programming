#include <bits/stdc++.h>
#define INF 1e6
// Base code for Edmods-karp algorithm: https://cp-algorithms.com/graph/edmonds_karp.html#implementation

/*
General Idea: Convert the input into an graph where we have an initial node connected to every task (every node that represents a task) with a flow equal to the number 
of times that tasks needs to be ran, after that, each task is connected to the possible pc's with a flow of 1
And finally, every pc is connected to the end node with flow of 1

With this graph we only need to apply the max-flow algorithm and then iterate through the residual graph and get with application is attributed to each pc

Time complexity: O(V*E^2)
*/

using namespace std;
map<char, int> tasks;
int n;
vector<vector<int>> capacity;
vector<vector<int>> adj;
vector<int> parent;

bool findTask(int a){
    if(tasks.find((char)((a-10) + 'A')) != tasks.end()) return true;
    return false;
}

int bfs(int s, int t) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});
    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        //cout << "cur: " << cur << " flow: " << flow << "\n";
        q.pop();
        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                //cout << "new flow: " << new_flow << " end: " << (next == t) <<  endl;
                if (next == t){
                   // cout << "RETURNIG: " << new_flow << " Cur: " << cur << " parent: " << parent[cur] <<  endl;
                    return new_flow;
                }
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    parent = vector<int>(55, -3);
    int new_flow;

    while ((new_flow = bfs(s, t))) {
        //cout << "Flow: " << new_flow << endl;
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}


int getN(char a){
    return (int)(a - 'A') + 10;
}   

void getPcs(string s, int *pcs){
    for(long unsigned int i = 0; i < s.length()-1; i++){
        *(pcs + i) = s.at(i) - '0';
    }
}
// TEST
void printAdj(){
    cout << "ADJ ###########\n";
    for(int i = 0; i < adj.size(); i++){
        if(!adj[i].empty()) cout << "i: " << i << endl;
        for(auto i : adj[i]){
             cout << i << " ";
        }
        if(!adj[i].empty()) cout << endl;
    }
}
// TEST
void printCap(){
    cout << "CAP ############\n";
    for(int i = 0; i < capacity.size(); i++){
        if(!capacity[i].empty()) cout << "i: " << i << endl;
        for(auto i : capacity[i]){
            cout << i << " ";
        }
        if(!capacity[i].empty()) cout << endl;
    }
}

int main(){
    string line;
    while(getline(cin, line), line != ""){
        char delimiter = ' ';
        adj = vector<vector<int>>(55, vector<int>());
        capacity = vector<vector<int>>(55, vector<int>(55, 0));
        tasks.clear();
        //cout << "Line1: <" << line << ">\n";
        string s1, s2;
        s1 = line.substr(0, line.find(delimiter));
        s2 = line.substr(line.find(delimiter)+1);
        // Store Tasks and its respective number
        tasks.insert({s1.at(0), s1.at(1) - '0'});
        int pcs[s2.length()-1];
        getPcs(s2, pcs);
        //cout << "First for\n";
        for(auto i : pcs){
            // For each possible pc for each letter, capacidade[letter][pc] = 1
            // adj[letter][pc]
            // adj[pc][letter]
            capacity[getN(s1.at(0))][i] = 1;
            adj[getN(s1.at(0))].push_back(i);
            adj[i].push_back(getN(s1.at(0)));
        }
        //cout << "First while\n";
        while(getline(cin, line), line != ""){
            //cout << "Line2: <" << line << ">\n";
            s1 = line.substr(0, line.find(delimiter));
            s2 = line.substr(line.find(delimiter)+1);
            tasks.insert({s1.at(0), s1.at(1) - '0'});
            int pcs[s2.length()-1];
            getPcs(s2, pcs);
            for(auto i : pcs){
            capacity[getN(s1.at(0))][i] = 1;
            adj[getN(s1.at(0))].push_back(i);
            adj[i].push_back(getN(s1.at(0)));

            }
        }

        // Ligar ai final
        for(int i = 0; i <= 9; i++){
            adj[i].push_back(49);
            adj[49].push_back(i);
            capacity[i][49] = 1;
        }
        // Connect the initial Node to all Computers
        for(auto it = tasks.begin(); it != tasks.end(); it++){
            capacity[48][getN(it->first)] = it->second;
            adj[48].push_back(getN(it->first));
            adj[getN(it->first)].push_back(48);
        }
        int total = 0;
        for(auto it = tasks.begin(); it != tasks.end(); it++){
            total += it->second;
        }
        if(maxflow(48, 49) == total){
            vector<char> res(10, '_');
            for(int i = 0; i < 10; i++){
                for(int j = 10; j < 36; j++){
                    if(capacity[i][j] == 1){
                        res[i] = (j-10) + 'A';
                    }
                }
            }
            for(int i = 0; i < 10; i++){
                cout << res[i];
            }
        }else {
            cout << "!";
        }
        cout << "\n";
    }
}