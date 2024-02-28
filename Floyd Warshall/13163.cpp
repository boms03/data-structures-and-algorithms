#include<iostream>
#include<vector>
#include<string>
#include<map>
using namespace std;

int n,m,r,k;
int nNaeilo[101][101];
int yNaeilo[101][101];
map<string,int>cities;
vector<string>trip;


void floyd(){
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i==j)continue;
                nNaeilo[i][j] = min(nNaeilo[i][j],nNaeilo[i][k]+nNaeilo[k][j]);
                yNaeilo[i][j] = min(yNaeilo[i][j],yNaeilo[i][k]+yNaeilo[k][j]);
            }
        }
    }
}

int main(){

    cin >> n >> r;
    
    for(int i=1; i<=n; i++){
        string city;
        cin >> city;
        cities[city] = i;
    }

    cin >> m;

    for(int i=0; i<m; i++){
        string tripCity;
        cin >> tripCity;
        trip.push_back(tripCity);
    }

    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(i!=j){
                nNaeilo[i][j]=1e9;
                yNaeilo[i][j]=1e9;
            }
        }
    }

    cin >> k;

    for(int i=0; i<k; i++){
        string type, start, dest;
        int cost;
        cin >> type >> start >> dest >> cost;
        int s = cities[start];
        int d = cities[dest];

        nNaeilo[s][d] = min(nNaeilo[s][d],cost);
        nNaeilo[d][s] = min(nNaeilo[d][s],cost);

        if(type=="Mugunghwa" || type == "ITX-Saemaeul" || type == "ITX-Cheongchun"){
            yNaeilo[s][d] = 0;
            yNaeilo[d][s] = 0;
        }
        else if(type=="S-Train" || type == "V-Train"){
            yNaeilo[s][d] = min(yNaeilo[s][d],cost/2);
            yNaeilo[d][s] = min(yNaeilo[d][s],cost/2);
        }
        else {
            yNaeilo[s][d] = min(yNaeilo[s][d],cost);
            yNaeilo[d][s] = min(yNaeilo[d][s],cost);
        }
    }

    floyd();

    int sumY = 0, sumN = 0;

    for(int i=0;i<m-1;i++){
        int s = cities[trip[i]];
        int e = cities[trip[i+1]];

        sumY += yNaeilo[s][e];
        sumN += nNaeilo[s][e];
    }
    sumY+=r;
    if(sumY<sumN) cout << "Yes";
    else cout << "No";
}

/*
    Approach:
        Use floyd warshall as it requires all pair distances.
        (!) Initalizing cost matrixes is the key
        Use map to hash city since duplication is not allowed
        Use two cost matrixes to calculate one with naeilo previlege and the other without naeilo previlege
        Only record the cheapest cost when initilazing the cost matrixes.
        Type matters only for the naeilo previlege.
            1] "Mugunghwa", "ITX-Saemaeul", "ITX-Cheongchun" : free
            2] "S-Train" "V-Train" : cost/2
        Then perform floyd warshall
        
    Time Complexity:
        O(N^3)
*/