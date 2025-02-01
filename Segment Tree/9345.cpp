#include<iostream>
#include<cmath>
#include<climits>
#include<vector>

using namespace std;
using pii = pair<int,int>;

vector<pii>seg_tree;


int t,n,m, tree_size;

void init(int node, int s, int e){
    if(s==e) return;
    int mid = (s+e) >> 1;
    init(node*2,s,mid);
    init(node*2+1,mid+1,e);
    seg_tree[node] = {min(seg_tree[node*2].first,seg_tree[node*2+1].first),max(seg_tree[node*2].second,seg_tree[node*2+1].second)};
}

void update(int node, int s, int e, int u_idx, int val){
    if(u_idx > e || u_idx < s) return;

    if(s==e){
        seg_tree[node] = {val, val};
        return;
    }

    int mid = (s+e)>>1;
    update(node*2,s,mid,u_idx,val);
    update(node*2+1,mid+1,e,u_idx,val);
    seg_tree[node] = {min(seg_tree[node*2].first,seg_tree[node*2+1].first), max(seg_tree[node*2].second,seg_tree[node*2+1].second)};
}

pii query(int node, int s, int e, int q_s, int q_e){
    if(q_e < s || q_s > e) return {INT_MAX,-1};
    if(q_s<=s && e<=q_e) return seg_tree[node];
    int mid = (s+e)>>1;
    pii l = query(node*2,s,mid,q_s,q_e);
    pii r = query(node*2+1,mid+1,e,q_s,q_e);
    return {min(l.first,r.first),max(l.second,r.second)};
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> t;
    while(t--){
        cin >> n >> m;
        int tree_height = ceil(log2(n));
        tree_size = 1 << (tree_height+1);
        int start_index = tree_size >> 1;
        seg_tree.resize(tree_size);
        for(int i=0;i<n;i++){
            seg_tree[i+start_index] = {i,i};
        }

        init(1,start_index,tree_size-1);
        while(m--){
            int a, b, c;
            cin >> a >> b >> c;
            if(a==0){
                int temp = seg_tree[b+start_index].first;
                update(1,start_index,tree_size-1,b+start_index,seg_tree[c+start_index].first);
                update(1,start_index,tree_size-1,c+start_index,temp);
            } else {
                pii q = query(1,start_index,tree_size-1,b+start_index, c+start_index);
                if(q.first == b && q.second == c) cout << "YES\n";
                else cout << "NO\n";
            }
        }
        seg_tree.clear();
    }
}