#include<iostream>
#include<algorithm>
using namespace std;
int n;
int map[65][65];
string s="";

void dq(int x, int y, int size){
    int cpr = map[y][x];
    for(int i=y;i<y+size;i++){ // (1)
        for(int j=x;j<x+size;j++){
            if (map[i][j]!=cpr){
                // (2) divide into 4 pieces 
                s+="("; // open whenever division is needed
                dq(x,y,size/2);
                dq(x+size/2,y,size/2);
                dq(x,y+size/2,size/2);
                dq(x+size/2,y+size/2,size/2);
                s+=")"; // close when all areas are compressed
                return;
            }
        }
    }
    // reach here when the selected range has same colors
    if (cpr==0) s+="0";
    else s+="1";

}
int main(){
    cin >> n;
    for (int i=0; i<n;i++){
        for (int j=0; j<n; j++){
            scanf("%1d",&map[i][j]);
        }
    }
    dq(0,0,n);
    cout << s << endl;
}

/*
    (1) ON^2
    (2) 4*(N/4)^2
    O(N^2)
*/