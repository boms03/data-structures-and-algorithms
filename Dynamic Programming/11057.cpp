#include<iostream>
#include<algorithm>
using namespace std;

int n;
int dp[1001][10];
int main(){
    cin >> n;
    for (int i=0;i<10;i++) dp[1][i]=1;
    for(int i=2;i<=n;i++){
        for(int j=0;j<10;j++){
            for(int k=j;k>=0;k--){
                dp[i][j]=(dp[i][j]+dp[i-1][k])%10007;
            }
        }
    }
    int ans=0;
    for(int i=0;i<10;i++){
        ans=(ans+dp[n][i])%10007;
    }
    cout << ans << endl;
}

/*
    Approach:
        dp[i][j]+=dp[i-1][0~(j-1)]
    Time Complexity:
        O(N)
*/

dp O(N)