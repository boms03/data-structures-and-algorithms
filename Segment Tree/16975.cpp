#include<iostream>
#include<vector>
#include<cmath>
#include<climits>
using namespace std;

int N,M;

vector<long long>seg_tree;
vector<long long>lazy;


void propagate(int node, int left, int right){
    if (lazy[node]){
        int mid = (left+right)/2;
        seg_tree[2*node] += (mid-left+1) * lazy[node];
        lazy[2*node]+=lazy[node];
        seg_tree[2*node+1] += (right-mid) * lazy[node];
        lazy[2*node+1]+=lazy[node];
        lazy[node]=0;
    }
}

// O(N)
void init(int node, int left, int right){
    if(left==right) return;
    int mid = (left+right)>>1;
    init(node*2,left,mid);
    init(node*2+1,mid+1,right);
    seg_tree[node]=seg_tree[node*2]+seg_tree[node*2+1];
}


void update(int node, int left, int right, int update_left, int update_right, int update_val){
    if(update_left > right || update_right < left) return;
    if(update_left<=left && right<=update_right){
        seg_tree[node] += (right-left+1) * update_val;
        lazy[node]+=update_val;
        return;
    }

    propagate(node,left,right);
    
    int mid = (left+right)>>1;
    update(node*2,left,mid,update_left,update_right,update_val);
    update(node*2+1,mid+1,right,update_left,update_right,update_val);
    seg_tree[node] = seg_tree[node*2]+seg_tree[node*2+1];
}

long long query(int node, int left, int right, int query_left, int query_right){
    if(query_left > right || query_right < left) return 0;
    if(query_left<=left && right<=query_right) return seg_tree[node];

    propagate(node,left,right);

    int mid = (left+right)>>1;
    return query(node*2,left,mid,query_left,query_right) + query(node*2+1,mid+1,right,query_left,query_right);
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;

    int height = ceil(log2(N));
    int size = (1 << (height+1));
    int start_index = size/2;
    seg_tree.resize(size+1);
    lazy.resize(size+1);

    for (int i=start_index; i<start_index+N; i++){
        cin >> seg_tree[i];
    }

    init(1,start_index,size-1);

    cin >> M;

    for(int i=0;i<M;i++){
        int a,b,c,d;
        cin >> a >> b;

        switch(a){
            case 1:
                cin >> c >> d;
                update(1,start_index,size-1,b+start_index-1,c+start_index-1,d);
                // for(int i=1;i<size;i++){
                //     cout << "node: " << seg_tree[i].idx <<  " " << seg_tree[i].min << " ";
                // }
                // cout << endl;
                break;
            case 2:
                cout << query(1,start_index,size-1,b+start_index-1,b+start_index-1) << '\n';
                break;
        }
    }
}