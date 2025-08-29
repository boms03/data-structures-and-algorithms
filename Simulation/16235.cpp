#include<iostream>
#include<vector>
#include<algorithm>
#define MAX_N 11
#define MAX_M 101
using namespace std;

struct tree{
    int age;
    bool dead;
    bool operator<(const tree& other) const {
        return age < other.age;
    }
};

int n,m,k;
int A[MAX_N][MAX_N];
int map[MAX_N][MAX_N];
vector<tree> umap[MAX_N][MAX_N];
int dx[]={-1,0,1,-1,1,-1,0,1};
int dy[]={-1,-1,-1,0,0,1,1,1};

void spring(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if (umap[i][j].size() == 0) continue;
            sort(umap[i][j].begin(),umap[i][j].end());
            int die_tree_energy = 0;
            auto iter = umap[i][j].begin();
            while(iter != umap[i][j].end()){
                if(iter->age > map[i][j]){
                    die_tree_energy+=iter->age / 2; 
                    iter = umap[i][j].erase(iter);
                }
                else {
                    map[i][j] -= iter->age;
                    iter->age++;
                    iter++; 
                }
            }
            map[i][j]+=die_tree_energy;
        }
    }
}

void spring_and_summer(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if (umap[i][j].size() == 0) continue;
            
            int die_tree_energy = 0;
            vector<tree> temp;
            
            sort(umap[i][j].begin(),umap[i][j].end());
            for(auto& tree: umap[i][j]){
                if(tree.age > map[i][j]){
                    die_tree_energy += tree.age / 2; 
                } else {
                    map[i][j] -= tree.age;
                    tree.age++;
                    temp.push_back(tree); 
                }
            }
            
            umap[i][j] = temp; 
            map[i][j] += die_tree_energy;
        }
    }
}

void fall(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(auto& tree: umap[i][j]){
                if(tree.age%5==0){
                    for(int k=0;k<8;k++){
                        int nx = j+dx[k];
                        int ny = i+dy[k];
                        if(nx<0 || nx >=n || ny <0 || ny >=n) continue;
                        umap[ny][nx].push_back({1,false});
                    }
                }
            }
        }
    }
}

void winter(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            map[i][j] += A[i][j];
        }
    }
}

int main(){
    cin >> n >> m >> k;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> A[i][j];
            map[i][j]=5;
        }
    }

    for(int i=0;i<m;i++){
        int x,y,z;
        cin >> x >> y >> z;
        umap[x-1][y-1].push_back({z,false});
    }

    while(k--){
        spring();
        fall();
        winter();
    }

    int cnt = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(auto& tree: umap[i][j]){
                if(!tree.dead) cnt++;
            }
        }
    }
    cout << cnt;

}