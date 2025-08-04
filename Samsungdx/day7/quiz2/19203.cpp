#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT    1
#define CMD_APPEND  2
#define CMD_CUT     3
#define CMD_REVERSE 4
#define CMD_COUNT   5

extern void init(char mStr[]);
extern void appendWord(char mWord[]);
extern void cut(int k);
extern void reverse();
extern int countOccurrence(char mWord[]);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static bool run()
{
	bool correct = false;
	int queryCnt;
	scanf("%d", &queryCnt);
	static char mStr[30001], mWord[5];

	while (queryCnt--)
	{
		int cmd;
		scanf("%d", &cmd);

		if (cmd == CMD_INIT)
		{
			scanf("%s", mStr);
			init(mStr);
			correct = true;
		}
		else if (cmd == CMD_APPEND)
		{
			scanf("%s", mWord);
			
			if (correct)
			{
				appendWord(mWord);
			}
		}
		else if (cmd == CMD_CUT)
		{
			int k;
			scanf("%d", &k);
			
			if (correct)
			{
				cut(k);
			}
		}
		else if (cmd == CMD_REVERSE)
		{
			if (correct)
			{
				reverse();
			}
		}
		else if (cmd == CMD_COUNT)
		{
			scanf("%s", mWord);

			int ret = -1;
			if (correct)
			{
				ret = countOccurrence(mWord);
			}

			int ans;
			scanf("%d", &ans);
			if(ret != ans)
			{
				correct = false;
			}
		}
	}
	return correct;
}

int main()
{
	setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}
	return 0;
}

#include<cstring>

struct Node{
    char alpha;
    Node* next;
    Node* prev;
} node[120001];

int cnt_node;
bool reversed;
Node* head;
Node* tail;

void init(char mStr[])
{
    cnt_node = 0;
    reversed = false;
    for(int i=0;i<strlen(mStr);i++){
        node[cnt_node].alpha=mStr[i];
        if(i>0){
            node[cnt_node].prev=&node[cnt_node-1];
            node[cnt_node-1].next=&node[cnt_node];
        }
        cnt_node++;
    }
    head = &node[0];
    tail = &node[cnt_node-1];
    //O(N)
}

void appendWord(char mWord[])
{
    if(!reversed){
        Node* cur_prev = tail;
        for(int i=0;i<strlen(mWord);i++){
            node[cnt_node].alpha=mWord[i];
            node[cnt_node].prev=cur_prev;
            cur_prev=
            cnt_node++;
        }

    }
    } else {

    }
    //O(1)
}

void cut(int k)
{
    //O(1)
}

void reverse()
{
    //O(N)

}

int countOccurrence(char mWord[])
{
	//O(N)
}

//길이 최대 12만