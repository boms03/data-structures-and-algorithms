#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int N,M,K;
vector<long long>seg_tree;

void init(int size){
    for(int i=size-1;i>1;i--){
        seg_tree[i/2] = (seg_tree[i/2]*seg_tree[i])% 1000000007;
    }
}

long long product(int start_idx, int end_idx){
    long long total_product = 1;
    while (start_idx<=end_idx){
        if(start_idx & 1) total_product = (total_product * seg_tree[start_idx++]) % 1000000007;
        if(!(end_idx & 1)) total_product = (total_product * seg_tree[end_idx--]) % 1000000007;
        start_idx= (start_idx)/2;
        end_idx= (end_idx)/2;
    }
    return total_product;
}

void update(int update_idx, long long update_val){
    seg_tree[update_idx] = update_val;
    update_idx /= 2;
    while (update_idx > 0){
        seg_tree[update_idx] = (seg_tree[update_idx*2]*seg_tree[update_idx*2+1])% 1000000007;
        update_idx/=2;
    }
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M >> K;

    int height = ceil(log2(N));
    int size = (1 << (height+1));
    int start_index = size/2;
    seg_tree.assign(size+1,1);

    for (int i=start_index; i<start_index+N; i++){
        cin >> seg_tree[i];
    }

    init(size);

    // for(int i=1;i<size;i++){
    //     cout << seg_tree[i] << " ";
    // }
    // cout << endl;
    long long a, b ,c;
    for (int i=0; i< M+K; i++){
        cin >> a >> b >> c;
        int b_index = b+start_index-1;
        switch(a){
            case 1:
                update(b_index,c);
                // for(int i=1;i<size;i++){
                //     cout << seg_tree[i] << " ";
                // }
                // cout << endl;
                break;
            case 2:
                cout << product(b_index,c+start_index-1) << '\n';
                break;
            default:
                break;
        }
    }
}