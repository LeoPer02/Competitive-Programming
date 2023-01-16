#include <iostream>
using namespace std;

/*
General Idea: Run through every number between i and j, and check wich one has the longest cycle
Time complexity: O(n^2)
*/

int max2(int a, int b){
    if (a > b){
        return a;
    }
    return b;
}

int main(){
    int i, j, temp = 0, count = 1, max = -1;
    while(cin >> i >> j){
    for(int l = min(i,j); l <= max2(i,j); l++){
            temp = l;
        while(temp != 1){
            if(temp % 2 != 0){
                temp = 3*temp +1;
            }else{
                temp /= 2;
            }
            count++;
        }
        if(max < count){
            max = count;
        }
        count = 1;
        }
        printf("%d %d %d\n", i, j, max);
        max = 0;
    }
    return 0;
}