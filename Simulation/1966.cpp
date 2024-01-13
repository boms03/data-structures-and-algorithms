#include<iostream>
#include<deque>
using namespace std;

int main(){
    int t,n,q;
    cin >> t;
    while(t--){
        deque<pair<int,int>>que;
        cin >> n >> q;
        for(int i=0;i<n;i++){
            int a;
            cin >> a;
            que.push_back(make_pair(i,a));
        }

        int order = 0;

        while(!que.empty()){
            int cIndex = que.front().first;
            int cPriority = que.front().second;
            bool skip = false;

            for(int i=1;i<que.size();i++){
                if(que[i].second>cPriority){
                   que.pop_front();
                   que.push_back(make_pair(cIndex,cPriority));
                   skip=true;
                   break;
               }
            }

           if(skip==false){
               int pop = que.front().first;
               que.pop_front();
               order++;
                //cout << pop << endl;
                if(pop==q){
                    cout << order << '\n';
                }
            }
        }
    }
}

/* 
    Approach:
        Iterate the queue everytime to check if there are higher priorities behind the front
    Time Complexity:
        O(N^2)
    Improvement:
        Use priority queue to check if the front has the highest priority.
        O(NlogN)
*/