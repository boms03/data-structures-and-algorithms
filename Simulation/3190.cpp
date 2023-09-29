#include<iostream>
#include<deque>
using namespace std;

int n,k,ax,ay,l,x;
char c;
int map[102][102]={0,};
deque<pair<int,char>>turn;
int dx[]={0,1,0,-1};
int dy[]={-1,0,1,0};

void Print()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

void start(){
    deque<pair<int,int>>path;
    int cx = 0,cy = 0,nx = 0,ny = 0,tx =0 ,ty=0, time = 0;
    map[0][0]=2;
    path.push_front({0,0});
    int direction = 1;
    while(true){
        time++;

        nx = cx + dx[direction];
        ny = cy + dy[direction];

        if (nx < 0 || nx >= n || ny < 0 || ny >= n || map[ny][nx]==2) break;

        if(map[ny][nx]==3){
            map[ny][nx]=2;
            path.push_front({nx,ny});
        } else {
            map[ny][nx]=2;
            map[path.back().second][path.back().first]=0;
            path.pop_back();
            path.push_front({nx,ny});
        }
        cx = nx;
        cy = ny;

        if(turn.back().first==time){
            if(turn.back().second=='D'){
                direction = (direction + 1)%4; 
            } else if (turn.back().second=='L'){
                direction = (direction + 3)%4; 
            }
            turn.pop_back();
        }
    }
    cout << time << '\n';
}
int main(){
    cin >> n;
    cin >> k;
    for(int i=0;i<k;i++){
        cin >> ay >> ax;
        map[ay-1][ax-1] = 3;
    }
    cin >> l;
    for(int i=0;i<l;i++){
        cin >> x >> c;
        turn.push_front({x,c});
    }
    start();

}

/*
    Approach:
        Use queue to keep all the indexs travled by the snake.

        Push_front the next index and pop_back when the snake traveles 0 (the length snake does not change).
        Push_front the next index only when the snake traveles 3 (apple) (the length increases by one).

        To calculate direction, I ordered elements in dx[] dy[] in clockwise order so that I can calculate R turn by (direction+1)%4 and L turn by (direction+3)%4.

    Time Complexity:
        Worst case when the snake turns at max(x) and travles n
        O(max(x)+n)
*/