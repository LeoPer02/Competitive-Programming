#include <bits/stdc++.h>
#define INF 1e6

/*
General Idea: Apply the principals of the Coin Change problem but keeping in mind that we can get change back
in a way, we can surpass the price and get coins back

Time complexity: O(coins*price)

*/

using namespace std;
int values[] = {5, 10, 20, 50, 100, 200}, price;
int amount[6];
int dp[650];
float pricef;

int coinChange(int price, int f)
{
    if (price < -650 || price > 650)
        return INF;                 // If the value surpasses the desired on
    if (price <= 0 && f < 0)        
        return dp[-price];          // In case we get change
    else if (f < 0)       // If we have already tested all coins  
        return INF;
    else if (amount[f] == 0) // If we dont have any more of this coins, try the precious one
        return coinChange(price, f - 1);
    else
    {
        int ans1 = 0, ans2 = 0;
        amount[f]--;
        ans1 = coinChange(price - values[f], f); // Simulate the situation we use the coin
        amount[f]++;
        ans2 = coinChange(price, f - 1); // Simulate the situation we didnt use the coin
        return min(ans1 + 1, ans2);      // Get the minimum between both
        // +1 to count the current coin
    }
}

int main()
{
    memset(dp, INF, sizeof(dp)); // Inicialize dp by INF
    dp[0] = 0;
    for (int i = 0; i < 6; i++)
    {
        for (int j = values[i]; j < 650; j++)
        {
            dp[j] = min(dp[j], 1 + dp[j - values[i]]);
        }
    }
    while (true)
    {
        bool stop = true;
        for (int i = 0; i < 6; i++)
        {
            cin >> amount[i];
            if (amount[i] != 0)
                stop = false;
        }
        if (stop) // If every coin is 0
            return 0;
        cin >> pricef;
        price = pricef * 1000; // Multiply the number by 1000 so avoid rounding problems
        price /= 10;           // Divide by 10 to get the real value
        printf("%3d\n", coinChange(price, 5)); // Start on 200 ($2)
    }
    return 0;
}