#include<iostream>
#include<algorithm>
using namespace std;

int n;
long long dp[101];

int main(){
    cin >> n;
    dp[1]=1;
    dp[2]=2;
    dp[3]=3;
    dp[4]=4;
    dp[5]=5;
    dp[6]=6;
    for (int i=7;i<=n;i++){
        for(int j=3;j<i;j++){
            dp[i]=max(dp[i],dp[i-j]*(j-1));
        }
    }
    cout << dp[n] << endl;
}

/*
    approach: 
        dp[i] = max number of As when i times clicked
        1<=i<=6 just add A
        i>=7 max of dp[i-3]*2, d[i-4]*3 ... dp[1]*(j-1)
        ex. at i=8, dp[i-4]*3 means at 1)select i-4 at i-3 2)copy at i-2 3) do anything at i-1 4)paste i
        
        reduced time complexity from 4^100 (4 choices at 100 trials)
*/
