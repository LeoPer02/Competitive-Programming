#include <bits/stdc++.h>

using namespace std;
/*
General Idea: Use segment Trees and in the merge, check if one of the elementes is negative or 0 etc.. and return 1, -1 or 0 accordingly to the result
that way you run into overflow problems

Time Complexity: O(log n)
*/

#define MAX 200005
#define MAX_BUF 16
#define MAX_ST 800005

#define NEUTRAL 1

#define int long long

int n;          // Number of elements in the segtree
int v[MAX];     // Array of values
int st[MAX_ST]; // Segtree (in this case storing interval sums)

// Merge contents of nodes a and b
int merge(int a, int b)
{
    // Avoid Overflow
    if (a < 0 && b > 0)
        return -1;
    if (a < 0 && b < 0)
        return 1;
    if (a > 0 && b > 0)
        return 1;
    if (a > 0 && b < 0)
        return -1;
    if (a == 0 || b == 0)
        return 0;
    return a * b;
}

// Build initial segtree (in position pos, interval [start,end])
void build(int pos, int start, int end)
{
    if (start == end)
    {
        st[pos] = v[start];
    }
    else
    {
        int middle = start + (end - start) / 2;
        build(pos * 2, start, middle);
        build(pos * 2 + 1, middle + 1, end);
        st[pos] = merge(st[pos * 2], st[pos * 2 + 1]);
    }
}

// Update node x to value r
void update(int pos, int start, int end, int x, int r)
{
    if (start > x || end < x)
        return;
    if (start == end && start == x)
    {
        st[pos] = r;
    }
    else
    {
        int middle = start + (end - start) / 2;
        update(pos * 2, start, middle, x, r);
        update(pos * 2 + 1, middle + 1, end, x, r);
        st[pos] = merge(st[pos * 2], st[pos * 2 + 1]);
    }
}

// Make a query of interval [x,y]
int query(int pos, int start, int end, int x, int y)
{
    if (start > y || end < x)
        return NEUTRAL;
    if (start >= x && end <= y)
        return st[pos];

    int middle = start + (end - start) / 2;
    int a = query(pos * 2, start, middle, x, y);
    int b = query(pos * 2 + 1, middle + 1, end, x, y);
    return merge(a, b);
}

signed main()
{
    int k, val1, val2, result;
    char op;
    while (cin >> n >> k)
    {
        for (int i = 1; i <= n; i++)
        {
            cin >> v[i];
            // cout << v[i] << " ";
        }
        // cout << endl;
        build(1, 1, n);
        while (k--)
        {
            cin >> op >> val1 >> val2;
            if (op == 'C')
            {
                update(1, 1, n, val1, val2);
                // cout << "Val: " << st[val1] << " Passou para: " << val2 << endl;
            }
            else
            {
                result = query(1, 1, n, val1, val2);
                // cout << "Result: " << result << " Query: " << k << endl;
                if (result == 0)
                    cout << 0;
                else if (result < 0)
                    cout << "-";
                else
                    cout << "+";
            }
        }
        cout << endl;
    }
}