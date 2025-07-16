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
    unordered_map<int,Node*>child;
    int cnt;
    int dir;
}; 

struct Tree {
    Node* root;
};

unordered_map<int,string>mapping;
Tree tree;

const int mod = 1610612741;
int nameHash(const char* s) {
    int h = 0;
    for (int i = 0; s[i]; i++) {
        h = (h * (long long)127 + s[i]) % mod;
    }
	mapping[h]=s;
    return h;
}

Node* findNode(const char* path){
	Node* cur = tree.root;
	int len = strlen(path);
	for(int i=1;i<len-1;i++){
		char token[7];
		int j=0;
		while(i<len && path[i]!='/'){
			token[j++]=path[i++];
		}
		token[j]='\0';
		int hash = nameHash(token);
		cur = cur->child[hash];
	}
	return cur;
}

void printTree(Node* cur){
	if(cur==nullptr) return;
	cout << mapping[cur->dir]<<endl;
	
	for(unordered_map<int,Node*>::iterator it = cur->child.begin();it!=cur->child.end();it++){
		printTree(it->second);
		cout << endl;
	}
}

void init(int n) {
    Node* newNode = new Node();
    newNode->dir = nameHash("/");
    newNode->cnt = 0;
	newNode->parent = nullptr;
    tree.root = newNode;
}

// const char* parse(const char* path){
// 	//cout << "parsing " << path << endl;
// 	string parent_dir = string(path);
//     int len = strlen(path);
//     if(len!=1){
//         int i = len-2;
//         while(path[i]!='/'){
//             i--;
//         }
//         parent_dir = parent_dir.substr(i+1,len-i-2);
//     }
// 	//cout << "parsed " << parent_dir << endl;
// 	return parent_dir;
// }

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
	//cout << "mkdir " << endl;
    //string parent_dir = parse(path);
    Node* parent = findNode(path);
    Node* newNode = new Node();
	int hash = nameHash(name);
    newNode->dir = hash;
	newNode->cnt = 0;
    newNode->parent=parent;
    parent->child[hash]=newNode;

	Node* curNode = parent;
	while(curNode){
		curNode->cnt++;
		//cout << curNode->dir << endl;
		curNode=curNode->parent;
	}
    //cout << parent->dir << endl;
	//cout << tree.root->cnt << endl;
	//printTree(tree.root);
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
	//cout << "rm" << endl;
	//string path_dir = parse(path);
	//cout << path_dir << endl;
	Node* node = findNode(path);
	node->parent->child.erase(node->dir);
	//cout << tree.nodes[path_dir]->parent->cnt << " sub " << tree.nodes[path_dir]->cnt << endl;
	Node* curNode = node->parent;
	while(curNode){
		curNode->cnt-=(node->cnt+1);
		//cout << curNode->dir << endl;
		curNode=curNode->parent;
	}
	//printTree(tree.root);
}

Node* clone_tree(Node* src, Node* prt){
	if(src==nullptr) return nullptr;
	Node* newNode = new Node();
	newNode->parent=prt;
	newNode->dir=src->dir;
	newNode->cnt=src->cnt;
	for(unordered_map<int,Node*>::iterator it = src->child.begin();it!=src->child.end();it++){
		Node* childNode = clone_tree(it->second,newNode);
		newNode->child[childNode->dir]=childNode;
	}
	//printTree(tree.root);
	return newNode;
}
void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	//cout << "cp" << endl;

	Node* src = findNode(srcPath);
	Node* dst = findNode(dstPath);
	Node* cloneNode = clone_tree(src,dst);

	Node* curNode = dst;
	curNode->child[cloneNode->dir]=cloneNode;

	while(curNode){
		curNode->cnt += (cloneNode->cnt+1);
		curNode=curNode->parent;
		//cout << curNode->dir << endl;
	}
		
	//cout << tree.root->cnt << endl;
	//cout << parent_dir << endl;
	//printTree(tree.root);
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	//cout << "mv" << endl;
	//cout << srcPath << " to " << dstPath << endl;
	Node* src = findNode(srcPath);
	Node* dst = findNode(dstPath);

	Node* curNode = src->parent;
	while(curNode){
		curNode->cnt-=(src->cnt+1);
		curNode=curNode->parent;
		//cout << curNode->dir << endl;
	}

	src->parent->child.erase(src->dir);
	src->parent= dst;
	dst->child[src->dir]=src;
	
	curNode = dst;
	while(curNode){
		curNode->cnt+=(src->cnt+1);
		curNode=curNode->parent;
		//cout << curNode->dir << endl;
	}
	//cout << tree.root->cnt << endl;
	//printTree(tree.root);
}

int cmd_find(char path[PATH_MAXLEN + 1]) {
	//cout << "find" << endl;
	Node* node = findNode(path);
	//cout <<node->cnt << endl;
	return node->cnt;
}