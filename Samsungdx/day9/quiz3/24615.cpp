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
#include <iostream>
#define MAP_SIZE_MAX	350
using namespace std;

int map[MAP_SIZE_MAX][MAP_SIZE_MAX];
int gates[MAP_SIZE_MAX][MAP_SIZE_MAX];
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
        gateID[i] = {-1, -1};
    }
    memset(removed,0,sizeof(removed));
    maxStamina = mMaxStamina;
    n = N;
	return;
}

void addGate(int mGateID, int mRow, int mCol)
{
    gates[mRow][mCol]= mGateID;
    gateID[mGateID]={mRow,mCol};
	return;
}

void removeGate(int mGateID)
{
    removed[mGateID]=true;
	return;
}

struct State {
    int x, y, stamina, time;
};

int getMinTime(int mStartGateID, int mEndGateID)
{
    //cout << "min" << endl;
    bool visited_gate[201];
    vector<pair<int,int>>next_gates;
    memset(visited, false, sizeof(visited));

    int startX = gateID[mStartGateID].second;
    int startY = gateID[mStartGateID].first;
    int endX = gateID[mEndGateID].second;
    int endY = gateID[mEndGateID].first;

    queue<State>q;
    q.push({startX, startY, maxStamina, 0});
    visited[startY][startX][maxStamina] = true;
    
    while(!q.empty()){
        State current = q.front();
        q.pop();
        
        int x = current.x;
        int y = current.y;
        int stamina = current.stamina;
        int time = current.time;

        if (x == endX && y == endY) {
            //cout << time << endl;
            return time;
        }

        for(int i=0;i<4;i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if (map[ny][nx] == 1) continue;
            if (stamina <= 0) continue;
            int newStamina = stamina - 1;
            int newTime = time + 1;

            int gateID = gates[ny][nx];
            if (gateID != 0 && !removed[gateID] && gateID != mStartGateID && gateID != mEndGateID) {
                newStamina = maxStamina;
            }
            if (visited[ny][nx][newStamina]) continue;
            visited[ny][nx][newStamina] = true;
            q.push({nx, ny, newStamina, newTime});
        }
    }
	return -1;
}



/*
    getMinTime 800번 -> 얘가 많다는건 얘를 줄이라는거임
    3차원 BFS -> 350 * 350 * 100 * 800 > 1억
    addGate() 및 removeGate()는 200 이하
    200 * 350 * 350 * 100
    
*/