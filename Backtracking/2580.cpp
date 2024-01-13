#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int map[10][10];
int row[10][10];
int col[10][10];
int sqr[10][10];
vector<pair<int,int> >zeros;

void btk(int z){
    if(z==zeros.size()){
        for (int i=0;i<9;i++){
            for (int j=0;j<9;j++){
                cout << map[i][j] << " ";
            }
            cout << '\n';
        }
        exit(0);
    }

    int x = zeros[z].first;
    int y = zeros[z].second;
    for (int i=1;i<10;i++){
        if (col[x][i]==0 && row[y][i]==0 && sqr[(x/3)*3+(y/3)][i]==0){ // pruning
            map[y][x]=i;
            row[y][i]=1;
            col[x][i]=1;
            sqr[(x/3)*3+(y/3)][i]=1;
            btk(z+1);
            map[y][x]=0;
            row[y][i]=0;
            col[x][i]=0;
            sqr[(x/3)*3+(y/3)][i]=0;
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    for (int i=0;i<9;i++){
        for (int j=0;j<9;j++){
            cin >> map[i][j];
            if (map[i][j]!=0){
                row[i][map[i][j]]=1; // record numbers in each row
                col[j][map[i][j]]=1; // record numbers in each coloum
                sqr[(j/3)*3+(i/3)][map[i][j]]=1; // record numbers in each quadrant(0~8)
            } else {
                zeros.push_back({j,i});
            }
        }
    }
    btk(0);
}

/* 
    N = |zeros|
    O(2^N)
*/