#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
using ll = long long;
ll n,R,G,B,dp[12][111][111][111],fac[12];

void table(){
    fac[0]=1;
    for(ll i=1;i<=11;i++){
        fac[i]=i*fac[i-1];
    }
}

ll mul(ll n,ll r){
    if(r==2) return fac[n]/fac[n/2]/fac[n/2];
    if(r==3) return fac[n]/fac[n/3]/fac[n/3]/fac[n/3];
}

ll dfs(int h,int r,int g, int b){
    //base case
    if(h==n+1) return (r<=R && g<=G && b<=B);
    
    ll& ret = dp[h][r][g][b];

    //use memoization
    if(ret!=-1) return ret;
    ret = 0;
    // color 1
    ret+=dfs(h+1,r+h,g,b);
    ret+=dfs(h+1,r,g+h,b);
    ret+=dfs(h+1,r,g,b+h);

    //color 2
    if(h%2==0){
        ret+=dfs(h+1,r+h/2,g+h/2,b)*mul(h,2);
        ret+=dfs(h+1,r+h/2,g,b+h/2)*mul(h,2);
        ret+=dfs(h+1,r,g+h/2,b+h/2)*mul(h,2);
    }
    //color 3
    if(h%3==0){
        ret+=dfs(h+1,r+h/3,g+h/3,b+h/3)*mul(h,3);
    }
    return ret;

}
int main(){
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> R >> G >> B;
    memset(dp,-1,sizeof(dp));
    table();
    cout << dfs(1,0,0,0) << '\n';
}

/*
    approach:
        3 cases for choosing 1 color -> for all level
        3 case for choosing 2 color -> for even level
        1 case for choosing 3 color -> for multiple of 3 level

        base case: return 1 if remainig condition met
        multiple of 2 case: nCn/2 * n/2Cn/2 = n!/(n/2)!/(n/2)!
        multiple of 3 case: nCn/3 * 2n/3Cn/3 = n!/(n/3)!/(n/3)!/(n/3)!
*/