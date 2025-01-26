#include<iostream>
#include<vector>
#include<cmath>
#include<climits>
using namespace std;

int N,M;

typedef struct{
    long long min;
    long long idx;
} node;

vector<node>seg_tree;

// O(N)
void init(int size){
    for(int i= size/2-1;i>=1;i--){
        if(seg_tree[i*2].min == seg_tree[i*2+1].min){
            seg_tree[i].min = seg_tree[i*2].min;
            seg_tree[i].idx = min(seg_tree[i*2].idx, seg_tree[i*2+1].idx);
        } else if (seg_tree[i*2].min < seg_tree[i*2+1].min){
            seg_tree[i].min = seg_tree[i*2].min;
            seg_tree[i].idx = seg_tree[i*2].idx;
        }
        else {
            seg_tree[i].min = seg_tree[i*2+1].min;
            seg_tree[i].idx = seg_tree[i*2+1].idx;
        }
    }
}


void update(int update_idx, long long update_val){
    seg_tree[update_idx].idx = update_idx;
    seg_tree[update_idx].min = update_val;
    update_idx/=2;
    while(update_idx>0){
        if(seg_tree[update_idx*2].min == seg_tree[update_idx*2+1].min){
            seg_tree[update_idx].min = seg_tree[update_idx*2].min;
            seg_tree[update_idx].idx = min(seg_tree[update_idx*2].idx, seg_tree[update_idx*2+1].idx);
        } else if (seg_tree[update_idx*2].min < seg_tree[update_idx*2+1].min){
            seg_tree[update_idx].min = seg_tree[update_idx*2].min;
            seg_tree[update_idx].idx = seg_tree[update_idx*2].idx;
        } else {
            seg_tree[update_idx].min = seg_tree[update_idx*2+1].min;
            seg_tree[update_idx].idx = seg_tree[update_idx*2+1].idx;
        }
        update_idx/=2;
    }
}

// O(N)
int find(int start_idx, int end_idx){
    long long mini = LLONG_MAX;
    long long ans;
    while (start_idx<=end_idx){
        if(start_idx & 1){
            if (mini > seg_tree[start_idx].min || 
                (mini == seg_tree[start_idx].min && ans > seg_tree[start_idx].idx)) {
                mini = seg_tree[start_idx].min;
                ans = seg_tree[start_idx].idx;
            }
            start_idx++;
        }
        if(!(end_idx & 1)){
            if (mini > seg_tree[end_idx].min || 
                (mini == seg_tree[end_idx].min && ans > seg_tree[end_idx].idx)) {
                mini = seg_tree[end_idx].min;
                ans = seg_tree[end_idx].idx;
            }
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

    cin >> N;

    int height = ceil(log2(N));
    int size = (1 << (height+1));
    int start_index = size/2;
    seg_tree.resize(size+1);

    for (int i=start_index; i<start_index+N; i++){
        long long val;
        cin >> val;
        seg_tree[i] = {val,i};
    }

    for (int i = start_index + N; i < size; i++) {
        seg_tree[i] = {LLONG_MAX, i};
    }

    init(size);

    // for(int i=1;i<size;i++){
    //     cout << "node: " << seg_tree[i].min << " " << seg_tree[i].idx << " ";
    // }
    // cout << endl;

    cin >> M;

    for(int i=0;i<M;i++){
        int a,b,c;
        cin >> a >> b >> c;

        switch(a){
            case 1:
                update(b+start_index-1,c);
                // for(int i=1;i<size;i++){
                //     cout << "node: " << seg_tree[i].idx <<  " " << seg_tree[i].min << " ";
                // }
                // cout << endl;
                break;
            case 2:
                cout << find(b+start_index-1,c+start_index-1)-start_index+1 << '\n';
                break;
        }
    }
}