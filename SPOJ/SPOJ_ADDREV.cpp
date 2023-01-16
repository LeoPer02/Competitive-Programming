#include <iostream>
#include <cmath>
using namespace std;

/*
General Idea: Reverse both numbers, add the reverse numbers, and finally reverse the result

Time Complexity: O(n)
*/


// Count the number of digits
int digits(long int a){
    int cont = 0;
    while(a > 0){
        a /= 10;
        cont++;
    }
    return cont;
}

long int reverse(long int a){
    int ordem = digits(a)-1;
    long int n = 0;
    while(a > 0){
        n += (a%10)*(int)(pow(10,ordem));
        a /= 10;
        ordem--;
    }
    return n;
}

int main(){
    long int a,b;
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> a >> b;
        printf("%ld\n", reverse(reverse(a)+reverse(b)));
    }
    return 0;
}