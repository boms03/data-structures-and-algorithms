#include<iostream>
#include<cmath>
#include<climits>
#include<algorithm>
#include<vector>
using namespace std;
int n,m;
vector<long long>seg_tree;
vector<pair<int,int>>edges;

void update(int update_index){
    while(update_index>0){
        seg_tree[update_index]++;
        update_index/=2;
    }
}

long long query(int start_index, int end_index){
    int total = 0;
    while(start_index<=end_index){

        if(start_index & 1){
            total += seg_tree[start_index++];
        }

        if(!(end_index & 1)){
            total += seg_tree[end_index--];
        }

        start_index/=2;
        end_index/=2;
    }
    return total;
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    int tree_height = ceil(log2(2000));
    int tree_size = 1 << (tree_height+1);
    int start_index = tree_size/2;
    seg_tree.resize(tree_size);

    for (int i=0; i<m; i++){
        int a,b;
        cin >> a >> b;
        edges.push_back({a,b});
    }

    sort(edges.begin(),edges.end());

    long long ans = 0;
    for (int i=0; i<m;i++){
        ans += query(edges[i].second+start_index,tree_size-1);
        update(edges[i].second+start_index-1);
    }
    cout << ans << '\n';

}