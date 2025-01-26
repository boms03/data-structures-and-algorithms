#include<iostream>
#include<vector>
#include<cmath>
#include<climits>
using namespace std;

vector<int>seg_tree;
int N,M;

void init(int start_index){
    for(int i=start_index-1;i>=1;i--){
        seg_tree[i] = min(seg_tree[i*2], seg_tree[i*2+1]);
    }
}
void update(int update_index, int update_val){
    seg_tree[update_index] = update_val;
    update_index/=2;
    while (update_index > 0){
        seg_tree[update_index] = min(seg_tree[update_index*2], seg_tree[update_index*2+1]);
        update_index/=2;
    }
}

int find_min(int start_index, int end_index){
    int minimum = INT_MAX;
    while(start_index<=end_index){
        if(start_index & 1){
            minimum = min(minimum,seg_tree[start_index++]);
        }

        if(!(end_index & 1)){
            minimum = min(minimum,seg_tree[end_index--]);
        }
        start_index/=2;
        end_index/=2;
    }
    return minimum;
}


int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    int height = ceil(log2(N));
    int size = 1 << (height + 1);
    int start_index = size/2;
    seg_tree.assign(size+1,INT_MAX);
    for (int i=start_index;i<start_index+N;i++){
        cin >> seg_tree[i];
    }
    init(start_index);
    cin >> M;
    for (int i=0; i<M; i++){
        int a,b,c;
        cin >> a >> b >> c;
        switch (a)
        {
        case 1:
            update(b + start_index - 1,c);
            break;
        case 2:
            cout << find_min(b + start_index - 1,c + start_index - 1) << '\n';
            break;
        default:
            break;
        }
    }
}