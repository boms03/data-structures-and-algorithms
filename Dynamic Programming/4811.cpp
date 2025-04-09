#include<iostream>
using namespace std;
int n,t;
long long dp[31][31];

int main(){
    for(int h=0;h<=30;h++){
        for(int w=0;w<=30;w++){
            if(h>w) continue;
            if(h==0) dp[w][h] =1;
            else dp[w][h]=dp[w-1][h]+dp[w][h-1];
        }
    }
    
    while(true){
        cin >> n;
        if(n==0) break;
        cout << dp[n][n] << endl;
    }
}

/*
    w: big h: small
    approach: the number of big and small that can be eaten is w>=h
    w=1 h=1, w=2 h=1,2, w=3 h=1,2,3 ... 
    assume putting w or h at the end whwh(w) wwwhw(h)
    (1) continue if h>w
    (2) when h==0 w ww www wwww .. -> d[w][h] = 1
    (3) ex. 3w 2h = 2w 2h + w or 3w 1h + h. 
        ex. 2w 2h = (1) 1w 2h + w or (2) 2w h +h 
        (1) cannot happen so 0
    O(30^2)
*/