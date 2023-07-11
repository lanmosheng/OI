#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = INT_MAX;
const ll Linf = LLONG_MAX;
typedef unsigned long long ull;
#define ms(a,v) memset(a,v,sizeof(a))
#define endl '\n'
const int N = 3e6+10;
int a[N];
int f[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    stack<int> s;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        while(!s.empty()&&a[i]>a[s.top()]){
            f[s.top()]=i;
            s.pop();
        }
        s.push(i);
    }
    for(int i=1;i<=n;i++)
    cout<<f[i]<<" ";
    return 0;
}
