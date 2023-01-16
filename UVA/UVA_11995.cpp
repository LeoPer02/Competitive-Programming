#include <bits/stdc++.h>

/*
General Idea: Create a stack a queue and a priority_queue and apply the commands to all of them
If at any point some operation yields a different result than expected or its not at all possible
ativate a flag so that at the end we can compare the data structs and see if one, more or any, behaved 
correctly according to the input

Time Complexity: O(n)
*/

using namespace std;

stack<int> s;
queue<int> q;
priority_queue<int> pq;

int main(){
    int n, op, val;
    while(cin >> n){
        while(!s.empty() && !q.empty() && !pq.empty()){
            s.pop();
            q.pop();
            pq.pop();
        }
        bool sB = true, qB = true, pqB = true, leastOneInput = false, empty = true, popEmpty = false;
        if(n > 0) empty = false;
        for(int i = 0; i < n; i++){
            cin >> op >> val;
            if(op == 1){
                leastOneInput = true;
                s.push(val);
                q.push(val);
                pq.push(val);
            }else{

                if(s.empty() || q.empty() || pq.empty()){
                    popEmpty = true;
                }

                if(!s.empty() && val != s.top()){
                    sB = false;
                }
                if(!s.empty())
                s.pop();

                if(!q.empty() && val != q.front()){
                    qB = false;
                }
                if(!q.empty())
                q.pop();

                if(!pq.empty() && val != pq.top()){
                    pqB = false;
                }
                if(!pq.empty())
                pq.pop();

            }
        }
        if((!leastOneInput && !empty) || popEmpty){
            cout << "impossible" << endl;
        }
        else if((sB && qB) || (sB && pqB) || (pqB && qB) || (sB && qB && pqB) || empty){
            cout << "not sure" << endl;
        }else if(!sB && !qB && !pqB){
            cout << "impossible" << endl;
        }else if(sB){
            cout << "stack" << endl;
        }else if(qB){
            cout << "queue" << endl;
        }else{
            cout << "priority queue" << endl;
        }
    }
    return 0;
}