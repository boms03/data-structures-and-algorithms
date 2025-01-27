#include<iostream>
#include<cmath>
#include<climits>
#include<algorithm>
#include<vector>
#include<unordered_map>
using namespace std;
int t,n,m;
int top_index;
vector<int>pos;
vector<int>seg_tree;


void init(int start_index){
    for(int i=start_index;i>=1;i--){
        seg_tree[i] = seg_tree[i*2] + seg_tree[i*2+1];
    }
}

void update(int update_index,int diff){
    while(update_index>0){
        seg_tree[update_index]+=diff;
        update_index/=2;
    }
}

long long query(int start_index, int end_index){
    long long total = 0;
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

    cin >> t;

    while(t--){
        cin >> n >> m;

        int tree_height = ceil(log2(n+m));
        int tree_size = 1 << (tree_height+1);
        int start_index = tree_size/2;
        seg_tree.resize(tree_size);
        pos.resize(n);

        for(int i=start_index;i<start_index+n;i++){
            seg_tree[i]=1;
        }

        for(int i=0;i<n;i++){
            pos[n-i]=start_index+i;
        }

        init(start_index-1);

        top_index = pos[1];

        for(int i=0;i<m;i++){
            int a;
            cin >> a;
            cout << query(pos[a]+1,tree_size-1) << " ";
            update(pos[a],-1);
            update(top_index+1,1);
            pos[a] = top_index+1;
            top_index++;
        }

        // for(int j=1;j<tree_size;j++){
        //     cout << seg_tree[j]<<" ";
        // }
        // cout << endl;

        // for(int i=n;i>=1;i--){
        //     cout << pos[i]<<" ";
        // }
        // cout << endl;

        cout << '\n';
        seg_tree.clear();
        pos.clear();
    }
}