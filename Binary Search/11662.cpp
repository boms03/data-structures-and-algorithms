#include<iostream>
#include<cmath>
using namespace std;

int ax,ay,bx,by,cx,cy,dx,dy;

double dist(double t){
    double mx = ax*t + bx*(1-t);
    double my = ay*t + by*(1-t);
    double kx = cx*t + dx*(1-t);
    double ky = cy*t + dy*(1-t);
    return sqrt(pow(kx-mx,2)+pow(ky-my,2));
} 

double ts(double l, double r){
    while(abs(l-r)>1e-6){ //[3]
        //[1]
        double l3 = (2*l+r)/3;
        double r3 = (l+r*2)/3;
        //[2]
        if(dist(l3)>dist(r3)) l=l3;
        else r = r3;
    }
    return dist(l);
}

int main(){
    cin >> ax >> ay >> bx >> by >> cx >> cy >> dx >>dy;
    cout.precision(11);
    cout << ts(0.0,1.0) << endl;
}

/*
    Approach:
        Two people walk at constant rate from the start until the end.
        This requires to calculate the common proportion traveled by two people to calculate distances between the two.
        
        Ternary searching can find the minimum point of proportion vs distance difference graph.
        [1]Third point equation is l3= 2*a+b/3 and r3= a+2*b/3 (l,l3,r3,r) 
        [2]If distance difference at l3 is greater than that at r3, l becomes l3 as the minimum point cannot exist at [l,l3].
        [3]Keep narrowing down the range until the approximation error 1e-6

        O(logN base 3)
        
*/