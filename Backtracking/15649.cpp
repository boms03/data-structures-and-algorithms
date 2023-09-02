#include<iostream>
#include<algorithm>
using namespace std;

int N,M;
int chk[9];
int ans[9];

void bt(int nx, int p){
    if(nx==M){ 
        for(int i=0; i<M;i++){
            cout << ans [i] << " ";
        }
        cout << '\n';
        return;
    }
    for (int i=1; i<=N;i++){
        if(chk[i])continue;
        chk[i]=1;
        ans[p]=i;
        bt(nx+1,p+1);
        chk[i]=0;
        ans[p]=0;
    }

}
int main(){
    cin >> N >> M;
    bt(0,0);
}
/*
    O(N!)
*/