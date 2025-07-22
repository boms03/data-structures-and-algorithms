#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern int init(int N, int sCity[], int eCity[], int mCost[]);
extern void add(int sCity, int eCity, int mCost);
extern int cost(int mHub);

/////////////////////////////////////////////////////////////////////////

#define MAX_N 1400
#define CMD_INIT 1
#define CMD_ADD 2
#define CMD_COST 3

static bool run() {
	int q;
	scanf("%d", &q);

	int n;
	int sCityArr[MAX_N], eCityArr[MAX_N], mCostArr[MAX_N];
	int sCity, eCity, mCost, mHub;
	int cmd, ans, ret = 0;
	bool okay = false;

	for (int i = 0; i < q; ++i) {
		scanf("%d", &cmd);
		switch (cmd) {
			case CMD_INIT:
				okay = true;
				scanf("%d", &n);
				for (int j = 0; j < n; ++j) {
					scanf("%d %d %d", &sCityArr[j], &eCityArr[j], &mCostArr[j]);
				}
				scanf("%d", &ans);
				ret = init(n, sCityArr, eCityArr, mCostArr);
				if (ans != ret)
					okay = false;
				break;
			case CMD_ADD:
				scanf("%d %d %d", &sCity, &eCity, &mCost);
				add(sCity, eCity, mCost);
				break;
			case CMD_COST:
				scanf("%d %d", &mHub, &ans);
				ret = cost(mHub);
				if (ans != ret)
					okay = false;
				break;
			default:
				okay = false;
				break;
		}
	}
	return okay;
}

int main() {
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++) {
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}


#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
#include<algorithm>
#define pii pair<int,int>
using namespace std;

vector<vector<pii>>info;
vector<vector<pii>>info_reverse;
unordered_map<int,int>h;
int cur;
int total_cities;

int init(int N, int sCity[], int eCity[], int mCost[]) {
    //cout << "init" << endl;
    info.clear();
    info_reverse.clear();
    h.clear();
    info.resize(601);
    info_reverse.resize(601);

    vector<int> all;
    for(int i = 0; i < N; i++) {
        all.push_back(sCity[i]);
        all.push_back(eCity[i]);
    }

    sort(all.begin(),all.end());
    all.erase(unique(all.begin(),all.end()),all.end());

    for(int i=0;i<all.size();i++) h[all[i]]=i;

    for(int i=0;i<N;i++){
        info[h[sCity[i]]].push_back({h[eCity[i]],mCost[i]});
        info_reverse[h[eCity[i]]].push_back({h[sCity[i]],mCost[i]});
    }

    total_cities=all.size();
    return total_cities;
}

void add(int sCity, int eCity, int mCost) {
    //cout << "add" << endl;
	info[h[sCity]].push_back({h[eCity],mCost});
    info_reverse[h[eCity]].push_back({h[sCity],mCost});
}

int dijkstra(int s, vector<vector<pii>>& inf){
    //cout << "dijk" << endl;
    vector<int> dist(total_cities, 1e9);
    priority_queue<pii, vector<pii>, greater<pii>>pq;
    dist[s]=0;
    pq.push({0,s});
    while(!pq.empty()){
        int cost = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if(cost > dist[node]) continue;

        //cout << node << endl;

        for(int i=0;i<inf[node].size();i++){
            int next_node = inf[node][i].first;
            int next_cost = cost + inf[node][i].second;
            if(dist[next_node] > next_cost){
                dist[next_node] = next_cost;
                pq.push({next_cost,next_node});
            }
        }
    }

    int total = 0;
    for(int i=0;i<total_cities;i++){
        if(dist[i] != 1e9) {
            total += dist[i];
        }
    }
    //cout << total << endl;
    return total;
}

int cost(int mHub) {
    //cout << "cost" << endl;
	int ans = dijkstra(h[mHub],info) + dijkstra(h[mHub],info_reverse);
    //cout << ans << endl;
    return ans;
}