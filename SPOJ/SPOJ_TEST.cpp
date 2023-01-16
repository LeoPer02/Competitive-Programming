#include <iostream>
using namespace std;

/*
General Idea: Research the meaning of life and the universe

*if you need help: https://news.mit.edu/2019/answer-life-universe-and-everything-sum-three-cubes-mathematics-0910*

Time Complexity: O(42)

*/

int main(){
    int val;
    while(cin >> val){
        if(val != 42){
            printf("%d\n", val);
        }
        else{
            return 0;
        }
    }
}