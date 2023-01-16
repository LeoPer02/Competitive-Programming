#include <bits/stdc++.h>
#define MAX 20000
///////////////////////////////// Algorithm used: https://cp-algorithms.com/graph/strongly-connected-components.html#implementation
/*
    General Idea: Representing the "trust" between employees as connection in a graph we can apply the above algorithm to find all the strongly connected components

    Time Complexity: O(V+E)
*/
bool visited[MAX];
using namespace std;
int p, t;
map<long int, vector<long int>> nodes;
map<long int, vector<long int>> rev;
map<long int, int> vals;
vector<long int> order, component;

void dfs1(long int i){
    visited[vals[i]] = true;
    vector<long int> adj = nodes[i];
    for(auto a : adj){
        if(!visited[vals[a]]){
            dfs1(a);
        }
    }
    order.push_back(i);
}

void dfs2(long int i){
    visited[vals[i]] = true;
    vector<long int> adj = rev[i];
    component.push_back(i);
    for(auto a : adj){
        if(!visited[vals[a]]){
            dfs2(a);
        }
    }
}

int main(){
    cin >> p >> t;
    string sur, name, fullname;
    while(p != 0 || t != 0){
        nodes.clear();
        rev.clear();
        component.clear();
        order.clear();
        vals.clear();
        memset(visited, false, sizeof(visited));
        for(int i = 0; i < p; i++){
            cin >> sur;
            sur = sur.substr(0, sur.length() - 1);
            cin >> name;
            fullname = name + sur;
            hash<string> hasher;
            auto hashed = hasher(fullname);
            nodes.insert({hashed, {}});
            rev.insert({hashed, {}});
            vals[hashed] = i;
            nodes[hashed].push_back(hashed);
            rev[hashed].push_back(hashed);
        }
        string fullname2;
        for(int i = 0; i < t; i++){
            cin >> sur;
            sur = sur.substr(0, sur.length() - 1);
            cin >> name;
            fullname = name + sur;
            /////////////////////
            cin >> sur;
            sur = sur.substr(0, sur.length() - 1);
            cin >> name;
            fullname2 = name + sur;
            hash<string> hasher;
            auto hashed1 = hasher(fullname);
            auto hashed2 = hasher(fullname2);
            nodes[hashed1].push_back(hashed2);
            rev[hashed2].push_back(hashed1);
        }
        for(auto it = nodes.begin(); it != nodes.end(); it++){
            if(!visited[vals[it->first]])
                dfs1(it->first);
        }
        memset(visited, false, sizeof(visited));
        reverse(order.begin(), order.end());

        int total = 0;

         for(auto it = order.begin(); it != order.end(); it++){
            if(!visited[vals[*it]]){
                dfs2(*it);
                total++;
                component.clear();
            }
        }
        cout << total << endl;
        cin >> p >> t;
    }
}