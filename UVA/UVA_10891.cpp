#include <bits/stdc++.h>
#define INF 1e4
using namespace std;

/*
General Idea: Using Dinamic programming we can simulate get the best plays by simulating all possible plays from left to right
and right to left and get the one that maximizes the sum

Time complexity: O(n*log(n))
*/

int n, v[200], dp[200][200];

int solve(int x, int y){
    if(x > y) return 0;             // base case
    if(dp[x][y] != -1) return dp[x][y]; // If case already has been solved
    int total = 0;
    int temp = -INF;
    for(int i = x; i <= y; i++){ // left to right
        total += v[i];
        temp = max(temp, total - solve(i+1 , y)); // Seek best play starting from the left ending in y
    }
    total = 0;

    for(int i = y; i >= x; i--){ // Right to left
        total += v[i];
        temp = max(temp, total - solve(x, i-1));
    }

    return dp[x][y] = temp;
}

int main(){
    cin >> n;
    while(n){
        memset(v, 0, sizeof(v));
        memset(dp, -1, sizeof(dp));
        for(int i = 0; i < n; i++){
            cin >> v[i];
        }
        cout << solve(0, n-1) << endl;
        cin >> n;
    }
}