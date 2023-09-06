#include<iostream>
#include<cmath>
using namespace std;
int n,r,c;
//int record[33000][33000] too big
int cnt=0;

void dq(int x, int y, int size){
    if (x==c && y==r){
        cout << cnt << endl;
        return;
    } else if (c>=x && c<x+size && r>=y && r<y+size){ // divide only when the target point is in the range
        dq(x,y,size/2);
        dq(x+size/2,y,size/2);
        dq(x,y+size/2,size/2);
        dq(x+size/2,y+size/2,size/2);
    } else{ // only calculate if the target point is not in the current quadrant
        cnt+=size*size;
    }

}
int main(){
    cin >> n;
    cin >> r >> c;
    dq(0,0,pow(2,n));
}

/*
    (1) ON^2
    (2) 4*(N/4)^2
    O(N^2)
*/