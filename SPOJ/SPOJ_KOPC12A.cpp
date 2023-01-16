
#include <bits/stdc++.h>
/*
General Idea: Use Ternary search to find the wich the height k to wich the cost of resizing every building is minimal
We start between size 0 and an really high size, and then check the price for resizing both "middles", and we repeat that
until we find the optimal k

Time Complexity: O(n*log(n))
*/
using namespace std;

map<int, long long int> buildings;

long long int check(int x)
{
    long long int total = 0;
    for (auto it = buildings.begin(); it != buildings.end(); it++)
    {
        // cout << "Middle: " << x << " Val: " << it->first << " Cost: " << it->second << endl;
        total += abs(x - it->first) * it->second;
    }
    // cout << "Total: " << total << endl;
    return total;
}

int main()
{
    int cases, n, val;
    cin >> cases;
    // cout << "Cases: " << cases << endl;
    for (int i = 0; i < cases; i++)
    {
        cin >> n;
        long long int build[n];
        buildings.clear();
        long int max = 0;
        long int min = 9999999999;
        for (int j = 0; j < n; j++)
        {
            // cout << "First for" << endl;
            cin >> build[j];
            // Check for max and min on input to avoid sorting the array
            if (build[j] < min)
            {
                min = build[j];
            }
            else if (build[j] > max)
            {
                max = build[j];
            }
        }

        for (int j = 0; j < n; j++)
        {
            cin >> val;
            auto it = buildings.find(build[j]);
            if (it == buildings.end())
                buildings.insert({build[j], val});
            else
                it->second += val;
        }

        long long int low = min, high = max;
        long long int middle1 = 0, middle2 = 1;

        while (low < high)
        {
            middle1 = (low + (high - low) / 3), middle2 = high - (high - low) / 3;
            // cout << "Middle1: " << middle1 << " Value: " << check(middle1) << " Middle2: " << middle2 << " Value: " << check(middle2) << " Low: " << low << " High: " << high << endl;
            long long int f1 = check(middle1), f2 = check(middle2);
            if (f1 > f2)
            {
                low = middle1 + 1;
            }
            else
                high = middle2 - 1;

            // cout << "Still in while" << endl;
        }
        cout << check(high) << endl;
        // cout << "Cases: " << cases << endl;
    }
    return 0;
}
