#include<iostream>
using namespace std;

int map[6][6];
int cnt=0;
pair<int,int>p[26];

bool checkBingo(){
    int bingo = 0; 
    int rDig = 0;
    int lDig = 0;
    for(int i=0;i<5;i++){
        int row = 0;
        int col = 0;
        for(int j=0;j<5;j++){ 
            if(map[i][j]==-1) row++;
            if(map[j][i]==-1) col++;
        }
        if(row==5) bingo++;
        if(col==5) bingo++;
        if(map[i][i]==-1) lDig++;
        if(map[i][4-i]==-1) rDig++;
    }
    if(lDig==5) bingo++;
    if(rDig==5) bingo++;

    if(bingo>=3) return true;
    return false;
}
int main(){
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            cin >> map[i][j];
            p[map[i][j]]={i,j};
        }
    }
    int t;
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            cnt++;
            cin >> t;
            map[p[t].first][p[t].second]=-1;
            if(i>1){
                if(checkBingo()){
                    cout << cnt << '\n';
                    return 0;
                }
            }
        }
    }
    return 0;
}

/*
    Approach:
        Check every vertical and horizontal lines of 5x5 map.
        The number of inputs must be more than 11 to create first bingo.
        Use a pair array to record the index of number. This helps to mark every called number.
    Time Complexity:
        Approximately 3*5*5*5 calculations
        O(1)
*/