#include<iostream>
#include<vector>
using namespace std;
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
int map[202][202];

int main(){
    int r,c,n;
    cin >> r >> c >> n;

    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            char a;
            cin >> a;
            if(a=='.') map[i][j]=9;
            else map[i][j]=2;
        }
    }

    if(n==1){
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                if(map[i][j]==9) cout << '.';
                else cout << 'O';
            }
            cout << '\n';
        }
        exit(0);
    }

    for(int t=2;t<=200;t++){

        if(t%2==0){
            for(int i=0;i<r;i++){
                for(int j=0;j<c;j++){
                    if(map[i][j]==9) {
                        map[i][j]=3;
                    } else{
                        map[i][j]--;
                    }
                }
            }
        } else {
            for(int i=0;i<r;i++){
                for(int j=0;j<c;j++){
                    if(map[i][j]!=9) map[i][j]--;
                    if(map[i][j]==0) {
                        map[i][j]=9;
                        for(int k=0;k<4;k++){
                            int nx = j + dx[k];
                            int ny = i + dy[k];
                            
                            if(nx>=0 && nx < c && ny >=0 && ny < r){
                                if(map[ny][nx]!=1) map[ny][nx]=9;
                            }
                       }
                   }
                }
            }
        }
        if(t==n) break;
    }
            
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(map[i][j]==9) cout << '.';
            else cout << 'O';
        }
        cout << '\n';
    }
}

/*
    Approach:
        [1] at even time, bomb is added to the blank spaces
        [2] at odd  time, bomb is exploded (after 3 second)
        [!] be careful when exploding adjacent bombs
            - do not explode the adjacent bomb that explodes at the same time
            - the adjacent bomb will explode itself -> exploding it will impact the adjacent bomb's adjancents
            - so only explode adjacent bombs that are scheduled to explode LATER
    Time Complexity:
        O(200*RC)=O(RC)
*/