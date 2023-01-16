#include <bits/stdc++.h>

using namespace std;

struct el
{
    map<int, int> x;
}

void
build(int a[], int v, int tl, int tr)
{
    if (tl == tr)
    {
        t[v].x[a[tl]]++;
    }
    else
    {
        int tm = (tl + tr) / 2;
        build(a, v * 2, tl, tm);
        build(a, v * 2 + 1, tm + 1, tr);
    }
}

void push(int v)
{
    if (marked[v])
    {
        t[v * 2] = t[v * 2 + 1] = t[v];
        marked[v * 2] = marked[v * 2 + 1] = true;
        marked[v] = false;
    }
}

void update(int v, int tl, int tr, int l, int r, int new_val)
{
    if (l > r)
        return;
    if (l == tl && tr == r)
    {
        if ()
            marked[v] = true;
    }
    else
    {
        push(v);
        int tm = (tl + tr) / 2;
        update(v * 2, tl, tm, l, min(r, tm), new_val);
        update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, new_val);
    }
}

int main()
{
}