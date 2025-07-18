#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>

extern void init(int N);
extern void follow(int uId1, int uId2, int timestamp);
extern void makePost(int uId, int pId, int timestamp);
extern void like(int pId, int timestamp);
extern void getFeed(int uId, int timestamp, int pIdList[]);

static int mSeed;
static int pseudo_rand(void)
{
	mSeed = mSeed * 431345 + 2531999;
	return mSeed & 0x7FFFFFFF;
}

static int follow_status[1005][1005];
static int answer_score;
static int n; // n >= 2 && n <= 1000
static int end_timestamp;
static int follow_ratio; // follow_ratio >= 1 && follow_ratio <= 10000
static int make_ratio; // make_ratio >= 1 && make_ratio <= 10000
static int like_ratio; // like_ratio >= 1 && like_ratio <= 10000
static int get_feed_ratio; // get_feed_ratio >= 1 && get_feed_ratio <= 10000
static int post_arr[200000];
static int total_post_cnt;
static int min_post_cnt;

static bool run()
{
	int uId1, uId2, pId, pIdList[10], ans_pIdList[10], rand_val;
	bool ret = true;

	scanf("%d%d%d%d%d%d%d", &mSeed, &n, &end_timestamp, &follow_ratio, &make_ratio, &like_ratio, &get_feed_ratio);
	init(n);

	for (int uId1 = 1; uId1 <= n; uId1++)
	{
		follow_status[uId1][uId1] = 1;
		int m = n / 10 + 1;
		if (m > 10)
			m = 10;
		for (int i = 0; i < m; i++)
		{
			uId2 = uId1;
			while (follow_status[uId1][uId2] == 1)
			{
				uId2 = pseudo_rand() % n + 1;
			}
			follow(uId1, uId2, 1);
			follow_status[uId1][uId2] = 1;
		}
	}
	min_post_cnt = total_post_cnt = 1;

	for (int timestamp = 1; timestamp <= end_timestamp; timestamp++)
	{
		rand_val = pseudo_rand() % 10000;
		if (rand_val < follow_ratio)
		{
			uId1 = pseudo_rand() % n + 1;
			uId2 = pseudo_rand() % n + 1;
			int lim = 0;
			while (follow_status[uId1][uId2] == 1 || uId1 == uId2)
			{
				uId2 = pseudo_rand() % n + 1;
				lim++;
				if (lim >= 5)
					break;
			}
			if (follow_status[uId1][uId2] == 0)
			{
				follow(uId1, uId2, timestamp);
				follow_status[uId1][uId2] = 1;
			}
		}
		rand_val = pseudo_rand() % 10000;

		if (rand_val < make_ratio)
		{
			uId1 = pseudo_rand() % n + 1;
			post_arr[total_post_cnt] = timestamp;

			makePost(uId1, total_post_cnt, timestamp);
			total_post_cnt += 1;
		}

		rand_val = pseudo_rand() % 10000;

		if (rand_val < like_ratio && total_post_cnt - min_post_cnt > 0)
		{
			while (post_arr[min_post_cnt] < timestamp - 1000 && min_post_cnt < total_post_cnt)
				min_post_cnt++;

			if (total_post_cnt != min_post_cnt)
			{
				pId = pseudo_rand() % (total_post_cnt - min_post_cnt) + min_post_cnt;
				like(pId, timestamp);
			}
		}

		rand_val = pseudo_rand() % 10000;
		if (rand_val < get_feed_ratio && total_post_cnt > 0)
		{
			uId1 = pseudo_rand() % n + 1;
			getFeed(uId1, timestamp, pIdList);

			for (int i = 0; i < 10; i++)
			{
				scanf("%d", ans_pIdList + i);
			}

			for (int i = 0; i < 10; i++)
			{
				if (ans_pIdList[i] == 0)
					break;

				if (ans_pIdList[i] != pIdList[i])
				{
					ret = false;
				}
			}
		}
	}

	return ret;
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);
	int tc;
	scanf("%d%d", &tc, &answer_score);

	for (int t = 1; t <= tc; t++)
	{
		int score;
		for (int i = 0; i < 1005; i++)
			for (int j = 0; j < 1005; j++)
				follow_status[i][j] = 0;

		if (run())
			score = answer_score;
		else
			score = 0;

		printf("#%d %d\n", t, score);
	}
	return 0;
}


