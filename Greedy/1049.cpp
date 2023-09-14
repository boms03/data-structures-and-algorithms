#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n,m,p,s;
vector<int>six;
vector<int>single;
int main(){
    int m_six = 1e9;
    int m_single = 1e9;
    cin >> n >> m;
    for(int i=0;i<m;i++){
        cin >> p >> s;
        if(p<m_six) m_six=p;
        if(s<m_single) m_single=s;
    }
    p = n/6; // number of sets to buy
    s = n%6; // number of singles to buy

    if(s*m_single>m_six){
        cout << p*m_six+m_six<< '\n';
    } else if(m_single*6 < m_six){
        cout << m_single*n << '\n';
    } else{
        cout << p*m_six+s*m_single << '\n';
    }

    /*
        Approach:
            Minimum cost means picking the cheapest choices as much mas possible.
            So pick the cheapest 6 set price and the cheapest individual price.
            Important parts to consider
            1) 6 times the cheapest individual price can be cheaper than the cheapest 6 set price
            2) when n less than 6, the price of 6 set can be cheaper than n * the price of single.
            3) buy 6 set as much as possible and buy remaining indivudals.
        Time Complexity:
            O(M)
    */
    
}