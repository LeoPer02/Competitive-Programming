#include <bits/stdc++.h>
using namespace std;
/*
    General Idea: Start from the right to the left, and, a mountain will have a light up side if its height its greater than all other mountain peaks to its right
    For that we keep a variable that stores the highest peak so far.
    Once we dectect a mountain peak greater than the max, we calculate the distance thats its affected by light (whose Y-coordinate is greater than max) and then update
    the max variable.

    Time Complexity: O(n)
*/

map<int,int> points;

double euclidean(int a1, int a2, int b1, int b2){
    return sqrt(pow((double) (a1-b1), 2) + pow((double) (a2-b2), 2));
}

int main(){
    int cases;
    cin >> cases;
    while(cases--){
        int n;
        cin >> n;
        points.clear();
        for(int i = 0; i < n; i++){
            int val1, val2;
            cin >> val1 >> val2;
            val1 *= -1; // Store points from right to left
            points.insert({val1, val2});
        }
        
        double max = 0;
        long double total = 0;
        pair<int, int> lastPoint = make_pair(-1,-1);
        for(auto it = points.begin(); it != points.end(); it++){
            if(it->second > max){ // Y-coordinate is higher than therefore theres light coming through

                if(lastPoint.second == 0) total += euclidean(abs(it->first), it->second, lastPoint.first, lastPoint.second); // If the mountain side base is 0 then we simply calculate the euclidian distance
                else total += euclidean(abs(it->first), it->second, lastPoint.first, lastPoint.second)*((double)it->second - max)/((double) (it->second - lastPoint.second)); // we apply the rule of three
                max = it->second; // update max
            }
            lastPoint = make_pair(-it->first, it->second); // store latest point
            //cout << "LastPoint: " << lastPoint.first << "  " << lastPoint.second << endl;
        }
        printf("%0.2Lf\n", total);
    }
}