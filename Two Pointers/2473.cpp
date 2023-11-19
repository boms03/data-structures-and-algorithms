#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;

int N;
vector<ll>v;

int main(){
    cin >> N;
    while(N--){
        int a;
        cin >> a;
        v.push_back(a);
    }
    sort(v.begin(),v.end());

    ll min=1e18;
    ll minl,minr,minm,sum;

    for (int l=0;l<v.size()-2;l++){ // fix l and use m and r as two pointers
        int m=l+1;
        int r=v.size()-1;
        while(m<r){
            ll sum = v[l]+v[m]+v[r];
            if(abs(sum)<min){
                min=abs(sum);
                minl=l;
                minm=m;
                minr=r;
            }
            if (sum==0) break;
            if (sum<0){
                m++;
            } else {
                r--;
            }
        }
    }
    cout << v[minl] << " " << v[minm] << " " << v[minr] << endl;
}

/*
    O(N^2)
*/