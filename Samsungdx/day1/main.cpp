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

#include <iostream>  
#include <cstring>  
using namespace std; 

struct node {
	char data;
	node* next;
	node* prev;
} Node[90002];

int w,h;
int row_alpha[301][27];
int cnt_node;
node* row_head[301];
int row_cnt[301];
node* row_tail[301];
node* cursor;
int cur_row;

void print(){
	for(int i=0;i<h;i++){
		node* cur = row_head[i];
		while(cur!=nullptr){
			cout << cur->data << " ";
			cur=cur->next;
		}
		cout << endl;
	}
}

void init(int H, int W, char mStr[])
{
	cout << "init" << endl;
	w = W;
	h = H;
	cnt_node = 0;
	memset(row_head,0,sizeof(row_head));
	memset(row_tail,0,sizeof(row_tail));
	memset(row_alpha,0,sizeof(row_alpha));
	memset(row_cnt,0,sizeof(row_cnt));
	memset(Node,0,sizeof(Node));

	bool end;
	for(int i=0;i<H && !end;i++){
		row_head[i] = &Node[cnt_node];
		node* prev = nullptr;
		bool notHead = false;
		for(int j=0;j<W && !end;j++){
			char cur_char = mStr[i*W+j];
			if(cur_char=='\0'){
				end = true;
				break;
			}
			Node[cnt_node].data = cur_char;
			Node[cnt_node].next = nullptr;

			row_alpha[i][cur_char-'a']++;

			if(notHead){
				Node[cnt_node].prev = prev;
				prev->next = &Node[cnt_node];
			}
			else{
				notHead = true;
			}
			prev = &Node[cnt_node];
			cnt_node++;
			row_cnt[i]++;
		}
		row_tail[i]= &Node[cnt_node];
		prev->next = &Node[cnt_node];
		Node[cnt_node].prev = prev;
		Node[cnt_node].next = nullptr;
		cnt_node++;
	}

	//print();
	cursor = row_head[0];
	cur_row = 0;
}

void insert(char mChar)
{
	cout << "insert " << mChar << endl;
	cout << cur_row << " " << cursor->data << endl;
	Node[cnt_node].next = cursor;
	Node[cnt_node].prev = cursor->prev;
	Node[cnt_node].data = mChar;
	row_alpha[cur_row][mChar-'a']++;

	if(!cursor->prev){
		row_head[cur_row] = &Node[cnt_node];
	}
	else {
		cursor->prev->next = &Node[cnt_node];
	}
	cursor->prev = &Node[cnt_node];

	cnt_node++;

	for(int i=cur_row;i<h;i++){
		if(row_cnt[i]<w){
			row_cnt[i]++;
			break;
		}

		node* tail = row_tail[i];
		node* new_tail;
		node* new_head;

		if(tail->prev){
			new_tail = tail->prev->prev;
			new_head = tail->prev;
			tail->prev= new_tail;
			new_tail->next = tail;
		}
		node* cur_head = row_head[i+1];

		if(cur_head){
			cur_head->prev = new_head;
			new_head->next = cur_head;
		} else {
			row_tail[i+1]=new_head;
		}
		new_head->prev = nullptr;
		row_head[i+1]=new_head;
		row_alpha[i][new_head->data-'a']--;
		row_alpha[i+1][new_head->data-'a']++;
		//cout << new_head->data << " got moved!" << endl;
	}
	print();
	cout << cur_row << " " << cursor->data << endl;


}

char moveCursor(int mRow, int mCol)
{
	cout << "move " << mRow << " " << mCol << endl;
	cur_row = mRow-1;
	if(row_cnt[cur_row] < mCol){
		cursor = row_tail[cur_row];
		//cout << '$' << endl;
		return '$';
	}
	cursor = row_head[cur_row];
	int move = mCol-1;
	while(move-- && cursor->next != row_tail[cur_row]) cursor = cursor->next;
	//cout << cursor->data << endl;
	print();
	return cursor->data;
}

int countCharacter(char mChar)
{
	print();
	cout << "cnt " << mChar << endl;
	cout << cur_row << endl;
	cout << cursor->data << endl;
	int cnt = 0;

	//cout << "lets count"<< endl;
	for(int i=cur_row+1;i<h;i++){
		//cout << row_alpha[i][mChar-'a'] << endl;
		cnt += row_alpha[i][mChar-'a'];
	}

	node* temp = cursor;
	while(temp->next){
		//cout << temp->data << endl;
		if(temp->data == mChar) cnt++; 
		temp=temp->next;
	}
	cout << cnt << endl;
	return cnt;
}