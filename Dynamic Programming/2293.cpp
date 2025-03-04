#include<iostream>
#include<algorithm>
using namespace std;

int n,k;
int arr[101];
int dp[10001];

int main(){
    cin >> n >> k;
    for(int i=0;i<n;i++) cin >> arr[i];
    dp[0]=1;
    for(int i=0;i<n;i++){
        for(int j=arr[i];j<=k;j++){
            dp[j]+=dp[j-arr[i]];
        }
    }
    cout << dp[k] << endl;
}

/*
    first approach: for loop by deleting the current value by currency inputs like dp[5]=dp[5-1]+dp[5-2]+dp[5-3]
    problem: it creates duplicates
    second approach: assume putting each currency input at the end
    ex: currency 1,2,5: for 5 assume putting 1 at the end so dp[5]+=dp[5-1]
    go dp[5]+=dp[5-1] dp[6]+=dp[6-1] dp[7]+=dp[7-1]... meaning i am putting 1 at the end -> 1,11,111,1111,1111
    next dp[5]+=dp[5-2] dp[6]+=dp[6-2] ..... 1112/122, 11112/1122 ... 1212 (duplicates of 1122) does not happen because 1 must precede 2 everytime

    O(N*K)
*/