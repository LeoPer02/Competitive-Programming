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
    //cout << "Entered dfs(" << i << "," << j << ")\n";
    //cout << "Letter: " << graph[i][j] << " on " << i << " " << j <<endl;
    //if(i == 0 && j == 4) cout << "Bot: " << graph[i+1][j] << "\n Right: " << graph[i][j+1] << "visited right: " << visited[i][j+1] << endl;
    visited[i][j] = true;
    if(i+1 < x && graph[i+1][j] == graph[i][j] && !visited[i+1][j]){
        //cout << graph[i][j] << " has collegue bottom\n";
        dfs(i+1, j);
    }
    if(j+1 < y && graph[i][j+1] == graph[i][j] && !visited[i][j+1]){
        //cout << graph[i][j] << " has collegue right\n";
        dfs(i, j+1);
    }
    if(i-1 >= 0 && graph[i-1][j] == graph[i][j] && !visited[i-1][j]){
        //cout << graph[i][j] << " has collegue top\n";
        dfs(i-1, j);
    }
    if(j-1 >= 0 && graph[i][j-1] == graph[i][j] && !visited[i][j-1]){
        //cout << graph[i][j] << " has collegue left\n";
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
        //cout << "X: " << x << " Y: " << y << endl;
        memset(graph, 0, sizeof(graph));
        for(int i = 0; i < x; i++){
            for(int j = 0; j < y; j++){
                cin >> graph[i][j];
               //cout << graph[i][j];
                visited[i][j] = false;
            }
            //cout << "\n";
        }
        for(int i = 0; i < x; i++){
            for(int j = 0; j< y; j++){
                if(!visited[i][j]){
                    //cout << "dfs: "<< i << " " << j << endl;
                    dfs(i, j);
                    //debugPrintVisited();
                    //cout << "Adding to: " << graph[i][j] << " to a total of: " << freq[graph[i][j]]+1 << endl; 
                    freq[graph[i][j]]++;
                    //cout << "----------------------\n";
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