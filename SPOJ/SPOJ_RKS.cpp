#include <bits/stdc++.h>

using namespace std;

map<int, int> freq;
map<int, int> pos;

typedef struct
{
    int freq;
    int pos;
    int num;
} value;


/*
General Idea: We store the values into 2 maps, one wich stores the frequency of each number, and the other the index of their first
appearence.
After that we place them into a vector of "values" (check struct above) and sort it, first by frequency and then by index

Time Complexity: O(n*log(n))
*/

int main()
{
    int n, c, val;
    cin >> n >> c;
    vector<value> arr;

    for (int i = 0; i < n; i++)
    {
        cin >> val;
        auto it = freq.find(val);
        if (it == freq.end())
        {
            freq.insert({val, 1});
        }
        else
        {
            it->second += 1;
        }
        it = pos.find(val);
        if (it == pos.end())
        {
            pos.insert({val, i});
        }
    }
    for (auto ite = freq.begin(); ite != freq.end(); ite++)
    {
        value tempValue;
        tempValue.freq = ite->second;
        tempValue.pos = pos[ite->first];
        tempValue.num = ite->first;
        arr.push_back(tempValue);
    }

    sort(arr.begin(), arr.end(), [](const value &a, const value &b)
         {
        if(a.freq > b.freq) return true;
        if(a.freq < b.freq) return false;
        return a.pos < b.pos; });

    for (long unsigned int i = 0; i < arr.size(); i++)
    {
        for (int j = 0; j < arr[i].freq; j++)
        {
            if (i == arr.size() - 1 && j == arr[i].freq - 1)
                cout << arr[i].num << endl;
            else
                cout << arr[i].num << " ";
        }
    }
    return 0;
}