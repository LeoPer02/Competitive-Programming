
#include <bits/stdc++.h>

/*
General Idea: We can use Segment Trees, but instead of storing the values them selfs, we can store them as frequencies
So, if we had 1 1 2 2 2 2 7 7 7 that would become -> 2 2 4 4 4 4 3 3 3
That way we can search for the maximum number with the excepction
*consider the | as the limits of the query*
if we had the following query -> ------ 2 2 4 4 |4 4 3 3 3|  ---- 4 would not be the answear since we're not considering all of the elements that 
correspond to that frequency
Therefore, before making a query we need to check if this is the case, if it is, we can query from the end of the frequency that is "broken" until the end of
the actual query interval, and then compare with the frequency of the "broken" numbers
*Using the values above as an example*
 2 2 4 4 |4 4 3 3 3|
 in this case we would compare the result from a query on --- 2 2 4 4 4 4 |3 3 3| --- with the number of 4's that were included in the query
 in this case 2: (2 2 4 4 |<4 4> 3 3 3|)

Time Complexity: O(log n)
*/

using namespace std;

#define MAX 200005
#define MAX_BUF 16
#define MAX_ST 800005

#define NEUTRAL 0

long int n;          // Number of elements in the segtree
long int st[MAX_ST]; // Segtree (in this case storing interval sums)
map<long int, pair<int, pair<int, int>>> freq;
long int values[MAX];

// Merge contents of nodes a and b
long int merge(long int a, long int b)
{
    // Retornar o max, ou seja, a maior frequencia
    // Return max, that is, the highest frequency
    if (a > b)
        return a;
    else
        return b;
}

// Build initial segtree (in position pos, interval [start,end])
void build(long int pos, long int start, long int end)
{
    if (start == end)
    {
        // Instead of storing the value itself, we store its frequency
        // So, if we had 1 1 2 2 2 2 7 7 7 that would become -> 2 2 4 4 4 4 3 3 3
        // That way we reduce this problem to a "find the maximum" problem, with some exceptions
        auto it = freq.find(values[start - 1]);
        st[pos] = it->second.first;
    }
    else
    {
        long int middle = start + (end - start) / 2;
        build(pos * 2, start, middle);
        build(pos * 2 + 1, middle + 1, end);
        st[pos] = merge(st[pos * 2], st[pos * 2 + 1]);
    }
}

void update(long int pos, long int start, long int end, long int x, long int r)
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

long int query(long int pos, long int start, long int end, long int x, long int y)
{
    if (start > y || end < x)
        return NEUTRAL;
    if (start >= x && end <= y)
        return st[pos];

    long int middle = start + (end - start) / 2;
    long int a = query(pos * 2, start, middle, x, y);
    long int b = query(pos * 2 + 1, middle + 1, end, x, y);
    return merge(a, b);
}

int main()
{
    long int q, val1, val2;
    cin >> n;
    while (n != 0)
    {
        cin >> q;
        freq.clear();
        cin >> val1;
        values[0] = val1;
        long int last = val1;
        freq.insert({val1, {1, {1, 1}}});
        for (int i = 1; i < n; i++)
        {
            cin >> val1;
            values[i] = val1;
            if (val1 == last)
            {
                auto it = freq.find(val1);
                it->second.first += 1;
                it->second.second.second = i + 1;
            }
            else
            {
                freq.insert({val1, {1, {i + 1, i + 1}}});
                last = val1;
            }
        }
        build(1, 1, n);
        for (int i = 0; i < q; i++)
        {
            cin >> val1 >> val2;
            auto it = freq.find(values[val1 - 1]);
            auto it2 = freq.find(values[val2 - 1]);
            if (it == freq.end() || it2 == freq.end())
            {
                return -1;
            }

            if (it->second.second.first < val1)
            {
                // In case "end" is before val2
                if (it->second.second.second < val2 && it2->second.second.second <= val2)
                    cout << max((long int)it->second.second.second - val1 + 1, query(1, 1, n, it->second.second.second + 1, val2)) << endl;
                else if (it->second.second.second >= val2 && it->second.second.first <= val1)
                    cout << (val2 - val1) + 1 << endl;
                else
                {
                    cout << max(max((val2 - it2->second.second.first) + 1, (long int)it->second.second.second - val1 + 1), query(1, 1, n, it->second.second.second + 1, it2->second.second.first - 1)) << endl;
                }
            }
            else if (it2->second.second.second > val2)
                cout << max(query(1, 1, n, val1, it2->second.second.first - 1), (val2 - it2->second.second.first) + 1) << endl;
            else
                cout << query(1, 1, n, val1, val2) << endl;
        }
        cin >> n;
    }
}