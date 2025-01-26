#include<iostream>
#include<cmath>
#include<climits>
#include<vector>
using namespace std;

vector<int>seg_tree;
int n;
int tree_size;
int start_index;

void update(int update_index, int difference){
    while(update_index>0){
        seg_tree[update_index] += difference;
        update_index/=2;
    }
}

int query(int query_index, int cnt){
    while(query_index<start_index){
        if(seg_tree[query_index*2]>=cnt){
            query_index = query_index*2;
        } else {
            cnt -= seg_tree[query_index*2];
            query_index = query_index*2+1;
        }
    }
    update(query_index,-1);
    return query_index-start_index+1;
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    int height = ceil(log2(1000000));
    tree_size = 1 << (height+1);
    start_index = tree_size/2;
    seg_tree.resize(tree_size+1);

    for (int i=0;i<n;i++){
        int a, b, c;
        cin >> a >> b;
        switch(a){
            case 1:
                cout << query(1,b) << '\n';
                break;
            case 2:
                cin >> c;
                update(b+start_index-1,c);
                break;
            default:
                break;
        }
    }
}