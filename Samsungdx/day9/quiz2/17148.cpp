#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 100
#define CMD_DESTROY 200
#define CMD_UPDATE 300
#define CMD_UPDATE_TYPE 400
#define CMD_CALC 500

void init(int N, int M, int mType[], int mTime[]);
void destroy();
void update(int mID, int mNewTime);
int updateByType(int mTypeID, int mRatio256);
int calculate(int mA, int mB);

#define MAX_N 100000

static int mType[MAX_N];
static int mTime[MAX_N];

static int run()
{
	int C;
	int isOK = 0;
	int cmd, ret, chk;

	int N, M;
	int mID, mTypeID, mNewTime, mRatio;
	int mA, mB;

	scanf("%d", &C);

	for (int c = 0; c < C; ++c)
	{
		scanf("%d", &cmd);
		switch (cmd)
		{
		case CMD_INIT:
			scanf("%d %d ", &N, &M);
			for (int i = 0; i < N - 1; i++) scanf("%d", &mType[i]);				
			for (int i = 0; i < N - 1; i++) scanf("%d", &mTime[i]);
			init(N, M, mType, mTime);
			isOK = 1;
			break;

		case CMD_UPDATE:
			scanf("%d %d", &mID, &mNewTime);
			update(mID, mNewTime);			
			break;

		case CMD_UPDATE_TYPE:
			scanf("%d %d", &mTypeID, &mRatio);
			ret = updateByType(mTypeID, mRatio);
			scanf("%d", &chk);
			if (ret != chk)
				isOK = 0;
			break;

		case CMD_CALC:
			scanf("%d %d", &mA, &mB);
			ret = calculate(mA, mB);
			scanf("%d", &chk);
			if (ret != chk)
				isOK = 0;
			break;

		default:
			isOK = 0;
			break;
		}
	}
	destroy();
	return isOK;
}

int main()
{
	setbuf(stdout, NULL);
    freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		if (run()) printf("#%d %d\n", tc, MARK);
		else printf("#%d %d\n", tc, 0);
	}
	return 0;
}


#include <vector>
#include <iostream>
#define MAX_N 100000
#define MAX_M 1000
using namespace std;

vector<vector<int>>track_type(MAX_M);

int segtree[MAX_N*4];
int* arr;
int n;

void build(int node, int s, int e){
    if(s==e){
        segtree[node]=arr[s];
        //cout << node << " " << s << " " << arr[s] << endl;
        return;
    }
    int mid = (s+e)/2;
    build(node*2,s,mid);
    build(node*2+1,mid+1,e);
    segtree[node]= segtree[node*2]+segtree[node*2+1];
}

void update_seg(int node, int s, int e, int idx, int val){
    if(s==e){
        segtree[node]=val;
        arr[idx] = val;
        return;
    }
    int mid = (s+e)/2;
    if(idx<=mid) update_seg(node*2,s,mid,idx, val);
    else update_seg(node*2+1,mid+1,e, idx,val);
    segtree[node] = segtree[node*2] + segtree[node*2+1];
}

int query_seg(int node, int s, int e, int l , int r){
    if(r < s || l > e) return 0;
    if(l<=s && e<=r) return segtree[node];
    int mid = (s+e)/2;
    return query_seg(node*2,s,mid,l,r) + query_seg(node*2+1,mid+1,e,l,r);
}


void init(int N, int M, int mType[], int mTime[])
{
    //cout << "init" << endl;
    n = N;
    arr = mTime;
    build(1,0,N-2);
    for(int i=0;i<N-1;i++){
        track_type[mType[i]].push_back(i);
    }
    for(int i=1;i<N*4;i++){
        cout << segtree[i] << ' ';
    }
    cout << endl;
}

void destroy()
{
    //cout << "destroy" << endl;
    for (int i = 0; i < MAX_M; i++) {
        track_type[i].clear();
    }
    memset(segtree, 0, sizeof(segtree));
}

void update(int mID, int mNewTime)
{
    //cout << "update" << endl;
    update_seg(1,0,n-2, mID, mNewTime);
}

int updateByType(int mTypeID, int mRatio256)
{
    //cout << "updatetype" << endl;
    int sum = 0;
    for(int idx: track_type[mTypeID]){
        int change = (arr[idx] * mRatio256) / 256;
        sum += change;
        update(idx,change);
    }
	return sum;
}

int calculate(int mA, int mB)
{
    //cout << "calc" << endl;
    if(mB<mA) swap(mA,mB);
	int calc = query_seg(1,0,n-2,mA,mB-1);
    //cout << calc << endl;
    return calc;
}