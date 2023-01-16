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
        // cout << "Assign Start" << endl;
        // cout << "bit size: " << n << endl;
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
        // cout << "Assign End" << endl;
    }

    FenwickTree2D(vector<vector<int>> a) : FenwickTree2D(a.size())
    {
        // cout << "Add Init Start" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                add(i, j, a[i][j]);
            }
        }
        // cout << "Add Init End" << endl;
    }

    void set(int x, int y, int val)
    {
        // cout << "Set Start" << endl;
        this->bit[x][y] = val;
        // cout << "Set: " << x << " " << y << " to = " << bit[x][y] << endl;
        //  cout << "Set End" << endl;
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
        // cout << "Returning: " << sum << " for x: " << x << " y: " << y << endl;
        return sum;
    }

    int query(int x1, int y1, int x2, int y2)
    {
        return (query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1));
    }

    int sum(int x, int y)
    {
        // cout << "Sum Start" << endl;
        int ret = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
                ret += bit[i][j];

        // cout << "Sum End" << endl;
        return ret;
    }

    void add(int x, int y, int delta)
    {
        // cout << "Add Start" << endl;
        for (int i = x; i <= n; i += (i & -i))
            for (int j = y; j <= n; j += (j & -j))
                bit[i][j] += delta;
        // cout << "Add End" << endl;
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
        // cout << "OP: " << op << endl;
        while (op[0] != 'E')
        {
            if (op[1] == 'U')
            {
                cin >> x1 >> y1 >> x2 >> y2;
                // cout << "Sum [" << x2 << "," << y2 << "]: " << ftree.sum(x2, y2) << " - Sum [" << x1 << "," << y1 << "]: " << ftree.sum(x1, y1) << endl;
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