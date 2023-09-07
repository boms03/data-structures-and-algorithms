#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n;
int map[11][11];
int chk[30];
int mx=0;
vector<pair<int,int> >v[30];

void btk(int rn, int cnt){
    if(rn>=2*n-1){
        mx=max(mx,cnt);
        return;
    }
    for(int j=0; j<v[rn].size();j++){ // pick one from v[rn] and check if its downward diagnal is already visited
        if(chk[v[rn][j].first-v[rn][j].second+n-1]==1) continue; // i-j+n-1 represents idex of downward diagnal 
        chk[v[rn][j].first-v[rn][j].second+n-1]=1;
        btk(rn+2, cnt+1);
        chk[v[rn][j].first-v[rn][j].second+n-1]=0;
    }
    btk(rn+2,cnt); // does not select

}
int main(){
    cin >> n;
    for (int i=0;i<n;i++){
        for(int j=0; j<n;j++){
            cin >> map[i][j];
        }
    }
     for (int i=0;i<n;i++){ // i+j is row number representing upper diagnal
        for(int j=0; j<n;j++){
            if(map[i][j]==1){
                v[i+j].push_back({i,j});
            }
        }
    }
    btk(0,0); // divide into two cases as bishop cannot attack adjacent rows
    int t = mx;
    mx=0;
    btk(1,0);
    cout << t+mx << endl; // add two max results from the two cases.
}

/*
    O(2^(n/2+1))
*/