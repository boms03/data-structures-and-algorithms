#include<iostream>
#include<cmath>
#include<climits>
#include<vector>
using namespace std;

int n,m;
vector<int>seg_tree;
vector<int>lazy;

void init(int node, int s, int e){
    if (s==e) return;
    int mid = (s+e)>>1;
    init(node*2,s,mid);
    init(node*2+1,mid+1,e);
    seg_tree[node] = seg_tree[node*2] ^ seg_tree[node*2+1];
}


void propagate(int node, int s, int e){
    if (lazy[node]){
        if((e-s+1) & 1){
            seg_tree[node] ^= lazy[node];
        }
        lazy[2*node] = lazy[node];
        lazy[2*node+1] = lazy[node];
        lazy[node] = 0;
    }
}

void update(int node, int s, int e, int u_s, int u_e, int val){
    propagate(node,s,e);
    if(u_e < s || u_s > e) return;
    if(u_s<=s && e<=u_e){
        lazy[node] ^= val;
        propagate(node,s,e);
        return;
    }
    int mid = (s+e)>>1;
    update(node*2,s,mid,u_s,u_e,val);
    update(node*2+1,mid+1,e,u_s,u_e,val);
    seg_tree[node] = seg_tree[node*2] ^ seg_tree[node*2+1];
}

int query(int node, int s, int e, int u_s, int u_e){
    propagate(node,s,e);
    if(u_e < s || u_s > e) return 0;
    if(u_s<=s && e<=u_e){
        return seg_tree[node];
    }
    int mid = (s+e)>>1;
    return query(node*2,s,mid,u_s,u_e) ^ query(node*2+1,mid+1,e,u_s,u_e);
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    int tree_height = ceil(log2(n));
    int tree_size = 1 << (tree_height+1);
    int start_index = tree_size/2;
    seg_tree.resize(tree_size);
    lazy.resize(tree_size);

    for(int i=start_index;i<start_index+n;i++){
        cin >> seg_tree[i];
    }

    init(1,start_index,tree_size-1);

    cin >> m;
    while(m--){
        // for(int i=1;i<tree_size;i++){
        //     cout << seg_tree[i] << " ";
        // }
        // cout << endl;
        int a,b,c,d;
        cin >> a >>  b >> c;
        int s = min(b,c)+start_index;
        int e = max(b,c)+start_index;
        switch(a){
            case 1:
                cin >> d;
                update(1,start_index,tree_size-1,s,e,d);
                break;
            case 2:
                cout << query(1,start_index,tree_size-1,s,e) << '\n';
                
        }
    }

}