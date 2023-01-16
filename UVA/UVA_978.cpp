#include <bits/stdc++.h>

using namespace std;

/*
General Idea: Assign 1 lemming from each color to every battlefield starting from the strongest, and simulate a fight (Subtracting life points) 
Repeat the process until one, or both, of the sides as 0 lemmings

Time Complexity: O(n)
*/

multiset<int> blue;
multiset<int> green;

int main(){
    int n, val;
    cin >> n;
    long int b, sb, sg;
    for(int i = 0; i < n; i++){
        cin >> b >> sg >> sb;
        green.clear();
        blue.clear();

        //Read Green Lemmings
        for(int j = 0; j < sg; j++){
            cin >> val;
            green.insert(val*-1);
        }

        //Read Blue Lemmings
        for(int j = 0; j < sb; j++){
            cin >> val;
            blue.insert(val*-1);
        }

        //Simulation of the battles
        int temp;
        multiset<int> greenSoldiers;
        multiset<int> blueSoldiers;
        while(!blue.empty() && !green.empty()){
            auto itG = green.cbegin();
            auto itB = blue.cbegin();
            //cout << "Avaible Greens: " << green.size() << " Avaible Blues: " << blue.size() << endl;
            greenSoldiers.clear();
            blueSoldiers.clear();
            for(int j = 0; j < b; j++){
                //cout << "Iteração " << j << " Green: " << green.size() << " Blue: " << blue.size() << endl;
               // Separate the lemmings who will fight from the ones who wont
               if(itG != green.end()){
               greenSoldiers.insert(*itG);
               //cout << "Drafted Green: " << *itG*-1 << "   ";
               itG++;
               }

               if(itB != blue.end()){
               blueSoldiers.insert(*itB);
               //cout << "Drafted Blue: " << *itB*-1 << endl;
               itB++;
               }
                
            }
            itG = greenSoldiers.begin();
            itB = blueSoldiers.begin();
            for(int j = 0; j < b; j++){
                //cout << "Green soldier: " << *itG*-1 << " Blue Soldier " << *itB*-1 << endl;
                if(itG == greenSoldiers.end() && itB == blueSoldiers.end()){
                    break;
                }else if(itG == greenSoldiers.end()){
                    break;
                }else if(itB == blueSoldiers.end()){
                    break;
                }

                if(*itG == *itB){
                    // Search the first element with value X to avoid removing duplicates
                    auto er = green.find(*itG);
                    if(er != green.end())
                    green.erase(er);

                    er = blue.find(*itB);
                    if(er != blue.end())
                    blue.erase(er);
                }else if(*itG < *itB){
                    temp = *itG*-1 - *itB*-1;

                    auto er = blue.find(*itB);
                    if(er != blue.end())
                    blue.erase(er);

                    er = green.find(*itG);
                    if(er != green.end())
                    green.erase(er);

                    green.insert(temp*-1);
                }else{
                    temp = *itB*-1 - *itG*-1;
                    
                    auto er = blue.find(*itB);
                    if(er != blue.end())
                    blue.erase(er);

                    er = green.find(*itG);
                    if(er != green.end())
                    green.erase(er);

                    blue.insert(temp*-1);
                }
                itG++;
                itB++;
            }
        }
        if(green.empty() && !blue.empty()){
            cout << "blue wins" << endl;
            for(auto x = blue.begin(); x != blue.end(); ++x){
                cout << *x*-1 << endl;
            }
            if(i != n-1)
            cout << endl;
        }else if(blue.empty() && !green.empty()){
            cout << "green wins" << endl;
            for(auto x = green.begin(); x != green.end(); ++x){
                cout << *x*-1 << endl;
            }
            if(i != n-1)
            cout << endl;
        }else{
            cout << "green and blue died" << endl;
            if(i != n-1)
            cout << endl;
        }
    }
    return 0;
}