#include <bits/stdc++.h>
using namespace std;
#define INF 1e6

/*

General Idea: The given polygon is represented as a group of vertices. Through those vertices we can obtain the lines that form the polygon
A line is define by 2 points. We can use those 2 points to check if the flight path intercepts the polygon. Since the path is a vertical line
to check if it intersects the line we only need to check that, given the 2 points of the line, A and B, the X-coordinate of the path belongs
to the interval ]A.x, B.x[ or ]B.x, A.x[. If it does, in order to calculate the point of intersection we use the reduced equation of the line
y = mx + b                Since we have 2 points, we can get the equation, change the value of x to the Path.x and get the Y-coordinate of intersection 

From there, every time there's an intersection, there will be an even number of coordinates of intersection, so, by ordering the coordinates from high to low
we can subtract 2 by 2 the y values to get the final distance

Time Complexity: O(n)
*/
pair<double, double> inter(pair<int,int> linePoint1, pair<int,int> linePoint2, int path){
    // A equação da linha de voo -> x = path
    double declive = ((double)(linePoint1.second - linePoint2.second)/(double)(linePoint1.first - linePoint2.first));

    // Coeficiente Linear = y - m*x
    double coefLinear =  (double)(linePoint1.second - declive*linePoint1.first);
    // Isto dá-nos a equação reduzida da reta <-> y = mx + n
    // Com isto calculamos o valor de y da interseção
    double interY = declive*path + coefLinear;

    return make_pair((double)path, interY);
}

int main(){
    int cases;
    cin >> cases;
    while(cases--){
        int n;
        cin >> n;
        vector<pair<pair<int,int>, pair<int,int>>> lines; // Guardar as linhas do poligno
        int val1, val2;
        cin >> val1 >> val2;
        pair<int,int> first = make_pair(val1, val2);
        pair<int,int> lastPoint = first;
        for(int i = 1; i < n; i++){
            cin >> val1 >> val2;

            // Ordenar linha pelo ponto com menor x, assim sabemos que o x do outro ponto é >=, sendo assim mais facil saber quais linhas
            // Podem potencialmente intercetar o voo

            if(lastPoint.first > val1)
                lines.push_back(make_pair(make_pair(val1,val2), lastPoint));
            else
                lines.push_back(make_pair(lastPoint, make_pair(val1,val2)));

            lastPoint = make_pair(val1, val2);
        }
        // Fechar o poligno
        lines.push_back(make_pair(lastPoint, first));
        
        int thresh, path;
        cin >> thresh;
        cin >> path;
        
        // Iterar pelas linhas do poligno enquanto o x do ponto da linha com menor valor x for menor que path
        // Caso contrário a linha já não interceta o voo

        pair<double, double> inter1;
        double total = 0;
        // Vector que guarda os valores de y onde houve interseção
        vector<double> dist;
        for(long unsigned int i = 0; i < lines.size(); i++){
            if((lines[i].second.first > path && lines[i].first.first < path) || (lines[i].second.first < path && lines[i].first.first > path)){
                inter1 = inter(lines[i].first, lines[i].second, path);
                dist.push_back(inter1.second);
            } 
        }

        // Ordenar o vector para termos y em ordem crescente, para podermos obter o espaço entre interseções consequintes
        sort(dist.begin(), dist.end());
        for(long unsigned int i = 1; i < dist.size(); i+=2){
            total += dist[i] - dist[i-1];
        }
        if(total >= (double)thresh) cout << "YES\n";
        else cout << "NO\n";
        

    }
}