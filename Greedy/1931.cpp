#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int n, s, e, cnt=1;
vector<pair<int,int>>v;

int main(){
    cin >> n;
    for (int i=0;i<n;i++){
        cin >> s >> e;
        v.push_back({e,s});
    }
    sort(v.begin(),v.end());
    int temp=v[0].first;
    for (int i=1;i<n;i++){
        if(v[i].second>=temp){
            temp=v[i].first;
            cnt++;
        }
    }
    cout << cnt << '\n';

}

/*
    Approach:
        Brute force 100,000^2 is over time limit. So O(N) or O(NlogN)
        Priority is to pick more meetings as much as possible.
        Sort by starting vs sort by ending time?
        Even if a meeting starts early, we cant pick more meetings if it ends too late!

        Sort by starting time
        1)- - - - - - - -
        2) - - - 
        3)       - -
        4)           - -

        I can only pick 1)

        Sort by ending time  
        1) - - - 
        2)       - -
        3)           - -
        4) - - - - - - - -

        I can pick 1,2,3 in this case -> so sort by ending time!

        Time complexity:
            O(N)
*/