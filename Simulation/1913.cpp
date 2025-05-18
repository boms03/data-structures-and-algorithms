// Online C++ compiler to run C++ program online
#include <iostream>
#include <algorithm>
using namespace std;
int map[1000][1000];
int n,k, ax,ay;
int main() {
    cin >> n;
    cin >> k;
    
    int side = n;
    int o_x = 0;
    int o_y = 0;
    int number = n*n;
    while(side>0){
        int cur_x = o_x;
        int cur_y = o_y;
    
        if(side==1){
            map[cur_y][cur_x]=number;
            if(number==k){
                ax = cur_x;
                ay = cur_y;
            }
            break;
        }
        //아래
        for(int i=0;i<side-1;i++){
            map[cur_y][cur_x]=number;
            if(number==k){
                ax = cur_x;
                ay = cur_y;
            }
            number--;
            cur_y++;
        }
        //오른쪽
        for(int i=0;i<side-1;i++){
            map[cur_y][cur_x]=number;
            if(number==k){
                ax = cur_x;
                ay = cur_y;
            }
            number--;
            cur_x++;
        }
        //위로
        for(int i=0;i<side-1;i++){
            map[cur_y][cur_x]=number;
            if(number==k){
                ax = cur_x;
                ay = cur_y;
            }
            number--;
            cur_y--;
        }
        //왼쪽
        for(int i=0;i<side-1;i++){
            map[cur_y][cur_x]=number;
            if(number==k){
                ax = cur_x;
                ay = cur_y;
            }
            number--;
            cur_x--;
        }
        o_x++;
        o_y++;
        side-=2;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
    cout << ay+1 << " " << ax+1;
}