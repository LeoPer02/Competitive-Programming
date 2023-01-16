#include <bits/stdc++.h>
using namespace std;

/*
General Idea: We represent the matrix as a graph in wich every elements connects to a another only if they are
nightbours and are represented by the same letter, then applying dfs to get the connected components, we can get the
number of states in wich the language x is spoken

Time complexity: O(V), where v = vertices
*/

#define MAX 150
bool visited[MAX][MAX];
char graph[MAX][MAX];
map<char,int> freq;
multimap<int, char> rev;
int x, y;

// There is a path between 2 nodes if and only if they represent the same letter

void dfs(int i, int j){
    visited[i][j] = true;
    if(i+1 < x && graph[i+1][j] == graph[i][j] && !visited[i+1][j]){
        dfs(i+1, j);
    }
    if(j+1 < y && graph[i][j+1] == graph[i][j] && !visited[i][j+1]){
        dfs(i, j+1);
    }
    if(i-1 >= 0 && graph[i-1][j] == graph[i][j] && !visited[i-1][j]){
        dfs(i-1, j);
    }
    if(j-1 >= 0 && graph[i][j-1] == graph[i][j] && !visited[i][j-1]){
        dfs(i, j-1);
    }
}

void debugPrintVisited(){
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            if(visited[i][j]) cout << "1";
            else cout << "0";
        }
        cout << endl;
    }
}

int main(){
    int cases;
    cin >> cases;
    for(int k = 0; k<cases; k++){
        cout << "World #" << k+1 << endl;
        rev.clear();
        freq.clear();
        cin >> x >> y;
        memset(graph, 0, sizeof(graph));
        for(int i = 0; i < x; i++){
            for(int j = 0; j < y; j++){
                cin >> graph[i][j];
                visited[i][j] = false;
            }
        }
        for(int i = 0; i < x; i++){
            for(int j = 0; j< y; j++){
                if(!visited[i][j]){
                    dfs(i, j);
                    freq[graph[i][j]]++;
                }
            }
        }

        for(auto it = freq.begin(); it != freq.end(); it++){
            rev.insert({it->second * -1, it->first});
        }

        for(auto it = rev.begin(); it != rev.end(); it++){
            cout << it->second << ": " << it->first*-1 << endl;
        }
    }

}