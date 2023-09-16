#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int n,L,h,cnt;
vector<int>v;

int main(){
    cin >> n >> L;
    for(int i=0;i<n;i++){
        cin >> h;
        v.push_back(h);
    }
    sort(v.begin(),v.end());
    int start = v[0];
    int cnt = 1;
    for(int i=1;i<v.size();i++){
        if(v[i]<start+L) continue;
        start=v[i];
        cnt++;
    }
    cout << cnt<< '\n';
}

/*
    Approach:
        Sort the vector in ascending order and check how many holes one tape can cover at a time.
        The tape must cover [h-0.5,h+0.5] for each hole.
        This means if the first hole to cover is placed at S, the tape can cover holes placed up to S+L exclusive.

    Time Complexity:
        O(nlogn)
    
*/