#include <bits/stdc++.h>
using namespace std;
// Closest pair of points problem
// Base code for the closest pair of points: https://www.geeksforgeeks.org/closest-pair-of-points-using-divide-and-conquer-algorithm/


  
// Distance between 2 points
long double dist(pair<long double, long double> p1, pair<long double, long double> p2) 
{ 
    return sqrt( (p1.first - p2.first)*(p1.first - p2.first) + 
                (p1.second - p2.second)*(p1.second - p2.second) 
            ); 
} 
long double dist2(pair<long double, long double> p1, pair<long double, long double> p2) 
{ 
    return sqrt( (p1.second - p2.second)*(p1.second - p2.second) + 
                (p1.first - p2.first)*(p1.first - p2.first) 
            ); 
} 
  
// Return the min
long double min(long double x, long double y) 
{ 
    return (x < y)? x : y; 
} 

// Brute force search of the closest pair
long double bruteForce(vector<pair<long double, long double>> pontos, int n) 
{ 
    long double min = FLT_MAX; 
    for (int i = 0; i < n; ++i) 
        for (int j = i+1; j < n; ++j) 
            if (dist(pontos[i], pontos[j]) < min) 
                min = dist(pontos[i], pontos[j]); 
    return min; 
} 


// Finds the minimum distance between 2 points of the strip
// Points are in increasing order of y, for that
// the coordinates were inverted and then sorted
// So point.first = y and point.second = x
long double stripClosest(vector<pair<long double, long double>> strip2, int size, long double d) 
{ 
    long double min = d; // Inicialize with minimum distance of d

    // Place the points inside the vector with inverted coordinates
    vector<pair<long double, long double>> strip;
    for(auto it = strip2.begin(); it != strip2.end(); it++){
        if(it->second != -1 && it->first != -1){
            strip.push_back(make_pair(it->second, it->first));
        }
    }
    sort(strip.begin(), strip.end());

    // Take all points and search if theres any with distance lower than min
    for (int i = 0; i < size; ++i) 
        for (int j = i+1; j < size && (strip[j].first - strip[i].first) < min; ++j) 
            if (dist2(strip[i],strip[j]) < min){ 
                min = dist2(strip[i], strip[j]);
            } 

    return min; 
}

long double DnC_util(vector<pair<long double, long double>> pontos, int n){
    if (n <= 3) 
        return bruteForce(pontos, n); 
  
    // Middle point
    int mid = n/2; 
    pair<long double, long double> midPoint = pontos[mid]; 
    long double dl = DnC_util(pontos, mid);
    vector<pair<long double, long double>> pontos2;
    for(int i = n-1; i >= mid; i--) pontos2.push_back(pontos[i]); 
    long double dr = DnC_util(pontos2, n - (mid)); 
  
    // Store the minimum distances between the left and right part of the vector
    long double d = min(dl, dr); 
  
    // Store on the strip all the points with distance to the line that passes through the middle point, lower than d
    vector<pair<long double, long double>> strip(n, {-1,-1}); 
    int j = 0; 
    for (int i = 0; i < n; i++) 
        if (abs(pontos[i].first - midPoint.first) < d) 
            strip[j] = pontos[i], j++; 
   

    // Find the points with the lowest distance and compare with min
    return min(d, stripClosest(strip, j, d) );
}

int main(){
    int n;
    while(cin >> n, n){
        vector<pair<long double, long double>> pontos;
        pontos.clear();
        for(int i = 0; i < n; i++){
            long double v1, v2;
            cin >> v1 >> v2;
            pontos.push_back(make_pair(v1, v2));
        }
        // sort points by X coordenates
        sort(pontos.begin(), pontos.end());
        long double res = DnC_util(pontos, n);
        
        if(res >= 10000.0) cout << "INFINITY\n";
        else printf("%0.4Lf\n", res);
    }
}