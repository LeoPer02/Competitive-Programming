#include <bits/stdc++.h>
#define Leo   ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define INF 1e6 
using namespace std;
int n;
int dp[55][55], cuts[55];

// Retornar o custo do corte, ou seja, o tamanho do segmento antes do corte
int cost(int x, int y){
    return cuts[y] - cuts[x];
}

int solve(int x, int y){
    if ( x+1 == y) return 0;  // Significa que estamos a tentar cortar entre dois pontos sucessivos (exemplo, entre 1 e 2, que não é possivel)
    if ( dp[x][y] != -1 ) return dp[x][y];
    int temp = INF;
    for(int i = x+1; i < y; i++){
        temp = min(temp, solve(x, i) + solve(i, y) + cost(x,y));
        // minimo entre temp e o custo caso cortemos em i, que será o custo do segmento entre x<->i + i<->y + tamanho do segmento antes do corte
    }
    return temp;
}


int main(){
    LeozinGostozin
    int l;
    while(cin >> l, l){
        cin >> n;
        cuts[0] = 0;
        memset(cuts, 0, sizeof(cuts));
        for(int i = 1; i <= n; i++){
            cin >> cuts[i];
        }
        cuts[n+1] = l; 
        // Cortes em 0 e l são impossiveis, mas é preciso colocálos para calcular o tamanho do segmento
        memset(dp, -1, sizeof(dp));
        cout << "The minimum cutting is "<< solve(0, n+1) << endl;
    }
    return 0;
}
