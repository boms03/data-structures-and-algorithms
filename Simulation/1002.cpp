#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;

double t,xa,ya,ra,xb,yb,rb;

double getDist(){
    return sqrt(pow(abs(xb-xa),2)+pow(abs(yb-ya),2));
}

int main(){
    cin >> t;
    while(t--){
        cin >>xa>>ya>>ra>>xb>>yb>>rb;
        vector<double>lengths;
        double dist = getDist();
        lengths.push_back(dist);
        lengths.push_back(ra);
        lengths.push_back(rb);
        sort(lengths.begin(),lengths.end());
        if(xa==xb && ya==yb && ra==rb) cout << -1 << '\n';
        else if(lengths[2]>lengths[0]+lengths[1]) cout << 0 << '\n';
        else if(lengths[2]==lengths[0]+lengths[1]) cout << 1 << '\n';
        else if(lengths[2]<lengths[0]+lengths[1]) cout << 2 << '\n';
    }
}