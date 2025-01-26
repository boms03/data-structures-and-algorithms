#include<iostream>
#include<vector>
#include<cmath>
#include<climits>
using namespace std;

int N,M;

vector<long long>seg_tree;

// O(N)
void init(int size){
    for(int i= size/2-1;i>=1;i--){
        seg_tree[i] = min(seg_tree[i*2], seg_tree[i*2+1]);
    }
}

// O(N)
int find(int start_idx, int end_idx){
    long long mini = LLONG_MAX;
    while (start_idx<=end_idx){
        if(start_idx & 1){
            mini = min(mini, seg_tree[start_idx]);
            start_idx++;
        }
        if(!(end_idx & 1)){
            mini = min(mini, seg_tree[end_idx]);
            end_idx--;
        }
        start_idx/=2;
        end_idx/=2;
    }
    return mini;
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
        cin >> seg_tree[i];
    }

    for (int i = start_index + N; i < size; i++) {
        seg_tree[i] = LLONG_MAX;
    }

    init(size);

    // for(int i=1;i<size;i++){
    //     cout << "node: " << seg_tree[i].min << " " << seg_tree[i].max << " ";
    // }
    // cout << endl;

    for(int i=0;i<M;i++){
        int a,b;
        cin >> a >> b;
        cout << find(a+start_index-1,b+start_index-1) << '\n';
    }
}