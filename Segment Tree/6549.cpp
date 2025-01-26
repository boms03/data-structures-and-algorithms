#include<iostream>
#include<vector>
#include<cmath>
#include<climits>
using namespace std;
vector<int>seg_tree;
vector<int>arr;
long long ans = 0;
void init(int start_index){
    for(int i=start_index; i>=1; i--){
        if(arr[seg_tree[i*2]]<arr[seg_tree[i*2+1]]) seg_tree[i] = seg_tree[i*2];
        else seg_tree[i] = seg_tree[i*2+1];
    }
}

int find(int start_index, int end_index){
    int minimum = INT_MAX;
    int index = 0;
    while(start_index<=end_index){
        if(start_index & 1){
            if(minimum>arr[seg_tree[start_index]]){
                 minimum = arr[seg_tree[start_index]];
                 index = seg_tree[start_index];
            }
            start_index++;
        } 
        if (!(end_index & 1)){
            if(minimum>arr[seg_tree[end_index]]){
                 minimum = arr[seg_tree[end_index]];
                 index = seg_tree[end_index];
            }
            end_index--;
        }
        start_index/=2;
        end_index/=2;
    }
    return index;
}

void solve(int left, int right){
    if (left > right) return;
    int mid = find(left,right);
    long long m_area = (right-left+1)*(long long)arr[mid];
    ans = max(ans,m_area);
    solve(left,mid-1);
    solve(mid+1,right);
}

int n;
int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    while(cin >> n){
        if (n==0) break;
        int height = ceil(log2(n));
        int size = 1 << (height+1);
        int start_index = size/2;
        seg_tree.resize(size+1);
        arr.assign(size+1, INT_MAX);
        for (int i=start_index; i<start_index+n; i++){
            cin >> arr[i];
            seg_tree[i] = i;
        }
        init(start_index-1);
        // for (int i=1;i<=size;i++){
        //     cout << arr[i] << " ";
        // }
        // cout << endl;
        solve(start_index,start_index+n-1);
        seg_tree.clear();
        cout << ans << '\n';
        ans = 0;
    }
}