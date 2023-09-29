#include<iostream>
#include<queue>
#include <climits>
using namespace std;

int N,K,t,x,nx,nt;
int dx[3]= {2,-1,1};
int dt[3]= {0,1,1};
int st[100001];

void dijkstra(int start){
    fill(st,st+100001,INT_MAX);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int> > > pq;
    pq.push({0,start}); // initialize pq
    st[start]=0; // initialize the shortest time to the starting point

    while(!pq.empty()){
        t = pq.top().first; // current time
        x = pq.top().second; // current point
        pq.pop();

        if (x==K){
            break; 
        }

        for (int i=0; i<3; i++){
            // next point 
            if (i==0) nx = x*dx[i]; 
            else nx = x + dx[i]; 

            // possible shortest time to the next point
            nt = t + dt[i];

            if (nx>=0 && nx <100001){
                if (nt < st[nx]){
                    st[nx] = nt; // update the shortest time from N to nx
                    pq.push({nt,nx}); // min heap the shortest time from N to nx
                }
            }
        }
    }
}
int main(){
    cin >> N >> K;
    dijkstra(N);
    cout << st[K] << endl;
}

/*
    Assume every vertex has 3 edges(-1,+1,*2): E = 3V 
    V = |K-N|
    The weight of *2 is 0 and that of -1 and 1 is 1 so 0-1 bfs also works O(V+E) which is faster than dijkstra.
    O(3Vlog_2 V)
*/ 
