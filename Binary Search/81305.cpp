#include <string>
#include <vector>

using namespace std;

constexpr int max_k = 10000;
int people[max_k];
int child[max_k][2];
int root;
int parent[max_k];
int limit;
int cnt;

int dfs(int node){
    if(node == -1) return 0;
    if(people[node]>limit){
        cnt = max_k+1;
        return people[node];
    }
    
    int l = dfs(child[node][0]);
    int r = dfs(child[node][1]);
    
    if(l+r+people[node]<=limit){
        return l+r+people[node];
    }
    
    // 여기서 부터는 잘라내야함
    
    
    // 자식 노드 하나만 있는데 잘라내는 경우
    if(l==0 || r==0){
        cnt++;
        return people[node];
    }
    
    // 자식이 노드가 2개 있는데 잘라내는 경우 -> 둘중 한쪽만 자르기
    if(l+people[node]<=limit && r+people[node]<=limit){
        cnt++;
        return l<r ? l+people[node] : r+people[node]; // 더 큰쪽 끊어내기
    }
    
    // 자식이 노드가 2개 있는데 한쪽만 자르는 경우
    if(l+people[node]<=limit){
        cnt++;
        return l+people[node];
    }
    
    if(r+people[node]<=limit){
        cnt++;
        return r+people[node];
    }
    
    // 둘 다 자르는 경우
    
    cnt+=2;
    return people[node];
    
}
bool check(int mid, int root, int k){
    cnt = 0;
    limit = mid;
    dfs(root);
    if(cnt<k) return true;
    return false;
}

int solution(int k, vector<int> num, vector<vector<int>> links) {
    int sum = 0;
    for(int i=0;i<num.size();i++){
        people[i]=num[i];
        sum+=num[i];
        parent[i]=-1;
    }
    for(int i=0;i<links.size();i++){
        child[i][0]=links[i][0];
        child[i][1]=links[i][1];
        parent[child[i][0]]= i;
        parent[child[i][1]]= i;
    }
    for(int i=0;i<num.size();i++){
        if(parent[i]==-1){
            root = i;
            break;
        }
    }
    int left = sum/k;
    int right = sum;
    while(left<=right){
        int mid = (left+right)/2;
        if(check(mid,root,k)){
            right = mid-1;
        } else {
            left = mid+1;
        }
    }
    return left;
    
}

/*
    Approach:
        We have to make the number of largest group as large as possible.
        To do this, use parametric search to test every possible number that can create up to k groups.
        Finding edges of binary tree that should be cut to satisfy 

        [1] Build binary tree
        [2] Parametic search to find the maximum possible people in a group 
            - left boundary is sum of all people divided by k number of group as this is the least possible number in a group
            - right boundary is just sum of all people
        [3] Check() method checks if it can create less than k group when the maximum people in a group is picked (mid)
        [4] Depth First Search to check how many cuts should happen
            - Possible senarios are..
                - keep adding as no need to cut 
                - need to cut but only one child exist
                    - 1 cut
                - need to cut but both childs can be cut
                    - 1 cut
                - need to cut but only one of childs should be cut
                    - 1 cut
                - need to cut but two childs should be cut
                    - 2 cuts
        [5] Add up the total number of cuts and check if it is less than k to see if the parametric search worked
            - if count < k, try less maximum number of people in a groun
                - right = mid-1
            - if count > k, try larger numbers to reduce cuts required
                - left = mid+1
    Time Complexity:
        O(logN)

*/