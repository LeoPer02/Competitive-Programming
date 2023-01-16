#include <bits/stdc++.h>
#define MAX 1000

/*
General Idea: Apply the Kadana algorithm to an matrix

Time Complexity: O(columns*columns*rows)
*/

using namespace std;

int n;
long int col[MAX];

long int kadane()
{
    long int sum = 0, max = INT32_MIN;
    bool pos = false; // Check if exists at least one positive (or zero)
    int min = INT16_MIN;
    for (int i = 0; i < n; i++)
    {
        if (*(col + i) >= 0) // If its positive or zero, change flag to true
            pos = true;

        if (*(col + i) < 0) // Get the highest negative
        {
            if (min < *(col + i))
            {
                min = *(col + i);
            }
        }
        sum += *(col + i);
        if (sum > max)
        {
            max = sum;
        }
        if (sum < 0)
        {
            sum = 0;
        }
    }
    if (!pos) // If there's no positive numbers, return the highest negative
        return min;
    return max;
}

int main()
{
    cin >> n;

    int v[n][n], sums[n][n];
    long int maxSum = INT16_MIN;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> v[i][j];
        }
    }

    // Cumulative sum left to right
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == 0)
            {
                // Keep the first element the same
                sums[i][j] = v[i][j];
            }
            else
            {
                // Sum the value of v[i][j] to sums[i][j-1] that is, replace the current value by its sum with the line cumulative sum
                sums[i][j] = v[i][j] + sums[i][j - 1];
            }
        }
    }

    // Find the highest sum
    for (int i = 0; i < n; i++) // Start in collumn i
    {
        memset(col, 0, n - i);      // Reset col
        for (int j = i; j < n; j++) // iterate through all columns after i
        {
            int k = 0;
            for (k = 0; k < n; k++) // Iterate through all lines
            {
                if (i == 0)
                {   // if i == 0, then we are at the left limit, value is static
                    col[k] = sums[k][j];
                }
                else
                {
                    // sums[k][j] - sums[k][i-1] gives us the cumulative sum as if the had started adding from column i
                    col[k] = sums[k][j] - sums[k][i - 1];
                }
            }
            maxSum = max(kadane(), maxSum); // Check if line Kadane is higher then maxSum
        }
    }
    cout << maxSum << endl;
}