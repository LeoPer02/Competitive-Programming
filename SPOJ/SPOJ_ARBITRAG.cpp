#include <bits/stdc++.h>
#define INF 1e6
#define MAX 1000
using namespace std;
map<string, int> names;
int n, V;
// Base code for Floyd-Warshall: https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/

/*
General Idea: Represent the currency exchange as a graph and apply Floyd-Warshall
in the end we only need to traverse the diagonal to check if it's possible to return to the same currency with a value
greater than 1.0. Because that would mean that we multiplied the initial currency by X and X > 1.0 means an improval of ((X - 1.0)*100)%

Time Complexity: O(V^3)
*/
double dist[MAX][MAX];

void printSolution();

void floydWarshall()
{
  int i, j, k; 
 

    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (dist[i][k] * dist[k][j] > dist[i][j])
                    dist[i][j] = dist[i][k] * dist[k][j];
            }
        }
    }
}

int main(){
    int m, count = 1;
    do{
        bool flag = false;
        names.clear();
        cin >> n;
        if(n == 0) break;
        V = n;
        memset(dist, 0, sizeof(dist));
        double a;
        string line, line2;
        for(int i = 0; i < n; i++){
            cin >> line;
            if(names.find(line) == names.end())
                names.insert({line, i});
        }
        cin >> m;
        for(int i = 0; i < m; i++){
            cin >> line >> a >> line2;
            dist[names[line]][names[line2]] = a;
        }
        floydWarshall();
        cout << "Case " << count << ": ";
        for(int i = 0; i < n; i++){
            if(dist[i][i] > 1.0){
                cout << "Yes\n";
                flag = true;
                break;
            }
        }
        if(!flag) cout << "No\n";
        count++;

    }while(n != 0);
}