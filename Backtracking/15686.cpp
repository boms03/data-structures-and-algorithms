#include<iostream>
#include<vector>
#include<climits>
using namespace std;

int n,m;
int ans=1e9;
vector<pair<int,int>>house;
vector<pair<int,int>>chicken;
vector<pair<int,int>>pickChicken;
int map[51][51];

void distance(){
    int sum = 0;
    for(int i=0;i<house.size();i++){
        int mn = 1e9;
        for(int j=0; j<pickChicken.size();j++){
            mn = min(mn,abs(abs(house[i].first-pickChicken[j].first)+abs(house[i].second-pickChicken[j].second)));
        }
        sum+=mn;
    }
    ans = min(ans,sum);
    
}
void btk(int idx, int cnt){
    if(cnt==m){
        distance();
        return;
    }
    for(int i=idx; i<chicken.size();i++){
        pickChicken.push_back(chicken[i]);
        btk(i+1,cnt+1);
        pickChicken.pop_back();
    }
}
int main(){
    cin >> n >> m;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>> map[i][j];
            if(map[i][j]==1) house.push_back({i,j});
            else if(map[i][j]==2) chicken.push_back({i,j});
        }
    }
    btk(0,0);
    cout << ans << '\n';
}

/*
    Approach:   
        Use backtracking to create combination of chicken stores.
        No duplicates allowed and order does not matter.
        After picking stores in the pickChicken vector, iterate houses and pickChicken stores to calculate minimum distances.
        Then decide whether to update the previously updated minimum distance or not.
    Time Complexiy:
        O(13C6 * 50*13)
*/