#include<iostream>
#include<cmath>
#include<climits>
#include<vector>
#include<algorithm>
using namespace std;
vector<vector<int>>mst;
vector<pair<int,int>>coord;

int t,n;

bool comp(pair<int,int> a , pair<int,int>b){
    if (a.first != b.first) return a.first > b.first;
    return a.second < b.second;
}

void init(int node, int s, int e){
    if(s==e) return;
    int mid = (s+e)>>1;
    init(node*2,s,mid);
    init(node*2+1,mid+1,e);
    mst[node].resize(mst[node*2].size()+mst[node*2+1].size());
    merge(mst[node*2].begin(),mst[node*2].end(),mst[node*2+1].begin(),mst[node*2+1].end(),mst[node].begin());
}

long long query(int node, int s, int e, int q_s, int q_e, int k){
    if(q_e < s || q_s > e) return 0;
    if(q_s<=s && e <=q_e){
        return upper_bound(mst[node].begin(),mst[node].end(),k) - mst[node].begin();
    }
    int mid = (s+e)>>1;
    return query(node*2,s,mid,q_s,q_e,k) + query(node*2+1,mid+1,e,q_s,q_e,k);
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> t;
    while(t--){
        cin >> n;
        for(int i=0;i<n;i++){
            int x,y;
            cin >> x >> y;
            coord.push_back({x,y});
        }

        sort(coord.begin(),coord.end(),comp);

        int tree_height = ceil(log2(n));
        int tree_size = 1 << (tree_height+1);
        int start_index = tree_size/2;
        mst.resize(tree_size);

        for (int i=0;i<n;i++){
            mst[i+start_index].push_back(coord[i].second);
        }

        init(1,start_index,tree_size-1);

        long long cnt=0;
        for (int i=1;i<n;i++){
            cnt += query(1,start_index,tree_size-1,start_index,i+start_index-1,coord[i].second);
        }
        cout << cnt << '\n';

        coord.clear();
        mst.assign(0,vector<int>());
    }
}
