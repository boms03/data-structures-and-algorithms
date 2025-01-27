#include<iostream>
#include<cmath>
#include<climits>
#include<algorithm>
#include<vector>
#include<unordered_map>
using namespace std;
int n;
vector<long long>seg_tree;
vector<int>row_b;
unordered_map<int,int>conversion;

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

    cin >> n;
    int tree_height = ceil(log2(n));
    int tree_size = 1 << (tree_height+1);
    int start_index = tree_size/2;
    seg_tree.resize(tree_size);

    for (int i=1; i<=n; i++){
        int a;
        cin >> a;
        conversion[a]=i;
    }

    for (int i=0; i<n; i++){
        int b;
        cin >> b;
        row_b.push_back(conversion[b]);
    }

    long long ans = 0;

    for (int i=0; i<n;i++){
        ans += query(row_b[i]+start_index,tree_size-1);
        update(row_b[i]+start_index-1);
    }
    cout << ans << '\n';

}