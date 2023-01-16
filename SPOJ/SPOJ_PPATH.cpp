#include <bits/stdc++.h>
#define MAX 10000
#define INF 1e6
using namespace std;

/*
General Idea: One node will have has his neightbours all integers that we can obtain by changing 1 bit (not changing the most significant bit to 0) that is also prime
    From there, applying bfs we can get the optimal path to the answear

Time Complexity: O((V + E)*sqrt(n))
*/

int countDigit(int n)
{
    if (n == 0)
        return 1;
    int count = 0;
    while (n != 0) {
        n = n / 10;
        ++count;
    }
    return count;
}

bool is_prime(int n) {
    // Assumes that n is a positive natural number
    // We know 1 is not a prime number
    if (n == 1) {
        return false;
    }

    int i = 2;
    // This will loop from 2 to int(sqrt(x))
    while (i*i <= n) {
        // Check if i divides x without leaving a remainder
        if (n % i == 0) {
            // This means that n has a factor in between 2 and sqrt(n)
            // So it is not a prime number
            return false;
        }
        i += 1;
    }
    // If we did not find any factor in the above loop,
    // then n is a prime number
    return true;
}

vector<int> calcChild(int u){
    vector<int> a;
    int size = countDigit(u);
    for(int i = 0; i < size; i++){
        int avoid = u % (int)pow(10, i+1);
        string s = std::to_string(u);
        for(int j = 0; j < 10; j++){
            if(j != avoid || (j != 0 || i != 0)){
                s.at(i) = j + '0';
                int num = stoi(s);
                if(num != u && is_prime(num)){
                    a.push_back(num);
                    //cout << "<" << s << ">" << endl;
                }
            }
        }
    }
    return a;
}

int main(){
    int cases, pri, res;
    cin >> cases;
    while(cases--){
        cin >> pri >> res;

        vector<int> adj;  // adjacency list representation

        queue<int> q;
        bool used[MAX];
        int d[MAX], p[MAX];
        memset(d, INF, sizeof(d));
        memset(p, INF, sizeof(p));
        memset(used, false, sizeof(used));
        q.push(pri);
        used[pri] = true;
        p[pri] = -1;
        d[pri] = 0;
        while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : (adj = calcChild(v))) {
            if (!used[u]) {
                used[u] = true;
                q.push(u);
                d[u] = d[v] + 1;
                p[u] = v;
            }
        }
    }
    if(d[res] == INF) cout << "Impossible\n";
    else cout << d[res] << endl;

    }
}