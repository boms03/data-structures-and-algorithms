#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;

int result[6][3];
vector<pair<int,int>>pairs = {{0,1},{0,2},{0,3},{0,4},{0,5},
                     {1,2},{1,3},{1,4},{1,5},
                     {2,3},{2,4},{2,5},
                     {3,4},{3,5},
                     {4,5}};
bool btk(int idx){
    if(idx==15){
        for(int i=0;i<6;i++){
            for(int j=0;j<3;j++){
                if(result[i][j]) return false;
            }
        }
        return true;
    }

    int p1= pairs[idx].first;
    int p2= pairs[idx].second;

    if(result[p1][1]&&result[p2][1]){
        result[p1][1]--;
        result[p2][1]--;
        if(btk(idx+1)) return true;
        result[p1][1]++;
        result[p2][1]++;
    }

    if(result[p1][0]&&result[p2][2]){
        result[p1][0]--;
        result[p2][2]--;
        if(btk(idx+1)) return true;
        result[p1][0]++;
        result[p2][2]++;
    }

    if(result[p1][2]&&result[p2][0]){
        result[p2][0]--;
        result[p1][2]--;
        if(btk(idx+1)) return true;
        result[p2][0]++;
        result[p1][2]++;
    }
    return false;
}

int main(){
    for(int k=0;k<4;k++){
        for(int i=0;i<6;i++){
            for(int j=0;j<3;j++){
                cin >> result[i][j];
            }
        }
        cout << btk(0) << " ";
    }
}

/*
    4 cases,three options for each pair , 15 pairs
    O(4*3^15)
*/