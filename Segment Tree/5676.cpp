#include<iostream>
#include<vector>
#include<cmath>
#include<climits>
using namespace std;

vector<int>seg_tree;
int N,M;


void init(int start_index){
    for(int i=start_index-1;i>=1;i--){
        seg_tree[i] = seg_tree[i*2] * seg_tree[i*2+1];
    }
}

int convert(int val){
    if (val>0){
        return 1;
    } else if(val==0){
        return 0;
    } else {
        return -1;
    }
}

void update(int update_index, int update_val){
    seg_tree[update_index] = convert(update_val);
    update_index/=2;
    while (update_index > 0){
        seg_tree[update_index] = seg_tree[update_index*2] * seg_tree[update_index*2+1];
        update_index/=2;
    }
}

int find_mul(int start_index, int end_index){
    int mul = 1;
    while(start_index<=end_index){
        if(start_index & 1){
            mul *= seg_tree[start_index++];
        }

        if(!(end_index & 1)){
            mul *= seg_tree[end_index--];
        }
        start_index/=2;
        end_index/=2;
    }
    
    return mul;
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    while (cin >> N >> M){
        int height = ceil(log2(N));
        int size = 1 << (height + 1);
        int start_index = size/2;
        seg_tree.resize(size+1);

        for (int i=start_index;i<start_index+N;i++){
            int val;
            cin >> val;
            seg_tree[i] = convert(val);
        }

        init(start_index);

        for (int i=0; i<M; i++){
            char a;
            int b, c, ans;
            cin >> a >> b >> c;
            switch (a)
            {
            case 'C':
                update(b + start_index - 1,c);
                break;
            case 'P':
                ans = find_mul(b + start_index - 1,c + start_index - 1);

                if (ans == 1){
                    cout << '+';
                } else if (ans == 0){
                    cout << '0';
                } else {
                    cout << '-';
                }
                break;

            default:
                break;
            }
        }
        seg_tree.clear();
        cout << '\n';
    }
}