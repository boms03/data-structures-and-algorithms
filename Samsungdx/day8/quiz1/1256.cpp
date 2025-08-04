/////////////////////////////////////////////////////////////////////////////////////////////
// 기본 제공코드는 임의 수정해도 관계 없습니다. 단, 입출력 포맷 주의
/////////////////////////////////////////////////////////////////////////////////////////////

#include<iostream>
#include<string>
#include<map>
#include<cstdio>

using namespace std;

const int MAX_NODES = 100001; 

struct node{
    char alpha;
    map<char,node*>children;
    bool isEnd;
    node(): isEnd(false) {}
} Node[MAX_NODES];

int k;
string result;

void printInOrder(node* node, int counter, string currentPath) {
    if (node->isEnd) {
        counter++;
        cout << counter << ": \"" << currentPath << "\n";
    }
    
    for (auto& pair : node->children) {
        char ch = pair.first;
        currentPath.push_back(ch);
        printInOrder(pair.second, counter, currentPath);
        currentPath.pop_back();
    }
}

bool findKth(node* node, int& counter, string& currentPath) {
    if (node->isEnd) {
        counter++;
        if(counter == k){
            result = currentPath;
            return true;
        }
    }
    
    for (auto& pair : node->children) {
        char ch = pair.first;
        currentPath.push_back(ch);
        if(findKth(pair.second, counter, currentPath)) return true;
        currentPath.pop_back();
    }
    return false;
} 

void initNodes() {
    for(int i = 0; i < MAX_NODES; i++) {
        Node[i].children.clear();
        Node[i].isEnd = false;
        Node[i].alpha = '\0';
    }
}

int main(int argc, char** argv)
{
    int test_case;
    int T;
    
    freopen("input.txt", "r", stdin); 
    cin >> T;
    
    for(test_case = 1; test_case <= T; ++test_case)
    {
        int cur_node = 1;
        string s;
        result = "";
        
        cin >> k >> s;
        
        // 노드 초기화
        initNodes();
        
        for(int i = 0; i < s.length(); i++){
            node* cur = &Node[0];
            
            for(int j = i; j < s.length(); j++){
                if(cur->children.find(s[j]) == cur->children.end()){
                    Node[cur_node].alpha = s[j];
                    cur->children[s[j]] = &Node[cur_node];
                    cur_node++;
                }
                cur = cur->children[s[j]];
            }
                 
            cur->isEnd = true;
        }
        
        
        int cnt = 0;
        string ss = "";
        findKth(&Node[0], cnt, ss);
        
        cout << "#" << test_case << " " << result << '\n';
        
    }
    return 0;
}

/*
메모리 사용량 분석:
- 문자열 길이 400인 경우
- 최악의 경우 필요 노드: 400 × 401 / 2 = 80,200개
- 설정된 배열 크기: 100,001개
- 여유분: 약 20%

테스트 케이스:
5
1 a
3 abc
1 abcdefghijklmnopqrstuvwxyz
100 banana
5 hello

예상 출력:
#1 a
#2 c
#3 a
#4 none  
#5 o
*/