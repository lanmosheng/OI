#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = INT_MAX;
const ll Linf = LLONG_MAX;
#define endl '\n'
const int N = 3e6+10;
int ch[N][70];
int tot=0;
int cnt[N];
int getnum(char s){
    if(s>='a'&&s<='z')
        return s-'a';
    else if(s>='A'&&s<='Z')
        return s-'A'+26;
    else 
        return s-'0'+52;
}
void insert(string s){
    int p=0;
    for(int i=0;i<s.size();i++){
        int c=getnum(s[i]);
        if(!ch[p][c]){
            ch[p][c]=++tot;
        }
        p=ch[p][c];
        cnt[p]++;
    }
}
int find(string s){
    int p=0;
    for(int i=0;i<s.size();i++){
        int c=getnum(s[i]);
        if(!ch[p][c]) return 0;
        p=ch[p][c];
    }
    return cnt[p];
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        for(int i=0;i<=tot;i++){
            for(int j=0;j<70;j++){
                ch[i][j]=0;
            }
            cnt[i]=0;
        }
        tot=0;
        int n,q;
        cin>>n>>q;
        string s;
        for(int i=1;i<=n;i++){
            cin>>s;
            insert(s);
        }
        for(int i=1;i<=q;i++){
            cin>>s;
            cout<<find(s)<<endl;
        }
    }   
    return 0;
}
