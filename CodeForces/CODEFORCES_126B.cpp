#include <bits/stdc++.h>
using namespace std;
int n;
char s[1000005];
#pragma GCC optimize("Ofast")

// Base code for KMP algorithm: https://cp-algorithms.com/string/prefix-function.html#final-algorithm

/*
General Idea: Apply the KMP algorithm to verify if the prefix is the same as the suffix and then check if the suffix/prefix occurs atleast once
within the word

Time Complexity: O(n)
*/


// KMP alg
vector<int> prefix_function() {
    vector<int> pi(1000005);
    int j = 0;
    for (int i = 2; i <= n; i++) {
        while (j > 0 && s[i] != s[j+1])
            j = pi[j];
        if (s[i] == s[j+1])
            j++;
        pi[i] = j;
    }
    return pi;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >>(s+1);
    //cout << "<" << s+1 << ">\n";
    n = strlen(s+1);
    auto res = prefix_function();
    int size = res[n];
    //cout << "Size: " << size << endl;
    if(size <= 0) {
        cout << "Just a legend\n";
        return 0;
    }
    vector<int> used(1000005, 0);
    for(int i = 2; i < n; i++){
        used[res[i]]++;
    }

    int f = 0;
    for(int i = n; i>1; ){
        if(res[i] == 0) break;
        if(used[res[i]] > 0){
            f = res[i];
            break;
        }
        i = res[i];
    }
    if(f == 0){
        cout << "Just a legend\n";
        return 0;
    }

    for(int i = 1; i <= f; i++) printf("%c", s[i]);
    printf("\n");


    
} 