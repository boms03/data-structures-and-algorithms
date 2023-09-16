#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
int n;
vector<ll>v;
vector<ll>sorted;
int main(){
    cin >> n;
    for(int i=0;i<n;i++){
        ll a;
        cin >> a;
        v.push_back(a);
        sorted.push_back(a);
    }
    sort(sorted.begin(),sorted.end());
    sorted.erase(unique(sorted.begin(),sorted.end()),sorted.end());

    for(int i=0;i<n;i++){
        int cnt = lower_bound(sorted.begin(),sorted.end(),v[i])-sorted.begin();
        cout << cnt << " ";
    }
}

/*
    Approch:
        how to erase duplicates in vector
        1) sort vector
        2) unique(v.begin(),v.end()) puts all duplicates at the end of vector and returns the address of the beginning of duplicates
        3) since we know the beginning address of duplicates, we can erase until the end using erase()
    Time Complexity:
        1<=n<=1,000,000 so use n times of binary search (logn) to reduce from sequencial search (n^2)
        O(nlogn)
*/