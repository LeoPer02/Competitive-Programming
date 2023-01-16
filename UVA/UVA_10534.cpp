#include <bits/stdc++.h>
using namespace std;
#define Leo   ios::sync_with_stdio(0);cin.tie(0);cout.tie(0); 

/*
General Idea: Apply the Longest Increasing Sequence(LIS) to the problem
We find the LIS from left to rigth and the LIS from right to left and see if they
connect

Time Complexity: O(n)
*/


using namespace std;
int n;

void LIS(int array[], int dp[])
{
    vector<int> values;
    for (int i = 0; i < n; i++)
    {
        // Find first number that is >= to array[i]
        long unsigned int idx = lower_bound(values.begin(), values.end(), array[i]) - values.begin();
        // If one does not exist, thats means its a decreasing subsequence, so we place the element in the vector
        if (idx == values.size())
            values.push_back(array[i]);
        else // If there is, swap values
            values[idx] = array[i];
        dp[i] = idx + 1;
    }
}

int main()
{
    Leo
    while (cin >> n)
    {
        int array[n];
        for (int i = 0; i < n; i++)
        {
            cin >> array[i];
        }
        int dp1[n], dp2[n];
        LIS(array, dp1);             // Calculate increasing subsequence
        reverse(array, array + n);   // Revert to calculate the higest increasing subsequence from right to left
        LIS(array, dp2);             // Calculate the increasing subsequence (Right to left)
        reverse(dp2, dp2 + n);       // Re order numbers

        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            ans = max(ans, min(dp1[i], dp2[i]));
            /*
            We seach the maximum between the 2 dps, we use min because:
            If we have 3 <-> 2, that means that we have 3 number increasing from left to right and
            2 decreasing from left to right. In that case, to get an equal number both increasing and
            decreasing we "remove" from the highest sequence so that they become equal, in this case, 2 <-> 2.
            */
        }

        cout << 2 * ans - 1 << endl;
    }
}