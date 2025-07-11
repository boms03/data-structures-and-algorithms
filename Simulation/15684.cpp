#include <iostream>
#include <vector>
using namespace std;

int n,m,h;
int line=1;
vector<vector<int>>grid;

void add_line(int i,int j){
    grid[i][j]=line;
    grid[i][j+1]=line++;
}

void delete_line(int i,int j){
    grid[i][j]=0;
    grid[i][j+1]=0;
    line--;
}

bool try_game(){
    bool correct=true;
    
    for(int i=0;i<n && correct ;i++){
        int cur_y = 0;
        int cur_x = i;
        while(cur_y<h){
            //cout << "before " << i << " " << cur_x << " " << cur_y << endl;
            if(grid[cur_y][cur_x]==0){
                cur_y++;
            }
            else{
                if(cur_x-1 >= 0 && grid[cur_y][cur_x]==grid[cur_y][cur_x-1]){
                    cur_x--;
                } else if(cur_x+1 < n && grid[cur_y][cur_x]==grid[cur_y][cur_x+1]) {
                    cur_x++;
                }
                cur_y++;
            }
            //cout << "after " << i << " " << cur_x << " " << cur_y << endl;
            
        }
        if(cur_x!=i){
            correct=false;
            break;
        }
    }
    return correct;
}

bool backtrack(int cnt, int target_depth){
    if(cnt==target_depth){
        // for(int i=0;i<n;i++){
        //     for(int j=0;j<h;j++){
        //         cout << grid[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
        return try_game();
    }
    
    for(int i=0;i<h;i++){
        for(int j=0;j<n-1;j++){
            if(grid[i][j]==0 && grid[i][j+1]==0){
                add_line(i,j);
                if(backtrack(cnt+1,target_depth)) return true;
                delete_line(i,j);
            }
        }
    }
    return false;
}

int main() {
    cin >> n >> m >> h;
    
    grid.resize(h);
    for(int i=0;i<h;i++){
        grid[i].resize(n);
    }
    
    if(m==0){
        cout << 0;
        return 0;
    }
    
    for(int i=0;i<m;i++){
        int a,b;
        cin >> a >> b;
        grid[a-1][b-1]=line;
        grid[a-1][b]=line++;
    }
    
    for(int i=0;i<=3;i++){
        if(backtrack(0,i)){
            cout << i;
            return 0;
        }
    }
    cout << -1;
}
