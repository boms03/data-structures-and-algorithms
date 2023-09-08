#include<iostream>
#include<algorithm>
using namespace std;
int n,k;
int icr[9];
int chk[9];
int ans =0;

void btk(int sum, int idx){
    if(idx==n) ans++;
    for (int i=0;i<n;i++){
        if(chk[i]==1) continue;
        if(sum+icr[i]<500) continue;
        chk[i]=1;
        btk(sum+icr[i],idx+1);
        chk[i]=0;
    }
}
int main(){
    cin>> n >> k;
    for (int i=0;i<n;i++){
        cin >> icr[i];
        icr[i]-=k;
    }
    btk(500,0);
    cout<< ans << endl;
}

// O(N!)