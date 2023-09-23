#include<iostream>
#include<queue>
#include<cmath>
using namespace std;
string v[4];
string s;
int n,a,b;
int isRotate[4];

void rotate(int t, int d){
    if(d==1){
        v[t] = v[t].substr(7)+v[t].substr(0,7);
    } else {
        v[t] = v[t].substr(1,7)+v[t].substr(0,1);
    }
}

void left(int t, int d){
    if(t<=0)return;
    if(v[t][6] != v[t-1][2]){
        isRotate[t-1]=d*-1;
        left(t-1,d*-1);
    }
}

void right(int t, int d){
    if(t>=3)return;
    if(v[t][2] != v[t+1][6]){
        isRotate[t+1]=d*-1;
        right(t+1,d*-1);
    }
}

void turn(int t, int d){
    isRotate[t]=d;
    left(t,d);
    right(t,d);
    for(int i=0;i<4;i++){
        rotate(i,isRotate[i]);
    }

}

int main(){
    for(int i=0;i<4;i++){
        cin >> v[i];
    }

    cin >> n;

    for(int i=0; i<n;i++){
        cin >> a >> b;
        turn(a-1,b);
        memset(isRotate,0,sizeof(isRotate));
    }

    int cnt = 0;
    int mul = 1;
    for(int i=0;i<4;i++){
        cnt+= (v[i][0]-'0') *mul;
        mul *=2;
    }
    cout << cnt << '\n';
}