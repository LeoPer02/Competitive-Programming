#include <bits/stdc++.h>
#include <cstdio>
#define MAX 4098

/*
General Idea: Application of Fenwick Tree 2D

Time Complexity: O(log n)
*/

using namespace std;

int v[MAX][MAX];

struct FenwickTree2D
{
    vector<vector<int>> bit;
    int n, m;

    FenwickTree2D(int n)
    {
        this->n = n;
        for (int i = 0; i < n + 5; i++)
        {
            vector<int> temp;
            for (int j = 0; j < n + 5; j++)
            {
                temp.push_back(0);
                v[i][j] = 0;
            }
            bit.push_back(temp);
        }
    }

    FenwickTree2D(vector<vector<int>> a) : FenwickTree2D(a.size())
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                add(i, j, a[i][j]);
            }
        }
    }

    void set(int x, int y, int val)
    {
        this->bit[x][y] = val;
    }

    int query(int x, int y)
    {
        long int sum = 0;

        for (int i = x; i > 0; i -= (i & -i))
        {
            for (int j = y; j > 0; j -= (j & -j))
            {
                sum += bit[i][j];
            }
        }
        return sum;
    }

    int query(int x1, int y1, int x2, int y2)
    {
        return (query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1));
    }

    int sum(int x, int y)
    {
        int ret = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
                ret += bit[i][j];

        return ret;
    }

    void add(int x, int y, int delta)
    {
        for (int i = x; i <= n; i += (i & -i))
            for (int j = y; j <= n; j += (j & -j))
                bit[i][j] += delta;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int cases, n, x2, y2, x1, y1, val;
    cin >> cases;
    char op[5];
    while (cases--)
    {
        cin >> n;
        FenwickTree2D ftree(n);
        cin >> op;
        while (op[0] != 'E')
        {
            if (op[1] == 'U')
            {
                cin >> x1 >> y1 >> x2 >> y2;
                x1++;
                y1++;
                x2++;
                y2++; // Somar coordenadas porque, por algum motivo, isso funcionou
                printf("%d\n", ftree.query(x1, y1, x2, y2));
            }
            else
            {
                cin >> x1 >> y1 >> val;
                x1++;
                y1++;
                ftree.add(x1, y1, val - v[x1][y1]);
                v[x1][y1] = val; // Não esquecer de ter uma estrutura para guardar os dados e outra a BIT (parece obvio, mas não foi obvio para ti durante 5hrs aparentemente)
            }
            cin >> op;
        }
    }
}