#include<iostream>
#include<cmath>
#include<climits>
#include<vector>
using namespace std;

typedef struct{
    long long sum;
    long long min;
    int index;
} node;

int n, tree_size, start_index;
long long ans = 0;
vector<node>seg_tree;

void init(int node, int s, int e ){
    if(s==e) return;
    int mid = (s+e)>>1;
    init(node*2,s,mid);
    init(node*2+1,mid+1,e);
    seg_tree[node].sum = seg_tree[node*2].sum+seg_tree[node*2+1].sum;
    if(seg_tree[node*2].min < seg_tree[node*2+1].min){
        seg_tree[node].min = seg_tree[node*2].min;
        seg_tree[node].index = seg_tree[node*2].index;
    } else{
        seg_tree[node].min = seg_tree[node*2+1].min;
        seg_tree[node].index = seg_tree[node*2+1].index;
    }
}

node query(int n, int s, int e, int q_s, int q_e){
    if (q_e < s || q_s > e){
        return {0,LLONG_MAX,0};
    }
    else if (q_s <= s && e <= q_e) return seg_tree[n];

    int mid = (s+e)>>1;
    
    node l = query(n*2,s,mid,q_s,q_e);
    node r = query(n*2+1,mid+1,e,q_s,q_e);
    long long sum = l.sum + r.sum;
    if(l.min < r.min){
        return {sum,l.min,l.index};
    } else {
        return {sum,r.min,r.index};
    }
}

// void solve(int left, int right){
//     if (left > right) return;
//     int mid = find(left,right);
//     long long m_area = (right-left+1)*(long long)arr[mid];
//     ans = max(ans,m_area);
//     solve(left,mid-1);
//     solve(mid+1,right);
// }

void solve(int s, int e){
    if (s>e){
        return;
    }
    node result = query(1,start_index,tree_size-1,s,e);
    ans = max(ans,result.sum*result.min);
    solve(s,result.index-1);
    solve(result.index+1,e);
}

int main(){
    cin >> n;
    int tree_height = ceil(log2(n));
    tree_size = 1 << (tree_height+1);
    start_index = tree_size/2;
    seg_tree.resize(tree_size);

    for (int i=start_index;i<start_index+n;i++){
        cin >> seg_tree[i].sum;
        seg_tree[i].min = seg_tree[i].sum;
        seg_tree[i].index = i;
    }

    for (int i=start_index+n;i<tree_size;i++){
        seg_tree[i].min = LLONG_MAX;
    }

    init(1,start_index,tree_size-1);

    // for(int i=1;i<tree_size;i++){
    //     cout << seg_tree[i].index << " ";
    // }
    // cout << endl;

    solve(start_index,start_index+n-1);

    cout << ans << '\n';
}