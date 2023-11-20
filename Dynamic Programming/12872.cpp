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
    Approach:
        Lets say I picked i songs and there are j different songs. 
        When adding a song I have two options 
        1) add a song not in the playlist
        2) add an already existing song 

        For the case 1, dp[i][j]=dp[i-1][j-1]*(n-j+1)
        n-j+1 is the number of songs not in the playlist
        pick one song from n-j+1 and add = (n-j+1)C1

        For the case 2, dp[i][j]+=dp[i-1][j]*(j-m)
        But the condition is that there must be at least m+1 different songs in the playlist.
        This is because we need m different songs in between same songs. 

    Time Complexity:
        O(N) 1<=N<=100
*/
