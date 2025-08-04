#include<iostream>
#include<climits>
#include<algorithm>

using namespace std;

const int MAXN = 100005;

struct Node {
    int max_val;
    int min_val;
    
    Node() : max_val(INT_MIN), min_val(INT_MAX) {}
    Node(int val) : max_val(val), min_val(val) {}
};

Node tree[MAXN * 4];
int arr[MAXN];
int n;

Node merge(Node left, Node right) {
    Node result;
    result.max_val = max(left.max_val, right.max_val);
    result.min_val = min(left.min_val, right.min_val);
    return result;
}

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = Node(arr[start]);
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }
}

void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        arr[idx] = val;
        tree[node] = Node(val);
    } else {
        int mid = (start + end) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }
}

Node query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return Node();
    }
    if (l <= start && end <= r) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    Node leftResult = query(2 * node, start, mid, l, r);
    Node rightResult = query(2 * node + 1, mid + 1, end, l, r);
    
    if (leftResult.max_val == INT_MIN) return rightResult;
    if (rightResult.max_val == INT_MIN) return leftResult;
    
    return merge(leftResult, rightResult);
}

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int test_case;
    int T;
    
    freopen("input.txt", "r", stdin);
    cin >> T;
    
    for(test_case = 1; test_case <= T; ++test_case)
    {
        int q;
        cin >> n >> q;
        
        // 배열 입력
        for(int i = 0; i < n; i++){
            cin >> arr[i];
        }
        
        // 세그먼트 트리 구축
        build(1, 0, n - 1);
        
        cout << '#' << test_case << ' ';
        
        // 쿼리 처리
        for(int i = 0; i < q; i++){
            int type;
            cin >> type;
            
            if(type == 0){
                int idx, x;
                cin >> idx >> x;
                update(1, 0, n - 1, idx, x);
            }
            else if(type == 1){
                int l, r;
                cin >> l >> r;
                Node result = query(1, 0, n - 1, l, r - 1);
                cout << result.max_val - result.min_val << ' ';
            }
        }
        cout << '\n';
    }
    
    return 0;
}