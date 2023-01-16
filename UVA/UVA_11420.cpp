#include <bits/stdc++.h>
using namespace std;
/*
General Idea: Use Dynamic Programming to get the optimal solution
Using a recursive function, we can "simulate" 3 possible situations for every drawer
1- The previous drawer is locked and we lock the current one (Securing it). This also includes the first drawer (Wich its "previous one" is always considered locked)
2- The previous one is not locked but we lock the current one
3- Regardless if the previous one is locked or not, we don't lock the current one

Simulating this 3 situations we obtain the number of different ways to lock the n drawers

Time Complexity: O(n*log(n))
*/

#define MAX 65
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

long long int dp[MAX][MAX][2];
int n, s;

long long int solve(int pos,int locked,int total){
    if(total > s) return 0; // If it exceeds the number of locked drawers
    if(pos == n && total == s) return 1; // If we get to the last drawer and the sum is the desired number
    if(pos == n && total != s) return 0; // If the sum is not s
    if(dp[pos][total][locked] != -1) return dp[pos][total][locked]; // If we have the value, return it
    long long int temp= 0;
    if(locked) temp += solve(pos +1, 1, total+1); // If the previous drawer is locked, call solve locking the current one
    else temp += solve(pos +1, 1 ,total); // If the previous is not locked, call solve with the same total secured drawers, but locking the current one

    temp += solve(pos+1, 0, total); // Simulate also the case we didnt lock the current one
    // dp[{current drawer}]
    //   [{Current sum, (We can have equal sums in different situations)}]
    //   [{Is the previous drawer locked?}]
    return dp[pos][total][locked] = temp;

}

int main(){
ios::sync_with_stdio(0); cin.tie(0);
while(cin >> n, cin >> s, n >= 0 && s >= 0){
    memset(dp, -1, sizeof(dp));
    printf("%lld\n", solve(0,1,0));
}

}