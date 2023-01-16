#include <bits/stdc++.h>

using namespace std;

/*
General Idea: In this problem we can apply binary search, in order to find the maximum minimum distance between cows
If we search between 1 (on the situation we have cows occuping all places) and lastIndex - firstIndex (in case we only have 2 cows) we
will get the max min distance between cows

Time Complexity: O(n* log(n))
*/

bool check(int pos[], int x, int numberCows, int n);

int main()
{
    int n, c, cases;
    cin >> cases;
    for (int i = 0; i < cases; i++)
    {
        cin >> n >> c;
        int pos[n];
        for (int j = 0; j < n; j++)
        {
            cin >> pos[j];
        }
        sort(pos, pos + n);
        // In the worst case, each cow is 1 space appart, in the "best" case theres only 2 cows and they are loccated at the begginig and the end
        long int low = 1;
        long int high = pos[n - 1] - pos[0];
        // cout << "Low: " << low << " High: " << high << endl;
        while (low <= high)
        {
            long middle = ((low + (high - low) / 2));
            // cout << "Middle: " << middle << " Low: " << low << " High: " << high << endl;
            //    Check if its possible to place C cows with minimal distance of middle between them
            //    If yes, Low = middle and we check if we can increase that distance
            if (check(pos, middle, c, n))
            {
                low = middle + 1;
                // cout << "Foi possivel com: " << middle << " Low: " << low << "  High: " << high << endl;
            }
            else
            {
                high = middle - 1;
                // cout << " Não Foi possivel com: " << middle << " Low: " << low << "  High: " << high << endl;
            }
        }
        cout << high << endl;
    }
    return 0;
}

bool check(int pos[], int x, int numberCows, int n)
{
    // The first cow is always placed in the first index
    int lastPlaced = pos[0];
    numberCows--;
    for (int i = 1; i < n; i++)
    {
        // If the distance between the last cow and the current one is greater than x, place a cow
        // cout << "X: " << x
        //     << " Pos[i]: " << pos[i] << " Last: " << lastPlaced << " Sub: " << pos[i] - lastPlaced << " NumberCows: " << numberCows << endl;
        if (pos[i] - lastPlaced >= x)
        {
            numberCows--;
            lastPlaced = pos[i];
            if (numberCows == 0)
            {
                // All the cows have been placed
                return true;
            }
        }
    }
    // In case we couldn't place all the cows with distance X return false
    return false;
}