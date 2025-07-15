#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT       100
#define CMD_INSERT     200
#define CMD_MOVECURSOR 300
#define CMD_COUNT      400

extern void init(int H, int W, char mStr[]);
extern void insert(char mChar);
extern char moveCursor(int mRow, int mCol);
extern int countCharacter(char mChar);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static bool run()
{
	bool correct = false;
	int queryCnt;
	scanf("%d", &queryCnt);
	int H, W;
	char mChar;
	static char mStr[90001];

	while (queryCnt--)
	{
		int cmd;
		scanf("%d", &cmd);

		if (cmd == CMD_INIT)
		{
			scanf("%d %d %s", &H, &W, mStr);
			init(H, W, mStr);
			correct = true;
		}
		else if (cmd == CMD_INSERT)
		{
			scanf(" %c", &mChar);
			insert(mChar);
		}
		else if (cmd == CMD_MOVECURSOR)
		{
			int mRow, mCol;
			scanf("%d %d", &mRow, &mCol);

			char ret = moveCursor(mRow, mCol);

			char ans;
			scanf(" %c", &ans);
			if (ret != ans)
			{
				correct = false;
			}
		}
		else if (cmd == CMD_COUNT)
		{
			scanf(" %c", &mChar);

			int ret = countCharacter(mChar);

			int ans;
			scanf("%d", &ans);
			if (ret != ans)
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
	freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}
	return 0;
}

#include <iostream>  // Add this for cout
#include <cstring>   // Add this for memset
using namespace std; // Add this for cout without std::

struct node {
	char data;
	node* next;
	node* prev;
}Node[90002];

int node_cnt;
int R,C;
node* head;
node* cursor;
node* line[301];
int line_alph[301][30];
int cur_loc;

void printAll() {
	node* cur = head;
	int i = 0;
	while (cur->next != nullptr) {
		cur = cur->next;
		if (i % R == 0) cout << "\n";
		cout << cur->data << " ";
		i++;
	}
	//cout << "\nnum of nodes : " << node_cnt << "\n";
	cout << "\t\t\t cursor's Left : " << cursor->data<< "\n";
	for (int i = 0; line[i]!=nullptr; i++) {
		//cout << "line " << i << " : " << line[i]->data << "\n";
		cout << "Line " << i << " count : " << line_alph[i]['e' - 'a'] << "\n";
	}
}

node* getNode(char c) {
	Node[++node_cnt].data = c;
	Node[node_cnt].next = nullptr;
	Node[node_cnt].prev = nullptr;
	return &Node[node_cnt];
}

void init(int H, int W, char mStr[])
{
	R = W;
	C = H;
	for (int i = 1; i < H; i++) {
		line[i] = nullptr;
	}
	memset(line_alph,0,sizeof(line_alph));
	node_cnt = -1;

	head = getNode('\0');
	line[0] = head;
	cursor = head;
	cur_loc = 0;
	
	node* cur = head;

	node* tmp;
	for (int i = 0; i < H * W; i++) {
		if (mStr[i] == '\0') break;
		tmp = getNode(mStr[i]);
		line_alph[i / R][mStr[i] - 'a']++;
		if (node_cnt % R == 0) {
			line[node_cnt / R] = tmp;
		}
		cur->next = tmp;
		tmp->prev = cur;
		cur = cur->next;
	}
	
}

void insert(char mChar)
{
	node* newNode = getNode(mChar);
	line_alph[cur_loc / R][mChar - 'a']++;
	if (node_cnt % R == 1) {
		node* tmp = line[(node_cnt / R) - 1];
		while (tmp->next != nullptr)
			tmp = tmp->next;
		line[(node_cnt / R)] = tmp;
	}
	newNode->next = cursor->next;
	newNode->prev = cursor;
	if(cursor->next != nullptr)
		cursor->next->prev = newNode;
	cursor->next = newNode;
	cursor = cursor->next;
	cur_loc++;
	
	for (int i = ((cur_loc-1)/R) + 1; line[i] != nullptr; i++) {
		if (i == 0) continue;
		int a = line[i]->data;
		line[i] = line[i]->prev;
		line_alph[i][a-'a']++;
		line_alph[i-1][a - 'a']--;
	}
}

char moveCursor(int mRow, int mCol)
{
	int loc = (mRow-1) * R + mCol-1;
	if (loc >= node_cnt) {
		while (cursor->next != nullptr) {
			cursor = cursor->next;
		}
		cur_loc = node_cnt;

		return '$';
	}
	else{
		cur_loc = loc;		
		cursor = line[loc/R];
		loc = loc % R;
		while (loc--) {
			cursor = cursor->next;
		}
		char res = cursor->next->data;
		return res;
	}

}

int countCharacter(char mChar)
{
	int res =0;
	node* cur = cursor;
	while (cur != line[cur_loc/R + 1] && cur->next !=nullptr) {
		cur = cur->next;
		if (cur->data == mChar)
			res++;
	}
	for (int i = cur_loc / R + 1; line[i] != nullptr; i++) {
		res += line_alph[i][mChar - 'a'];
	}

	return res;
}