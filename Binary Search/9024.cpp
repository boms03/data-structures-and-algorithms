#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int n,k,t,e,cnt,mini;
vector<int>v;

int main(){
    cin >> t;
    while(t--){
        ios::sync_with_stdio(false);
        cin.tie(NULL);

        cin >> n >> k;
        for (int i=0;i<n;i++){
            cin >> e;
            v.push_back(e);
        }
        sort(v.begin(),v.end());
        mini = 1e9;
        cnt = 0;
        for (int i=0;i<n;i++){ // [1]
            int l = i + 1;
            int r = n - 1;
            while(l<=r){
                int mid = (l+r)/2;
                int sum = v[i]+v[mid];
                if(sum>k){
                    r = mid - 1;
                } else {
                    l = mid + 1;
                } 
                if(abs(k-sum)<mini){ // [3]
                    cnt=1;
                    mini = abs(k-sum);
                } else if (abs(k-sum)==mini){ // [2]
                    cnt++;
                }
            }
        }
        cout << cnt << endl;
        v.clear();
    }
    
}

/*
    Approach:
        [1]For every element in an array, find a pair that sums closest to K.
        Absolute value of k-sum indicates the proximity of sum to K.
        [2]There can be many pairs with the same proximity, so increment count by 1 if another pair with the same proximity is found.
        [3]Keep recording the smallest abs(k-sum) and update count to 1 if smaller abs(k-sum) is found.

        (!) use two pointers if duplicates are allowed!
        
        O(NlogN) 

*/