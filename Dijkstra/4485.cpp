#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

int N;
int cnt=1;
int map[126][126];
int dist[126][126];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};

void dijkstra(){
    memset(dist,-1,sizeof(dist)); // reset dist to -1
    priority_queue< pair<int,pair<int,int>>,vector<pair<int,pair<int,int>> >,greater<pair<int,pair<int,int> > > > pq; // min heap priority queue
    pq.push({dist[0][0],{0,0}}); // initialize pq by pushing the starting element
    dist[0][0]=map[0][0]; // initialize distance of the staring element

    while(!pq.empty()){
        int d = pq.top().first; // current distance from the starting point
        int x = pq.top().second.first; // x index of current point
        int y = pq.top().second.second; // y index of current point
        pq.pop(); 

        for (int i=0; i<4; i++){
            int nx = x + dx[i]; // x index of next point
            int ny = y + dy[i]; // y index of next point
            if (nx >= 0 && nx<N && ny >= 0 && ny <N){ 
                if (dist[ny][nx]==-1 || d+map[ny][nx]<dist[ny][nx]){ // not visited yet or new distance smaller
                    dist[ny][nx]=dist[y][x]+map[ny][nx]; // update distance
                    pq.push({dist[ny][nx],{nx,ny}}); // min heap new distance
                }
            }
        }
    }

}
int main(){
    while(true){
        cin >> N;
        if(N==0){
            break;
        }
        for (int i=0;i<N;i++){
            for (int j=0;j<N;j++){
                cin >> map[i][j];
            }
        }
        dijkstra();
        cout << "Problem " << cnt << ": " << dist[N-1][N-1] << endl;
        cnt++;
    }
}

/*

    O( 2*|e|log_2 N)
*/ 

/*
    assume every vertex has 4 edges: E = N^2 * 4
    O(N^2log_2 N^2)
*/ 
