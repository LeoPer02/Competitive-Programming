#include <iostream>
using namespace std;

/*
Genreal Idea: If the frog jumps, first to the right a units and then b units to the left
Since he start on 0, we know that  we will end up at (a-b)*(t/2) if the number of jumps is even
and (a-b)*(t/2) + a if the number of jumps is odd

Time Complexity: O(n), O(1) for each of the n cases;
*/

int main(){
    long long int a,b,t, n;
    cin >> n;
    for(int k = 0; k < n; k++){
        cin >> a >> b >> t;
        if(t%2 == 0){
            printf("%lld\n", (a-b)*(t/2));
        }else{
            printf("%lld\n", (a-b)*(t/2) + a);
        }
    }
    return 0;
}