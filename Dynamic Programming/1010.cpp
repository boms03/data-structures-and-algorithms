#include<iostream>
using namespace std;

int dp[31][31];
int t,n,m;
int main(){
    cin>>t;
    while(t--){
        cin>>n>>m;
        dp[1][0]=1;
        dp[1][1]=1;
        for(int i=2;i<=m;i++){
            dp[i][0]=1;
            for(int j=1;j<=i;j++){
                dp[i][j]=dp[i-1][j-1]+dp[i-1][j];
            }
        }
        cout << dp[m][n]<< endl;
    }
}

/*
    nCr =n-1Cr-1 +n-1Cr
    pick particular one + dont pick particular one
    O(M)
*/