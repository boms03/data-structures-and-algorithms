#include<iostream>
#include<algorithm>
using namespace std;


int n,m,p;
long long dp[101][101];

int main(){
    cin >> n >> m >> p;

    dp[0][0]=1;
    for(int i=1;i<=p;i++){
        for(int j=1;j<=i;j++){
            (dp[i][j]+=dp[i-1][j-1]*(n-j+1))%=1000000007; // (1)
            if(j>m) (dp[i][j]+=dp[i-1][j]*(j-m))%=1000000007; // (2)
        }
    }
    cout << dp[p][n] << endl;
}

/*
    approach: 
    1) put different song 2) put already put song
*/