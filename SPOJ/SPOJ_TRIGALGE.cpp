#include <bits/stdc++.h>

/*
General Idea: Apply bisection (binary search) on the graph, from 0 and an really high number
Stop only when the the difference between the high and the low is less than the precision

Time Complexity: O(log n)
*/

using namespace std;

// Return the result from the expression
double func(int a, int b, int c, double x){
    return a*x + b*sin(x) - c;
}

int main(){
    int cases, a, b, c;
    cin >> cases;
    for(int i = 0; i < cases; i++){
        cin >> a >> b >> c;
         // If we check the function graph, it will be strictly increasing
         // that way we know for sure that the low is lower than the high (No "pits" in the graph)
         // Execute while f(high) - f(low) > 1 * 10^-6, in this case 10^-6 is the precision 
         long double low = 0.0, high = 9999999.0, middle;
        while(func(a,b,c,high) - func(a,b,c,low) > 1e-6){
            middle = low + (high - low)/2.0;
            
            if(func(a,b,c,middle) > 0.0) high = middle; 
            else low = middle;                          
                                                        
    }
    printf("%.6Lf\n", middle);
    }
    return 0;
}