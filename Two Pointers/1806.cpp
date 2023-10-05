#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>
using namespace std;

int N,S;
vector<int>v;

int main(){
    cin >> N >> S;
    for (int i=0; i<N;i++){
        int a;
        cin >> a;
        v.push_back(a);
    }
    //two pointers
    int l = 0;
    int r = 0;

    int mn = INT_MAX;
    int sum = 0;

    while(l<=r){
        if(sum>=S){ // record min length and reduce sum when reaching the answer 
            mn=min(mn,r-l);
            sum-=v[l++];
        }
        else if (r==N) break; // out of range
        else sum+=v[r++]; // add more when sum smaller than the condition
    }
    if(mn==INT_MAX) cout << 0 << endl; // 0 if sum didn't reach S 
    else cout << mn << endl;

}
/*
    two pointers O(N)
*/