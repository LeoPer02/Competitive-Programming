#include <bits/stdc++.h>
/*
General Idea: For each taks, multiply its period by the number of iterations and place it into a priority_queue 
and then simply starting removing the elements from the pq, and they will leave in the correct order

Time Complexity: O(n)

*/
using namespace std;

class comparator{
    public:
    bool operator()(pair<int,int> a, pair<int,int> b){
        if(a.second==b.second){
            return a.first > b.first;
        }
        return a.second > b.second;
    }
};

priority_queue<pair<int,int>, vector<pair<int,int>>, comparator> tasks;
multiset<pair<int,int>> tempSet;

int main(){
    string tmp;
    int id, interval, k;
    cin >> tmp;
    while(tmp != "#"){
        cin >> id >> interval;
        tempSet.insert({id, interval});
        cin >> tmp;
    }

    cin >> k;
    for(int i = 0; i < k; i++){
        for(auto x : tempSet){
            tasks.push({x.first, x.second*(i+1)});
        }
    }
    tempSet.clear();
    for(int i = 0; i < k; i++){
        cout << tasks.top().first << endl;
        tasks.pop();
    }
    return 0;
}