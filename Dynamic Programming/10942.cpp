#include<iostream>
#include<algorithm>
using namespace std;

int n,m;
int arr[2001];
int dp[2001][2001];
int main(){
    ios_base::sync_with_stdio(0);
	cin.tie(0);

    cin >> n;
    for(int i=1; i<=n; i++){
        cin>> arr[i];
        dp[i][i]=1;
        if(i!=1 && arr[i-1] == arr[i]) dp[i-1][i]=1;
    }

    for(int i=2;i<=n-1;i++){
        for(int j=1;j+i<=n;j++){
            if(arr[j]==arr[j+i] && dp[j+1][i+j-1]==1) dp[j][i+j]=1;
        }
    }
    cin >> m;
    for(int i=0;i<m;i++){
        int s, e;
        cin >> s >> e;
        cout << dp[s][e]<< '\n';
    }
}

/*
    approach: the property of palindrom is that d[i-1]==d[i+1] when i is the center.
    it means that to know if 2~6 is palindrom, we have to know if 3~5 is palindrom and 2==6
    (!) update by length! not the begining index!
    first update length 3 using length 1
    then update length 4 using length 2
    then update length 5 using length 4
    ...
    O(N^2)
*/