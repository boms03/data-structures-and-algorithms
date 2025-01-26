#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int N,M;
vector<long long>seg_tree;

void init(int size){
    for(int i=size-1;i>1;i--){
        seg_tree[i/2]+=seg_tree[i];
    }
}

long long sum(int start_idx, int end_idx){
    long long selected_sum = 0;
    while (start_idx<=end_idx){
        if(start_idx%2==1) selected_sum+=seg_tree[start_idx++];
        if(end_idx%2==0) selected_sum+=seg_tree[end_idx--];
        start_idx= (start_idx)/2;
        end_idx= (end_idx)/2;
    }
    return selected_sum;
}

void update(int update_idx, long long update_val){
    long long difference = update_val-seg_tree[update_idx];
    while (update_idx > 0){
        seg_tree[update_idx]+=difference;
        update_idx/=2;
    }
}

int convert_idx(int idx, int height){
    return idx + (1<<height) -1;
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

    // for(int i=1;i<size;i++){
    //     cout << seg_tree[i] << " ";
    // }
    // cout << endl;
    long long a, b ,c;
    for (int i=0; i< M; i++){
        cin >> a >> b >> c;
        switch(a){
            case 0:
                int start_bound, end_bound;
                if(b<=c){
                    start_bound = b;
                    end_bound = c;
                } else {
                    start_bound = c;
                    end_bound = b;
                }
                cout << sum(start_bound+start_index-1,end_bound+start_index-1) << '\n';
                break;
            case 1:
                update(b+start_index-1,c);
                // for(int i=1;i<size;i++){
                //     cout << seg_tree[i] << " ";
                // }
                // cout << endl;
                break;
            default:
                break;
        }
    }
}