#include<iostream>
#include<cmath>
#include<climits>
#include<vector>
#include<algorithm>
using namespace std;
vector<vector<int>>mst;

int n,m;

void init(int node, int s, int e){
    if(s==e) return;
    int mid = (s+e)>>1;
    init(node*2,s,mid);
    init(node*2+1,mid+1,e);
    mst[node].resize(mst[node*2].size()+mst[node*2+1].size());
    merge(mst[node*2].begin(),mst[node*2].end(),mst[node*2+1].begin(),mst[node*2+1].end(),mst[node].begin());
}

int query(int node, int s, int e, int q_s, int q_e, int k){
    if(q_e < s || q_s > e) return 0;
    if(q_s<=s && e <=q_e){
        return upper_bound(mst[node].begin(),mst[node].end(),k)-mst[node].begin();
    }
    int mid = (s+e)>>1;
    return query(node*2,s,mid,q_s,q_e,k) + query(node*2+1,mid+1,e,q_s,q_e,k);
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m;
    int tree_height = ceil(log2(n));
    int tree_size = 1 << (tree_height+1);
    int start_index = tree_size/2;
    mst.resize(tree_size);

    for (int i=0;i<n;i++){
        int val;
        cin >> val;
        mst[i+start_index].push_back(val);
    }

    init(1,start_index,tree_size-1);

    while(m--){
        int a,b,c;
        cin >> a >> b >> c;
        int l = -1e9;
        int r = 1e9;
        while(l<=r){
            int mid = (l+r)>>1;
            if(query(1,start_index,tree_size-1,a+start_index-1,b+start_index-1,mid) < c) l = mid + 1;
            else r = mid -1;
        }
        cout << l << '\n';
    }
}
