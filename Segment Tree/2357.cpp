#include<iostream>
#include<vector>
#include<cmath>
#include<climits>
using namespace std;

int N,M;

typedef struct{
    long long min;
    long long max;
} node;

vector<node>seg_tree;

// O(N)
void init(int size){
    for(int i= size/2-1;i>=1;i--){
        seg_tree[i].max=  max(seg_tree[i*2].max, seg_tree[i*2+1].max);
        seg_tree[i].min = min(seg_tree[i*2].min, seg_tree[i*2+1].min);
    }
}

// O(N)
node find(int start_idx, int end_idx){
    node ans = {LLONG_MAX,0};
    while (start_idx<=end_idx){
        if(start_idx & 1){
            ans.max = max(ans.max,seg_tree[start_idx].max);
            ans.min = min(ans.min,seg_tree[start_idx].min);
            start_idx++;
        }
        if(!(end_idx & 1)){
            ans.max = max(ans.max,seg_tree[end_idx].max);
            ans.min = min(ans.min,seg_tree[end_idx].min);
            end_idx--;
        }
        start_idx/=2;
        end_idx/=2;
    }
    return ans;
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;

    int height = ceil(log2(N));
    int size = (1 << (height+1));
    int start_index = size/2;
    seg_tree.resize(size+1);

    for (int i=start_index; i<start_index+N; i++){
        long long value;
        cin >> value;
        seg_tree[i] = {value,value};
    }

    for (int i = start_index + N; i < size; i++) {
        seg_tree[i] = {LLONG_MAX, 0};
    }

    init(size);

    // for(int i=1;i<size;i++){
    //     cout << "node: " << seg_tree[i].min << " " << seg_tree[i].max << " ";
    // }
    // cout << endl;

    for(int i=0;i<M;i++){
        int a,b;
        cin >> a >> b;
        node ans = find(a+start_index-1,b+start_index-1);
        cout << ans.min << " " << ans.max << '\n';
    }
}