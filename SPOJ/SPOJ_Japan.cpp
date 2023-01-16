#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
#define MAX 4005
#pragma GCC optimize("Ofast")
using namespace std;

vector<pair<int, int>> roads;

vector<int> bit; // binary indexed tree
int M;

int read(int idx)
{
    int sum = 0;
    while (idx > 0)
    {
        sum += bit[idx];
        idx -= (idx & -idx);
    }
    return sum;
}

void update(int idx, int val)
{
    while (idx <= M)
    {
        bit[idx] += val;
        idx += (idx & -idx);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int cases, east, west, N, K;
    scanf("%d ", &cases);
    for (int j = 0; j < cases; j++)
    {
        scanf("%d %d %d ", &N, &M, &K);
        bit.assign(M + 5, 0);
        roads.clear();
        while (K--)
        {
            scanf("%d %d ", &east, &west);
            roads.emplace_back(east, west);
        }
        sort(roads.begin(), roads.end());
        long int ans = 0;
        for (auto it = roads.begin(); it != roads.end(); it++)
        {
            update(it->second, 1);
            ans += read(it->second);
        }
        printf("Test Case %d: %ld\n", j + 1, ans);
    }
    return 0;
}