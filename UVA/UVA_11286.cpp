#include <bits/stdc++.h>
#include <string>

using namespace std;
map<string, int> insc;

/*
General Idea: Read the classes numbers into an array, order that array and convert it into an string, that way we can identify the same combination even
if the order is diferent, after that add it to a map, or if its already in there, increment the number of times it appeared.


In the end iterate through the map and add all of the combinations that the highest frequency
*/

int main(){
    int c;
    long int max = 0;
    int array[5];
    cin >> c;
    while(c != 0){
        for(int i = 0; i < c; i++){
            for(int j = 0; j < 5; j++){
                cin >> array[j];
            }
            sort(array, array + 5);
            string b ="";
            for(int j = 0; j < 5; j++){
                b += to_string(array[j]);
            }
            auto search = insc.find(b);
            int aux =0;
            if(search == insc.end()){
                insc.insert({b, 1});
                aux = 1;
            }else{
                search->second += 1;
                aux = search->second;
            }
            if(aux > max){
                    max = aux;
            }
        }
        int count = 0;
        for (auto const& x : insc)
            {
                if(x.second == max){
                    count+= x.second;
                
                }
            }
        insc.clear();
        cout << count << endl;
        max = 0;
        cin >> c;
    }
}