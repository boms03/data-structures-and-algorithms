#include<iostream>
#include<cstring>
#include<vector>
using namespace std;

int n;
int map[21][21];
int ans = 0;

int find_max(){
    int max_n = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            max_n = max(max_n,map[i][j]);
        }
    }
    return max_n;
}

void move(int dir){
    int new_map[21][21];
    if (dir==0){
        //상

        for(int col=0;col<n;col++){
            vector<int>col_v;
            //옮기기
            for(int row=0;row<n;row++){
                if(map[row][col]!=0) col_v.push_back(map[row][col]);
            }
            //합치기
            // for(int i=0;i<n;i++){
            //     for(int j=0;j<n;j++){
            //         cout << map[i][j];
            //     }
            //     cout << endl;
            // }
            for(int i=0;i<int(col_v.size())-1;i++){
                if(col_v[i]==col_v[i+1]){
                    col_v[i]*=2;
                    col_v[i+1]=0;
                }
            }
            //옮기기
            vector<int> new_col;
            for (int num : col_v) {
                if (num != 0) new_col.push_back(num);
            }
            while (new_col.size() < n) new_col.push_back(0);
            // for(int i=0;i<new_col.size();i++) cout << new_col[i] << " ";
            // cout << endl;

            for (int row = 0; row < n; row++) {
                map[row][col] = new_col[row];
            }
            // for(int i=0;i<n;i++){
            //     for(int j=0;j<n;j++){
            //         cout << map[i][j];
            //     }
            //     cout << endl;
            // }
        }


    } else if(dir==1) {
        //하
    
        for(int col=0;col<n;col++){
            vector<int>col_v;
            //옮기기
            for(int row=n-1;row>=0;row--){
                if(map[row][col]!=0) col_v.push_back(map[row][col]);
            }

            // for(int i=0;i<col_v.size();i++) cout << col_v[i] << " ";
            // cout << endl;

            //합치기
            for(int i=0;i<int(col_v.size())-1;i++){
                if(col_v[i]==col_v[i+1]){
                    col_v[i]*=2;
                    col_v[i+1]=0;
                }
            }
            //옮기기
            vector<int> new_col;
            for (int num : col_v) {
                if (num != 0) new_col.push_back(num);
            }
            while (new_col.size() < n) new_col.push_back(0);

            // for(int i=0;i<new_col.size();i++) cout << new_col[i] << " ";
            // cout << endl;

            for (int row = 0; row < n; row++) {
                map[n-1-row][col] = new_col[row];
            }
        }


    } else if(dir==2) {
        //좌

        for(int row=0;row<n;row++){
            vector<int>row_v;
            //옮기기
            for(int col=0;col<n;col++){
                if(map[row][col]!=0) row_v.push_back(map[row][col]);
            }

            // for(int i=0;i<row_v.size();i++) cout << row_v[i] << " ";
            // cout << endl;

            //합치기
            for(int i=0;i<int(row_v.size())-1;i++){
                if(row_v[i]==row_v[i+1]){
                    row_v[i]*=2;
                    row_v[i+1]=0;
                }
            }
            //옮기기
            vector<int> new_row;
            for (int num : row_v) {
                if (num != 0) new_row.push_back(num);
            }
            while (new_row.size() < n) new_row.push_back(0);

            // for(int i=0;i<new_row.size();i++) cout << new_row[i] << " ";
            // cout << endl;

            for (int col = 0; col < n; col++) {
                map[row][col] = new_row[col];
            }
        }
        
    } else {
        //우

        for(int row=0;row<n;row++){
            vector<int>row_v;
            //옮기기
            for(int col=n-1;col>=0;col--){
                if(map[row][col]!=0) row_v.push_back(map[row][col]);
            }

            // for(int i=0;i<row_v.size();i++) cout << row_v[i] << " ";
            // cout << endl;

            //합치기
            for(int i=0;i<int(row_v.size())-1;i++){
                if(row_v[i]==row_v[i+1]){
                    row_v[i]*=2;
                    row_v[i+1]=0;
                }
            }
            //옮기기
            vector<int> new_row;
            for (int num : row_v) {
                if (num != 0) new_row.push_back(num);
            }
            while (new_row.size() < n) new_row.push_back(0);

            // for(int i=0;i<new_row.size();i++) cout << new_row[i] << " ";
            // cout << endl;

            for (int col = 0; col < n; col++) {
                map[row][n-1-col] = new_row[col];
            }
        }
    }
}

void solve(int cnt){
    if(cnt==5){
        ans = max(ans,find_max());
        return;
    }
    int backup[21][21];
    for(int dir=0;dir<4;dir++){
        memcpy(backup,map, sizeof(backup));
        move(dir);
        // cout << cnt << endl;
        // for(int i=0;i<n;i++){
        //     for(int j=0;j<n;j++){
        //             cout << map[i][j];
        //     }
        //     cout << endl;
        // }
        // cout << endl;
        solve(cnt+1);
        memcpy(map,backup, sizeof(map));
    }
}
int main(){
    // freopen("output.txt", "w", stdout);
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> map[i][j];
        }
    }
    solve(0);
    cout << ans;
}

/*
    O(4^5 * N^2)
*/