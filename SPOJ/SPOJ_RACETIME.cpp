// Example solution for UVA 12086
// Pedro Ribeiro (DCC/FCUP)

#include <bits/stdc++.h>

using namespace std;

#define MAX 200005
#define MAX_BUF 16
#define MAX_ST 800005

#define NEUTRAL 0

#define p pair<long long int, int>

int n;                // Number of elements in the segtree
long long int v[MAX]; // Array of values
p st[MAX_ST];         // Segtree (in this case storing interval sums)

// Merge contents of nodes a and b
p merge(p a, p b, long long int c)
{
    // if (c != 1000000001)
    cout << "Merge -> "
         << " A: " << a.first << " A.second: " << a.second << " B: " << b.first << " B.second: " << b.second << " C: " << c << endl;
    if (c == 1000000001)
        return b;
    if (a.first <= c)
    {
        if (b.first <= c)
        {
            return make_pair(a.first, b.second + a.second);
        }
        else
        {
            return a;
        }
    }
    else
    {
        if (b.first <= c)
        {
            return b;
        }
        else
        {
            return make_pair(0, 0);
        }
    }
}

// Build initial segtree (in position pos, interval [start,end])
void build(int pos, int start, int end)
{
    if (start == end)
    {
        st[pos].first = v[start];
        st[pos].second = 1;
    }
    else
    {
        int middle = start + (end - start) / 2;
        build(pos * 2, start, middle);
        build(pos * 2 + 1, middle + 1, end);
        st[pos] = merge(st[pos * 2], st[pos * 2 + 1], 1000000001);
    }
}

// Update node x to value r
void update(int pos, int start, int end, int x, int r)
{
    if (start > x || end < x)
        return;
    if (start == end && start == x)
    {
        st[pos].first = r;
        st[pos].second = 1;
    }
    else
    {
        int middle = start + (end - start) / 2;
        update(pos * 2, start, middle, x, r);
        update(pos * 2 + 1, middle + 1, end, x, r);
        st[pos] = merge(st[pos * 2], st[pos * 2 + 1], 1000000001);
    }
}

// Make a query of interval [x,y]
p query(int pos, int start, int end, long long int x, long long int y, long long int c)
{
    if (start > y || end < x)
        return make_pair(0, 0);
    if (start >= x && end <= y)
        return st[pos];

    int middle = start + (end - start) / 2;
    p a = query(pos * 2, start, middle, x, y, c);
    p b = query(pos * 2 + 1, middle + 1, end, x, y, c);
    return merge(a, b, c);
}

int main()
{
    long int n, c;
    cin >> n >> c;
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    char code;
    build(1, 1, n);
    for (int i = 0; i < c; i++)
    {
        cin >> code;
        long long int a, b, c;
        cin >> a >> b;
        if (code == 'M')
        {
            update(1, 1, n, a, b);
        }
        else
        {
            cin >> c;
            cout << query(1, 1, n, a, b, c).second << endl;
        }
    }
}