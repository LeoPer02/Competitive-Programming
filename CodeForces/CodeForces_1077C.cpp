#include <iostream>
#include <list>
using namespace std;

/*
Genereal Idea: An array is good if the one elements represents the sum of all the other elements
Therefore we know that only 2 elements in each array can be the sum of the rest, the highest number
and the second highest number (in case we remove the highest).

For that, we can iterate trough the array, calculate the total and get the 2 highest numbers
Then iterate again through the array, check the total without the i-th element and check if its
equal to the highest number (or the second highest if i == max)

Time complexity: O(n)

*/

int main(){
    int n, max = 0, max2 = 0,maxv = 0, max2v = 0;
    long long unsigned int total = 0;
    cin >> n;
    list<int> lista;
    int array[n];
    // Get the 2 highest numbers on the array and their respective position and the total sum of all elements
    for(int i = 0; i <n; i++){
        scanf("%d", &array[i]);
        total += array[i];
        if (array[i] > max2v && array[i] > maxv){
            max2 = max;
            max = i;
            max2v = maxv;
            max2 = max;
            maxv = array[max];
        }else if(array[i] > max2v && array[i] < maxv){
            max2 = i;
            max2v = array[max2];
        }else if(array[i] > max2v && array[i] == maxv){
            max2 = max;
            max2v = array[max2];
        }
    }
    // Iterate through the array
    // If removing the element makes the total (without that element) equal the max1 or the max2
    // then add-it to the list
    for(int i = 0; i < n; i++){
        if(array[i] != maxv){
            if(total-(long unsigned int)array[i]-maxv == (long unsigned int)maxv){
                lista.push_back(i);
            }
        }else if(array[i] == maxv){
            if(total-(long unsigned int)array[i]-max2v == (long unsigned int)max2v){
                lista.push_back(i);
            }
        }
    }
    // Print the number of elemets and those elements
    if(lista.size() != 0){
    printf("%ld\n", lista.size());
    for(long long unsigned int i = 0; !lista.empty(); i++){
        printf("%d ", lista.front()+1);
        lista.pop_front();
    }
    return 0;
    }
    printf("0\n");
    return 0;
}