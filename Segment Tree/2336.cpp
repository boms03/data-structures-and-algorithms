#include<iostream>
#include<cmath>
#include<climits>
#include<vector>
#include<algorithm>
using namespace std;

struct student{
    int first;
    int second;
    int third;
};

vector<int>seg_tree;
vector<student>students;

bool compare(student a, student b){
    return a.first < b.first; 
}

void update(int node, int s, int e, int u_idx, int u_val){
    if(u_idx < s || u_idx > e) return;
    if(s == e){
        seg_tree[node] = u_val;
        return;
    }
    int mid = (s+e)>>1;
    update(node*2,s,mid,u_idx,u_val);
    update(node*2+1,mid+1,e,u_idx,u_val);
    seg_tree[node] = min(seg_tree[node*2],seg_tree[node*2+1]);
}

int query(int node, int s, int e, int q_s, int q_e){
    if(q_e < s || q_s > e) return INT_MAX;
    if(q_s <=s && e <= q_e) return seg_tree[node];
    int mid = (s+e)>>1;
    return min(query(node*2,s,mid,q_s,q_e), query(node*2+1,mid+1,e,q_s,q_e));
}

int n;
int main(){
    cin >> n;
    int tree_height = ceil(log2(n));
    int tree_size = 1 << ( tree_height + 1);
    seg_tree.assign(tree_size,INT_MAX);
    students.resize(n+1);
    int start_index = tree_size >> 1;

    for(int i=1;i<=n;i++){
        int s;
        cin >> s;
        students[s].first = i;
    }

    for(int i=1;i<=n;i++){
        int s;
        cin >> s;
        students[s].second = i;
    }

    for(int i=1;i<=n;i++){
        int s;
        cin >> s;
        students[s].third = i;
    }

    sort(++students.begin(),students.end(),compare);

    int cnt = 0;
    for(int i=1;i<=n;i++){
        int min = query(1,start_index,tree_size-1,start_index,students[i].second+start_index-2);
        // for(int i=1;i<tree_size;i++) cout << seg_tree[i] << " ";
        // cout << endl;
        // cout << min << " " << students[i].third << endl;
        if(students[i].third < min) cnt++;
        update(1,start_index,tree_size-1,students[i].second+start_index-1,students[i].third);
    }
    cout << cnt << '\n';
}