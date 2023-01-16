#include <bits/stdc++.h>
#define MAX 400005
using namespace std;

/*
General Idea: BIT with range update and query
Time Complexity: O(log n)
*/

long long int n, c;
long long int B1[MAX], B2[MAX];
void add(long long int b[], long long int idx, long long int x)
{
    while (idx <= n)
    {
        // cout << "Just added: " << x << " To b[" << idx << "]: " << b[idx] << endl;
        b[idx] += x;
        // cout << "Result: " << b[idx] << endl;
        idx += idx & -idx;
    }
}

void range_add(long int l, long int r, long long int x)
{
    add(B1, l, x);
    add(B1, r + 1, -x);
    add(B2, l, x * (l - 1));
    add(B2, r + 1, -x * r);
}

long long int sum(long long int b[], long long int idx)
{
    long int total = 0;
    while (idx > 0)
    {
        total += b[idx];
        idx -= idx & -idx;
    }
    return total;
}

long long int prefix_sum(long long int idx)
{
    return sum(B1, idx) * idx - sum(B2, idx);
}

long long int range_sum(long long int l, long long int r)
{
    return prefix_sum(r) - prefix_sum(l - 1);
}

int main()
{
    int cases, op;
    long long int p, q, v;
    cin >> cases;
    while (cases--)
    {
        cin >> n >> c;
        for (int i = 0; i < MAX; i++)
        {
            B1[i] = 0;
            B2[i] = 0;
        }
        while (c--)
        {
            cin >> op;
            if (op)
            {
                cin >> p >> q;
                cout << range_sum(p, q) << endl;
            }
            else
            {
                cin >> p >> q >> v;
                range_add(p, q, v);
            }
        }
    }
    return 0;
}