#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int m,n;
int ans = 0;
int mn=1000000;
int mx=0;
vector<int>eats;
int main(){
    cin >> m >> n;
    int sum=0;
    for(int i=0;i<n;i++){
        int eat;
        sum+=eat;
        cin >> eat;
        eats.push_back(eat);
        mn=min(mn,eat);
        mx=max(mx,eat);
    }
    int l = 1;
    int r = mx;

    bool possible;
    while(l<=r){
        int mid = (l+r)/2;
        int total = 0;
        for(int i=0;i<eats.size();i++){
            total+=eats[i]/mid;
        }
        if (total>=m){
            l = mid + 1;
            ans = mid;
        } else {
            r = mid - 1;
        }
    }
    cout << ans;
    
}

/*
    Approach:
        Find the largest possible length to distribute to m people.
        Parametric search the length and check if it can produce enough for m people.
        Too many -> try larger by making left = mid + 1
        Enough for m -> also try larger by making left = mid + 1
        Not enough for m -> try smaller length by making right = mid - 1

    Time Complexity:
        O(logn)
*/