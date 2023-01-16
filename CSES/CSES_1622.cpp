#include <iostream>
#include <cstring>
#include <ctype.h>
#include <set>
using namespace std;
set<string> difStrings;

/*
General Idea: Use a recursive function to, in each state, add a different character from the original string
For example, if we have a = "" and b ="ab", we create 2 instances
1 -> a="a" and b = "b"
2 -> a="b" and b = "a"

and keep iterating through the the chars of b until its empty
When we reach that point, store the string in a set (to avoid copies)

Time Complexity: O(n)
*/

void create(string a, string b);

int main(){
    string a;
    cin >> a;
    create("", a);
    printf("%ld\n", difStrings.size());
    while(!difStrings.empty()){
        cout << *difStrings.begin() << endl;
        difStrings.erase(difStrings.begin());
    }
    return 0;
}

void create(string a, string b){
        if(b.length() == 0){
            difStrings.insert(a);
            return;
        }
        for(long unsigned int i = 0; i < b.length(); i++){
            create(a + b.at(i), b.substr(0,i) + b.substr(i+1));
        }
    return;
}