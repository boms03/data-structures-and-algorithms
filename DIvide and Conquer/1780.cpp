#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
int n;
int map[2200][2200];
int mone, zero, one;

void dq(int x, int y, int size){ // x,y is the starting point of each pieces
    int color = map[y][x];
    for(int i=y;i<y+size;i++){ // (1)
        for(int j=x; j<x+size; j++){
            if (map[i][j]!=color){ 
                // (2)
                dq(x,y,size/3);
                dq(x+size/3,y,size/3);
                dq(x+size/3+size/3,y,size/3);
                dq(x,y+size/3,size/3);
                dq(x+size/3,y+size/3,size/3);
                dq(x+size/3+size/3,y+size/3,size/3);
                dq(x,y+size/3+size/3,size/3);
                dq(x+size/3,y+size/3+size/3,size/3);
                dq(x+size/3+size/3,y+size/3+size/3,size/3);
                return;
            }
        }
    }
    if(color==-1) mone++;
    else if (color==0) zero++;
    else one++;
}
int main(){
    cin >> n;
    for (int i=0;i<n;i++){
        for(int j=0; j<n;j++){
            cin >> map[i][j];
        }
    }
    dq(0,0,n);
    cout << mone << '\n' << zero << '\n' << one << '\n';
}

/*
    (1) N^2
    (2) 9*(N/3)^2 
    O(N^2)
*/
