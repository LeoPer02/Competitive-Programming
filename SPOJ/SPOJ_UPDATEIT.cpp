#include <bits/stdc++.h>

/*
General Idea: Use cumulative sums
On the update queries, add the val to l (the first element of the interval) and then subtract val from r+1
That way, when calculating the cumulative sum, the adding of val will propagate through l - r and "ignored" from r+1 onwards

Time Complexity: O(n)
*/

using namespace std;

long int n;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long int u, l, r, val;
        cin >> n >> u;
        long int v[n];

        for (int i = 0; i < n; i++)
        {
            v[i] = 0;
        }
        for (int i = 0; i < u; i++)
        {
            cin >> l >> r >> val;
            v[l] += val;
            v[r + 1] -= val;
        }
        // Cumulative Sum
        for (int i = 1; i < n; i++)
        {
            v[i] += v[i - 1];
        }
        int q, query;
        cin >> q;
        while (q--)
        {
            cin >> query;
            cout << v[query] << endl;
        }
    }
    return 0;
}