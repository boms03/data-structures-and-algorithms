#include<iostream>
using namespace std;
int map[100001][3];
int dp[100001][3][2];
int main(){
    int n;
    cin >> n;
    for (int i=0;i<n;i++){
        cin >> map[i][0] >> map[i][1] >> map[i][2];
    }
    
    dp[0][0][0]=map[0][0];
    dp[0][1][0]=map[0][1];
    dp[0][2][0]=map[0][2];
    dp[0][0][1]=map[0][0];
    dp[0][1][1]=map[0][1];
    dp[0][2][1]=map[0][2];
        
    for (int i=1;i<n;i++){
        dp[i][0][0] = max(dp[i-1][0][0],dp[i-1][1][0]) + map[i][0];
        dp[i][1][0] = max(dp[i-1][0][0],max(dp[i-1][1][0],dp[i-1][2][0])) + map[i][1];
        dp[i][2][0] = max(dp[i-1][1][0],dp[i-1][2][0]) + map[i][2];
        
        dp[i][0][1] = min(dp[i-1][0][1],dp[i-1][1][1]) + map[i][0];
        dp[i][1][1] = min(dp[i-1][0][1],min(dp[i-1][1][1],dp[i-1][2][1])) + map[i][1];
        dp[i][2][1] = min(dp[i-1][1][1],dp[i-1][2][1]) + map[i][2];
    }
    
    cout << max(dp[n-1][0][0],max(dp[n-1][1][0],dp[n-1][2][0])) << " " << min(dp[n-1][0][1],min(dp[n-1][1][1],dp[n-1][2][1])) << '\n';
}