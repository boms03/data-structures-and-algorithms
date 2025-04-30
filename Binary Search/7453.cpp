#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
ll n,result;
vector<ll>v[4];
vector<ll>sum;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    ll a;
    for(int i=0;i<n;i++){
        for(int j=0;j<4;j++){
            cin >> a;
            v[j].push_back(a);
        }
    }
    for(int i=0;i<n;i++){ // 1
        for(int j=0;j<n;j++){
            sum.push_back(v[2][i]+v[3][j]);
        }
    }
    sort(sum.begin(),sum.end()); // 2

    ll s;
    for(int i=0;i<n;i++){ // n^2
        for(int j=0;j<n;j++){
            //3
            s = v[0][i]+v[1][j];
            int low = lower_bound(sum.begin(),sum.end(),-s)-sum.begin(); //logn
            int upper = upper_bound(sum.begin(),sum.end(),-s)-sum.begin(); //logn
            //4
            if(-s==sum[low]){
                result+=upper-low;
            }
        }
    }
    cout << result << '\n';
    
}

/*
    Approach:   
        Iterating all 4 vectors at a time will take up to 4000^4 which is much greater than 1M
        Instead, split into pairs of 2 vectors and find matching pairs.
        (1)I picked 3rd and 4th vectors and save all possible sums into a sum vector
        (2)Sort this vector so that I can find the number of same sum values
        (3)Find the lower and upper bounds of -(sums of elements in 1st and 2cnd vector) to find the duplicates
        (4)Make sure that lower bound is equal to -(sums of elements in 1st and 2cnd vector). Pairs do not exist if not equal.

          Takes n^2 to find sum of 3,4 vectors
        + Takes n^2 to iterate 1,2 vectors
        + Takes logn to find the value in sum vector when iterating 1,2 vectors
        = n^2 + n^2logn

        O(N^2logn)
*/