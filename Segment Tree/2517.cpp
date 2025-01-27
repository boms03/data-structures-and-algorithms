#include<iostream>
#include<cmath>
#include<climits>
#include<algorithm>
#include<vector>
#include<unordered_map>
using namespace std;
int n;
vector<int>seg_tree;
vector<pair<int,int>>input;

bool compare(pair<int,int>a, pair<int,int>b){
    return a.second < b.second;
}

void update(int update_index){
    while(update_index>0){
        seg_tree[update_index]++;
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

    cin >> n;
    input.resize(n);

    for(int i=0;i<n;i++){
        cin >> input[i].first;
        input[i].second = i;
    }

    sort(input.begin(),input.end());

    for(int i=0;i<n;i++){
        input[i].first = i+1;
    }

    sort(input.begin(),input.end(), compare);

    int tree_height = ceil(log2(n));
    int tree_size = 1 << (tree_height+1);
    int start_index = tree_size/2;
    seg_tree.resize(tree_size);

    for (int i=1; i<=n;i++){
        int a = input[i-1].first;
        int cnt = query(start_index,a+start_index-2);
        update(a+start_index-1);
        // for(int j=1;j<=tree_size;j++){
        //     cout << seg_tree[j]<<" ";
        // }
        // cout << endl;
        cout << i-cnt << '\n';
    }

}