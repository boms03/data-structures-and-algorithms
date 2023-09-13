#include<iostream>
#include<algorithm>
using namespace std;

int n,m;
int chk[9];
int ans[9];

void btk(int num, int idx){ // i bigger than i at idx-1 
    if(idx==m){ // [1]
        for (int i=0; i<idx; i++) cout << ans[i] << " ";
        cout << '\n';
    }
    for(int i=num;i<=n;i++){
        if(chk[i]==1) continue;
        chk[i]=1;
        ans[idx]=i;
        btk(i+1,idx+1); // [2]
        chk[i]=0;
    }
}
int main(){
    cin >> n >> m;
    btk(1,0);
}

/*
    [1] N [2] N!
    O(N*N!)
*/