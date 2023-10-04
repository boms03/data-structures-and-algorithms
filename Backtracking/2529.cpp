#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n;
int operators[10];
int chk[10];
int ans[10];
string mx = "0";
string mn = "999999999";

void btk(int prv, int opr, int idx){
    if(idx==n+1){
        string a= "";
        for(int i=0;i<n+1;i++){
            a += to_string(ans[i]);
        }
        mx = max(mx,a);
        mn = min(mn,a);
        return;
    }
    for (int i=0; i<=9; i++){
        if (chk[i]==1) continue;
        if(opr && i<prv) continue;
        else if(!opr && i>prv) continue; 
        chk[i]=1;
        ans[idx]=i;
        btk(i,operators[idx], idx+1);
        chk[i]=0;
    }
}
int main(){
    cin >> n;
    for (int i=0; i<n;i++){
        char a;
        cin >> a;
        if (a=='<') operators[i] = 1;
        else operators[i] = 0;
    }
    btk(-1,-1,0);
    cout << mx << '\n' << mn << '\n';
}

// O(N!)