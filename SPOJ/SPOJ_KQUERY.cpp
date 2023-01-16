#include <bits/stdc++.h>
#define MAX 120005
#pragma GCC optimize("Ofast")
using namespace std;

struct el
{
    map<int, int> els;
};

el t[MAX];
int n;

el combine(el a, el b)
{
    for (auto it = b.els.begin(); it != b.els.end(); it++)
    {
        a.els[it->first]++;
    }
    return a;
}

void build(int a[], int v, int tl, int tr)
{
    if (tl == tr)
    {
        t[v].els.insert({-1 * a[tl], 1});
    }
    else
    {
        int tm = (tl + tr) / 2;
        build(a, v * 2, tl, tm);
        build(a, v * 2 + 1, tm + 1, tr);
        t[v] = combine(t[v * 2], t[v * 2 + 1]);
    }
}

int sum(int v, int tl, int tr, int l, int r, int k)
{
    if (l > r)
        return 0;
    if (l == tl && r == tr)
    {
        int count = 0;
        if (t[v].els.size() == 0)
            return 0;
        for (auto it = t[v].els.begin(); it != t[v].els.end(); it++)
        {
            if (it->first < k)
                count += it->second;
            else
            {
                return count;
            }
        }
        return count;
    }
    int tm = (tl + tr) / 2;
    return sum(v * 2, tl, tm, l, min(r, tm), k) + sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, k);
}

int main()
{
    cin.tie(0);
    scanf("%d\n", &n);
    int v[n], a, b, k, q;
    for (int i = 0; i < n; i++)
    {
        scanf("%d ", &v[i]);
    }
    scanf("%d\n", &q);
    build(v, 1, 0, n - 1);
    while (q--)
    {
        cin >> a >> b >> k;
        printf("%d\n", sum(1, 0, n - 1, --a, --b, (k * -1)));
    }
    return 0;
}