#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

struct post{
	int pid;
	int uid;
	int like;
	int timestamp;

	post() {
        pid = 0;
        uid = 0;
        like = 0;
        timestamp = 0;
    } 

	post(int p, int u, int l, int t) {
        pid = p;
        uid = u;
        like = l;
        timestamp = t;
    } 

};

struct PostLessComparator {
    bool operator()(const post& a, const post& b) const {
        if (a.like != b.like) {
            return a.like < b.like; 
        }
        return a.timestamp < b.timestamp; 
    }
};

struct PostMoreComparator {
    bool operator()(const post& a, const post& b) const {
        return a.timestamp < b.timestamp;
    }
};

vector<unordered_set<int>>follower_info;
vector<vector<int>>my_post;
unordered_map<int,post>post_info;
vector<priority_queue<post,vector<post>,PostLessComparator>>less_than_th;
vector<priority_queue<post,vector<post>,PostMoreComparator>>more_than_th;

int _N;

void init(int N)
{
    follower_info.clear();
	my_post.clear();
	less_than_th.clear();
	more_than_th.clear();
    post_info.clear();
    follower_info.resize(N+1);
	my_post.resize(N+1);
	less_than_th.resize(N+1);
	more_than_th.resize(N+1);
}

void follow(int uID1, int uID2, int timestamp)
{
    follower_info[uID1].insert(uID2);
	// PRINT FOLLOW
    // cout << uID1 << " followed " << uID2 << endl;
    // cout << uID1 << ": ";
    // for(auto it = follower_info[uID1].begin();it!=follower_info[uID1].end();it++){
    //     cout << *it << " ";
    // }
    // cout << endl;
}

void makePost(int uID, int pID, int timestamp)
{
	post_info[pID] = post(pID, uID, 0,timestamp);
	my_post[uID].push_back(pID);
	// PRINT POST
    // cout << uID << " posted " << pID << endl;
    // cout << uID << ": ";
    // for(auto it = post_info[uID].begin();it!=post_info[uID].end();it++){
    //     cout << it->first << " ";
    // }
    // cout << endl;
}

void like(int pID, int timestamp)
{
	post_info[pID].like++;
}


bool compare(const post& a, const post& b, int timestamp){
	bool a_recent = timestamp-a.timestamp <= 1000;
	bool b_recent = timestamp-b.timestamp <= 1000;
	if(a_recent && !b_recent) return true;
	if(!a_recent && b_recent) return false;

	if (a_recent && b_recent) {
        if (a.like != b.like) {
            return a.like > b.like;
        }
        return a.timestamp > b.timestamp;
    } else {
        return a.timestamp > b.timestamp;
    }
}

void getFeed(int uID, int timestamp, int pIDList[])
{
	//mine
	vector<post> post_list;
	for(int i=0;i<my_post[uID].size();i++){
		post_list.push_back(post_info[my_post[uID][i]]);
	}

	//followers
	int cnt = 0;
	for(auto it = follower_info[uID].begin();it!=follower_info[uID].end();it++){
        for(int i=0;i<my_post[*it].size();i++){
			post_list.push_back(post_info[my_post[*it][i]]);
			cnt++;
		}
    }

	
	sort(post_list.begin(), post_list.end(), [timestamp](const post& a, const post& b) {
        return compare(a, b, timestamp);
    });

	int len = post_list.size();

	// for(int i=0;i<len;i++){
	// 	cout << post_list[i].pid << " " ;
	// }
	// cout << endl;


	if(len>10) len = 10;
	for (int i = 0; i < len; i++) {
        pIDList[i] = post_list[i].pid;
    }

}