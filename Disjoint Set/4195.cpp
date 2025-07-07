// Online C++ compiler to run C++ program online
#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
using namespace std;

unordered_map<string,int>name_hash;
int parent[200001];
int network[200001];
int t,f;
int cnt;

void init(){
    name_hash.clear();
    cnt=0;
    for(int i=0;i<200000;i++){
        parent[i]=i;
        network[i]=1;
    }
}

int find_parent(int a){
    if(parent[a]==a) return a;
    return parent[a] = find_parent(parent[a]);
}

void join(int a, int b){
    int parent_a = find_parent(a);
    int parent_b = find_parent(b);
    
    if(parent_a == parent_b){
        cout << network[parent_a] << '\n';
        return;
    }
    
    parent[parent_b] = parent_a;
    network[parent_a] += network[parent_b];
    cout << network[parent_a] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> t;
    while(t--){
        cin >> f;
        init();
        
        for(int i=0;i<f;i++){
            string a,b;
            int c,d;
            cin >> a >> b;
            if(name_hash.find(a)==name_hash.end()){
                name_hash[a] = cnt;
                c = cnt++;
            } else{
                c = name_hash[a];
            }
            if(name_hash.find(b)==name_hash.end()){
                name_hash[b] = cnt;
                d = cnt++;
            } else {
                d = name_hash[b];
            }
            join(c,d);
        }
    }

    return 0;
}
