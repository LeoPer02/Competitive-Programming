#include <bits/stdc++.h>
using namespace std;
long long dp[120][10500], wt[110], val[110], n, maxAllow;

/*
General Idea: Apply the same idea used in the classic Dinamic Programming problem (KnapSack)
but having in consideration that we can surpass the budget if its by less 200

Time Complexity: O(v*w) v = number of elements; w = capacity
*/

int knapSackRec(int v, int w)
{
    int temp1 = 0;
    if (v >= n) // If we can't get more clothes return 0
        return 0;
    if (dp[v][w] != -1)
        return dp[v][w]; // If we already have the value for this position, return it

    // If the price until now plus the item price is less than the budget
    // OR
    // If it surpasses the budget but by less than 200
    if (w + wt[v] <= maxAllow || (w + wt[v] > 2000 && w + wt[v] <= maxAllow + 200))
    {
        temp1 = val[v] + knapSackRec(v + 1, w + wt[v]);
    }
    return dp[v][w] = max(temp1, knapSackRec(v + 1, w));
}

// Driver Code
int main()
{

    while (cin >> maxAllow >> n)
    {
        multimap<int, int> nmap;
        nmap.clear();
        int a, b;
        memset(dp, -1, sizeof(dp));
        for (int i = 0; i < n; i++)
        {
            cin >> a >> b;
            nmap.insert({a, b}); // Read values into map to store them in increasing order
        }
        int i = 0;
        for (auto it = nmap.begin(); it != nmap.end(); it++)
        {
            // cout << it->first << " " << it->second << endl;
            wt[i] = it->first;
            val[i] = it->second;
            i++;
        }
        cout << knapSackRec(0, 0) << endl;
    }
    return 0;
}