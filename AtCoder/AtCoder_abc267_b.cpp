#include <iostream>
using namespace std;
char grid[7][4];

/*
Genereal Idea: Store the values in a array, and check to see if all the conditions are true

Time Complexity: O(n)
*/

void checkrules(char a){
    bool contCol[7];
    int temp=0;
    if(a == '1') {
        printf("No\n");
        return;
    }else{
        for(int i = 0; i < 7; i++){
            for(int j = 0; j< 4; j++){
                if(grid[i][j] == '1'){
                    temp++;
                }
            }
            if(temp > 0) contCol[i] = 1;
            else contCol[i] = 0;
            temp = 0;
        }
        temp =0;
        for(int i = 0; i < 7; i++){
            if(contCol[i] == 1) temp++;
        }
        if(temp >= 2){
            bool zero = false;
            for(int i = 0; i < 7; i++){
                if(contCol[i] == 1){
                    for(int j = i+1; j < 7; j++){
                        if(contCol[j] == 0) zero = true;
                        else if(contCol[j] == 1 && zero == true){
                            printf("Yes\n");
                            return;
                        }else{
                            break;
                        }
                    }
                    zero = false;
                }
            }
        }else{
            printf("No\n");
            return;
        }
    }
    printf("No\n");
    return;
}

int main(){
    string a;
    cin >> a;

    for(int i = 0; i<7; i++){
        for(int j = 0; j < 4; j++){
            grid[i][j] = 'x'; // x meaning empty space
        }
    }

    grid[3][0] = a.at(0);
    grid[2][1] = a.at(1);
    grid[4][1] = a.at(2);
    grid[1][2] = a.at(3);
    grid[3][2] = a.at(4);
    grid[5][2] = a.at(5);
    grid[0][3] = a.at(6);
    grid[2][3] = a.at(7);
    grid[4][3] = a.at(8);
    grid[6][3] = a.at(9);
 
    checkrules(a.at(0));
 
    return 0;
}