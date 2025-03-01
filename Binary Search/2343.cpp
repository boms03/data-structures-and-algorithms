#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n,m;
vector<int>v;

int ps(int l,int r){ // [1]
    while(l<=r){
        int mid = (l+r)/2;
        int sum=0, cnt=1;
        
        for(int i=0;i<v.size();i++){ //[2]
            if(sum+v[i]>mid){
                sum=v[i];
                cnt++;
            } else {
                sum+=v[i];
            }
        }
        if(cnt<=m){ // [3]
            r = mid - 1;
        } else { // [4]
            l = mid + 1;
        }
    }
    cout << l << endl;
}
int main(){
    cin >> n >> m;
    int a,r,l;
    for(int i=0;i<n;i++){
        cin >> a;
        v.push_back(a);
        r+=a;
    }
    l = *max_element(v.begin(),v.end());
    ps(l,r);
}

/*
    Approach:
        Pick a blue ray size and count if it forms M number of blue rays
        [1]Use parametric search to choose the blue ray size
        [2]Sum the length of videos until it exceed mid and increment count by 1
        [3]Search for smaller size if there are more blue rays. Also, we are looking for the minimum size so it also applies to when count equals to M
        [4]Search for larger size if there are less blue rays.
    
    What to consider:
        I first used 0 as L and sum of all elements as R in the parametric search.
        But L should be the maximum of elements, because at least one video should be in a blue ray

    Time complexity:
        O(logn)
*/