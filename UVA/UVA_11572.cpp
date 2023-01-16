#include <bits/stdc++.h>

using namespace std;

/*
General Idea: We want to know the longest sequence of snowflakes that are different from each other
For that we can do a linear search with a twist. 
We keep track of the snowflakes that apperead and When they appeared (their index)
If we stumble upon a snowflake that has already apperead, we check if the current count is higher than the max
and if true, update the max, and then we check whats the last position in wich the current snowflake appeared,
then we remove every element of the map whose index is <= to the position that the current element appeared before
Example
1 -> 0
2 -> 1
3 -> 2
2 -> 3
3 -> 4
1 -> 5

Once we reach the element with index 3 (the number 2), since its repeated, we remove every element whose index belongs to
the interval [0, 1] and start counting again from index 3 (Wich is same as keep counting but adding to the total CurrentIndex - StartingIndex)

Time Complexity: O(n)
*/

map<int,int> m;

int main(){
    int n, c;
    long long int a, temp= 0, max= 0;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> c; 
        m.clear();
        max = 0, temp = 0;
        for(int j = 0; j< c; j++){
            cin >> a;
            auto search = m.find(a);
            // Check to see if the element isnt the bag
            if(search == m.end()){
                m.insert({a, j});
                temp++;
            }else{
                // Atualizar Temp
                if(max < temp){
                    max = temp;
                }
                temp = j - search->second;
                // Remove elements that appeared preciously to the starting element
                for(auto it = m.cbegin(); it != m.end(); ){
                    if(it->second <= search->second){
                        m.erase(it++);
                    }else{
                        ++it;
                    }
                }
                m.insert({a, j});

            }

        }
        if(temp > max){
            max = temp;
        }
        cout << max << endl;
        
    }
}