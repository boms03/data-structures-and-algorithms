#include<iostream>
using namespace std;

int arr[1001];
int dp[1001];
int n,mx=0;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }
    for(int i=0;i<n;i++){
        dp[i]=1;
        for(int j=0;j<i;j++){
            if(arr[i]<arr[j]) dp[i]=max(dp[j]+1,dp[i]);
        }
        mx=max(mx,dp[i]);
    }
    cout << mx << '\n';
}

// dp O(N^2)