#ifndef _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS 
#endif

#include<stdio.h>

#define CMD_MKDIR 1
#define CMD_RM 2
#define CMD_CP 3
#define CMD_MV 4
#define CMD_FIND 5

#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999

extern void init(int n);
extern void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]);
extern void cmd_rm(char path[PATH_MAXLEN + 1]);
extern void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]);
extern void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]);
extern int cmd_find(char path[PATH_MAXLEN + 1]);

static bool run(int m) {

	bool isAccepted = true;
	int cmd;
	char name[NAME_MAXLEN + 1];
	char path1[PATH_MAXLEN + 1], path2[PATH_MAXLEN + 1];

	while (m--) {

		scanf("%d", &cmd);

		if (cmd == CMD_MKDIR) {
			scanf("%s%s", path1, name);
			cmd_mkdir(path1, name);
		}
		else if (cmd == CMD_RM) {
			scanf("%s", path1);
			cmd_rm(path1);
		}
		else if (cmd == CMD_CP) {
			scanf("%s%s", path1, path2);
			cmd_cp(path1, path2);
		}
		else if (cmd == CMD_MV) {
			scanf("%s%s", path1, path2);
			cmd_mv(path1, path2);
		}
		else {
			int ret;
			int answer;

			scanf("%s", path1);
			ret = cmd_find(path1);
			scanf("%d", &answer);

			isAccepted &= (ret == answer);
		}
	}

	return isAccepted;
}

int main(void) {

	int test, T;
	int n, m;

	freopen("sample_input.txt", "r", stdin);

	setbuf(stdout, NULL);

	scanf("%d", &T);

	for (test = 1; test <= T; ++test) {

		scanf("%d%d", &n, &m);

		init(n);

		if (run(m)) {
			printf("#%d 100\n", test);
		}
		else {
			printf("#%d 0\n", test);
		}
	}

	return 0;
}

#include<unordered_map>
#include<iostream>
#include<string>
#include<cstring>
#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999
using namespace std;

// The below commented functions are for your reference. If you want 
// to use it, uncomment these functions.
/*
int mstrcmp(const char *a, const char *b)
{
	int i;
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return a[i] - b[i];
}

int mstrncmp(const char *a, const char *b, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return 0;
}

int mstrlen(const char *a)
{
	int len = 0;

	while (a[len] != '\0')
		len++;

	return len;
}

void mstrcpy(char *dest, const char *src)
{
	int i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
}

void mstrncpy(char *dest, const char *src, int len)
{
	for (int i = 0; i<len; i++)
	{
		dest[i] = src[i];
	}
	dest[len] = '\0';
}
*/

struct Node {
    Node* parent;
    unordered_map<string,Node*>child;
    int cnt;
    string dir;
}; 

struct Tree {
    unordered_map<string, Node*> nodes;
    Node* root;
};

Tree tree;
void init(int n) {
    Node* newNode = new Node();
    newNode->dir = "/";
    newNode->cnt = 1;
    tree.root = newNode;
    tree.nodes["/"]=newNode;
}

string parse(char path[PATH_MAXLEN + 1]){
	string parent_dir = string(path);
    int len = strlen(path);
    if(len!=1){
        int i = len-2;
        while(path[i]!='/'){
            i--;
        }
        parent_dir = parent_dir.substr(i+1,len-2);
    }
	return parent_dir;
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
    string parent_dir = parse(path);
    Node* parent = tree.nodes[parent_dir];
    Node* newNode = new Node();
    newNode->dir = name;
    newNode->cnt = 1;
    newNode->parent=parent;
    parent->child[name]=newNode;
    parent->cnt++;
    tree.nodes[name]=newNode;
    //cout << parent->dir << endl;
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
	string parent_dir = parse(path);
	cout << parent_dir << endl;

}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	string parent_dir = parse(srcPath);
	cout << parent_dir << endl;
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	string parent_dir = parse(srcPath);
	cout << parent_dir << endl;
}

int cmd_find(char path[PATH_MAXLEN + 1]) {
	string parent_dir = parse(path);
	cout << parent_dir << endl;
	return 0;
}