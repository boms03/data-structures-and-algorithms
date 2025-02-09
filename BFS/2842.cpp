#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<climits>
using namespace std;
typedef pair<int,int> pii;

int n;
char map[51][51];
int height[51][51];
bool visited[51][51];
int post_x,post_y;
vector<int>heights;
int total_houses;

int dx[]={0,0,-1,1,1,1,-1,-1};
int dy[]={1,-1,0,0,1,-1,1,-1};

int bfs(int l, int h){
    queue<pii>q;
    if(heights[l] <= height[post_y][post_x] && height[post_y][post_x] <= heights[h]){
        q.push({post_x,post_y});
        visited[post_y][post_x] = true;
    }
    int cnt_house = 0;
    while(!q.empty()){
        pii cur = q.front();
        q.pop();

        int cur_x = cur.first;
        int cur_y = cur.second;

        for(int i=0;i<8;i++){
            int next_x = cur_x + dx[i];
            int next_y = cur_y + dy[i];

            if(next_x < 0 || next_x >= n || next_y <0 || next_y >=n || visited[next_y][next_x]) continue;
            if(height[next_y][next_x] < heights[l] || height[next_y][next_x] > heights[h]) continue;
            q.push({next_x,next_y});
            visited[next_y][next_x] = true;
            if(map[next_y][next_x] == 'K') cnt_house++;
        }
    }
    if(cnt_house == total_houses) return 1;
    else return -1;
}

int solve(){
    sort(heights.begin(), heights.end());
    heights.erase(unique(heights.begin(),heights.end()), heights.end());
    int l = 0;
    int h = 0;
    int ans = INT_MAX;
    while(l < heights.size() && h < heights.size()){
        int result = bfs(l,h);
        fill(&visited[0][0],&visited[0][0]+51*51,false);
        if(result == 1){
            ans = min(ans,heights[h]-heights[l]);
            l++;
        } else if (result == -1){
            h++;
        }
    }
    return ans;
}

int main(){
    cin >> n;
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        for(int j=0;j<n;j++){

            map[i][j] = s[j];

            if(s[j]=='P'){
                post_x = j;
                post_y = i;
            } else if (s[j]=='K'){
                total_houses++;
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> height[i][j];
            heights.push_back(height[i][j]);
        }
    }
    cout << solve();

}