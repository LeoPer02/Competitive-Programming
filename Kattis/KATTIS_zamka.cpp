#include <iostream>
using namespace std;

/*
Genereal Idea: We iterate through all numbers from i to j until we find the first number wich will be the lowest number
whose sum of digits is equal to X (i < j, and therefore the first number we find is also the lowest)
And apply the same idea from j to i, to get the highest number

Time COmplexity: O(n)
*/


// Returns the sum of all digits
int sumDig(long int a){
    int total = 0;
    while(a > 0){
        total += a%10;
        a /= 10;
    }
    return total;
}

int main(){
    long int i,j,x,min,max;
    cin >> i >> j >> x;
    for(int k = i; k <= j; k++){
        if(sumDig(k) == x){
            min = k;
            break;
        }
    }
    for(int k = j; k >= i; k--){
        if(sumDig(k) == x){
            max = k;
            printf("%ld\n%ld\n", min, max);
            return 0;
        }
    }
    return 0;
}