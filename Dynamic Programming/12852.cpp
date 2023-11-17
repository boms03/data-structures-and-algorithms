#include<iostream>
#include<algorithm>
using namespace std;

int n;
int dp[1000001];
int main(){
    cin >> n;
    dp[1]=0;
    for(int i=2;i<=n;i++){
        dp[i]=i;
        if(i%2==0)dp[i]=min(dp[i],dp[i/2]);
        if(i%3==0) dp[i]=min(dp[i],dp[i/3]);
        dp[i]=min(dp[i],dp[i-1])+1;
    }
    cout << dp[n] << '\n';

    while(true){ //track back
        cout << n << " ";
        if(n==1) break;
        if(dp[n]==dp[n-1]+1){
            n=n-1;
        } else if (n%2==0 && dp[n]==dp[n/2]+1){
            n=n/2;
        } else if (n%3==0 && dp[n]==dp[n/3]+1){
            n=n/3;
        }
    }
}
//O(N)