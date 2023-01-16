#include <bits/stdc++.h>

/*
General Idea: Store the bills in a multiset in increasing order, then take the highest and the lowest bill
subtract both, add to the total and remove those 2 bills from the urn

Time Complexity: O(n)
*/

using namespace std;
multiset<int> urn;

int main(){
    int n, val;
    long int c;
    cin >> n;
    while(n != 0){
        long int total = 0;
        urn.clear();
        for(int i = 0; i < n; i++){
            //Insert receipts
            cin >> c;
            for(int j = 0; j < c; j++){
                cin >> val;
                urn.insert(val*-1);
            }
            //Simulate Promotion
            auto highest = urn.begin();
            auto lowest = urn.rbegin();
            //cout << "Highest: " << *highest*-1 << " Lowest: " << *lowest*-1 << endl;
            total += (*highest*-1 - *lowest*-1);
            //cout << "Total: " << total << endl;
            urn.erase(--urn.end());
            urn.erase(urn.begin());
        }
        cout << total << endl;
        cin >> n;
    }
    return 0;
}