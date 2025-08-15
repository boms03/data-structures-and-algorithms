#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define MAX_MAP_SIZE 350

extern void init(int N, int mMaxStamina, int mMap[MAX_MAP_SIZE][MAX_MAP_SIZE]);
extern void addGate(int mGateID, int mRow, int mCol);
extern void removeGate(int mGateID);
extern int getMinTime(int mStartGateID, int mEndGateID);

/////////////////////////////////////////////////////////////////////////

#define CMD_INIT			0
#define CMD_ADD_GATE		1
#define CMD_REMOVE_GATE		2
#define CMD_GET_MIN_TIME	3

static int gMap[MAX_MAP_SIZE][MAX_MAP_SIZE];

static bool run()
{
	int cmd, ans, ret;
	int N, maxStamina, gateID1, gateID2, row, col;
	int Q = 0;
	bool okay = false;

	scanf("%d", &Q);

	for (int q = 0; q < Q; ++q)
	{
		scanf("%d", &cmd);

		switch (cmd)
		{
		case CMD_INIT:
			scanf("%d %d", &N, &maxStamina);
			for (int i = 0 ; i <= N - 1 ; i++) {
				for (int j = 0 ; j <= N - 1 ; j++) {
					scanf("%d", &gMap[i][j]);
				}
			}
			init(N, maxStamina, gMap);
			okay = true;
			break;

		case CMD_ADD_GATE:
			scanf("%d %d %d", &gateID1, &row, &col);
			addGate(gateID1, row, col);
			break;

		case CMD_REMOVE_GATE:
			scanf("%d", &gateID1);
			removeGate(gateID1);
			break;

		case CMD_GET_MIN_TIME:
			scanf("%d %d", &gateID1, &gateID2);
			ret = getMinTime(gateID1, gateID2);
			scanf("%d", &ans);
			if (ret != ans)
				okay = false;
			break;

		default:
			okay = false;
		}
	}

	return okay;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1 ; tc <= T ; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}

#include <queue>
#include <cstring>
#include <iostream>
#include <vector>
#define MAP_SIZE_MAX	350
using namespace std;

int map[MAP_SIZE_MAX][MAP_SIZE_MAX];
int gates[MAP_SIZE_MAX][MAP_SIZE_MAX];
vector<unordered_map<int,int>> adj(201);
pair<int,int> gateID[201];

bool removed[201];
int maxStamina;;
int n;
int dx[]={-1,1,0,0};
int dy[]={0,0,-1,1};
bool visited[MAP_SIZE_MAX][MAP_SIZE_MAX][101];

void init(int N, int mMaxStamina, int mMap[MAP_SIZE_MAX][MAP_SIZE_MAX])
{
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            map[i][j]=mMap[i][j]; 
            gates[i][j]=0;
        }
    }
    for(int i = 0; i <= 200; i++) {
        adj[i].clear(); 
    }
    memset(removed,0,sizeof(removed));
    maxStamina = mMaxStamina;
    n = N;
	return;
}

void addGate(int mGateID, int mRow, int mCol)
{
    gates[mRow][mCol] = mGateID;
    gateID[mGateID] = {mRow, mCol};

    static bool visited[MAP_SIZE_MAX][MAP_SIZE_MAX];
    memset(visited, false, sizeof(visited));

    struct Node { int y, x, dist; };
    queue<Node> q;
    q.push({mRow, mCol, 0});
    visited[mRow][mCol] = true;

    auto add_edge = [&](int a, int b, int w) {
        auto it = adj[a].find(b);
        if (it == adj[a].end()) {
            adj[a][b] = w;
        } else if (w < it->second) {
            it->second = w;
        }
    };

    while (!q.empty()) {
        Node cur = q.front(); q.pop();
        if (cur.dist == maxStamina) continue;

        for (int d = 0; d < 4; d++) {
            int ny = cur.y + dy[d];
            int nx = cur.x + dx[d];
            if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
            if (map[ny][nx] == 1) continue;

            int gid = gates[ny][nx];
            if (gid != 0 && gid != mGateID && !removed[gid]) {
                add_edge(mGateID, gid, cur.dist + 1);
                add_edge(gid, mGateID, cur.dist + 1);
            }

            if (!visited[ny][nx]) {
                visited[ny][nx] = true;
                q.push({ny, nx, cur.dist + 1});
            }
        }
    }
}


void removeGate(int mGateID)
{
    //cout << "remove " << mGateID << endl;
    removed[mGateID]=true;
	return;
}

int getMinTime(int mStartGateID, int mEndGateID)
{
    //cout << "start " << mStartGateID << "to" << mEndGateID << endl;
    vector<int> dist(201, 1e9);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; 
    pq.push({0,mStartGateID});
    dist[mStartGateID]=0; 
    while(!pq.empty()){
        pair<int,int> top = pq.top();
        pq.pop();
        //cout << top.first << " " << top.second << endl;

        if (removed[top.second]) {
            continue;
        }

        if(top.second == mEndGateID){
            //cout << top.first << endl;
            return top.first;
        }

        if (top.first > dist[top.second]) {
            continue;
        }

        for (auto &pair : adj[top.second]){

            if (removed[pair.first]) {
                continue;
            }
            if(dist[pair.first]>pair.second + top.first){
                dist[pair.first] = pair.second + top.first;
                pq.push({pair.second + top.first, pair.first});
            }
        }
    }
    //cout << -1 << endl;
	return -1;
}



/*
    getMinTime 800번 -> 얘가 많다는건 얘를 줄이라는거임
    3차원 BFS -> 350 * 350 * 100 * 800 > 1억
    addGate() 및 removeGate()는 200 이하
    200 * 350 * 350 * 100
    
*/