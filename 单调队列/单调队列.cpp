#include<bits/stdc++.h>
using namespace std;
using std::cout;
using std::cin;
typedef long long ll;
const int inf = INT_MAX;
const ll Linf= LLONG_MAX;
#define endl '\n'
const int N =  1e6+10;
int a[N];
int hmax[N],hmin[N];
int n,k;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    deque<int> qmin,qmax;
    for(int i=1;i<=n;i++){
        while(!qmin.empty()&&a[i]<a[qmin.front()]) qmin.pop_front();
        qmin.push_front(i);
        while(!qmin.empty()&&i-qmin.back()>=k) qmin.pop_back();

        while(!qmax.empty()&&a[i]>a[qmax.front()]) qmax.pop_front();
        qmax.push_front(i);
        while(!qmax.empty()&&i-qmax.back()>=k) qmax.pop_back();

        hmax[i]=a[qmax.back()];
        hmin[i]=a[qmin.back()]; 
    }
    
    for(int i=k;i<=n;i++){
        cout<<hmin[i]<<" ";
    }
    cout<<endl;
    for(int i=k;i<=n;i++){
        cout<<hmax[i]<<" ";
    }
    return 0;
}
