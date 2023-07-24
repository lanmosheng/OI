#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
int n,m,s,t;
const int N = 5010;
const int M = 5010;
int head[N<<1],nxt[M<<1],to[M<<1],val[M<<1],tot=1;
void add(int x,int y,int z){
    nxt[++tot]=head[x];
    head[x]=tot;
    val[tot]=z;
    to[tot]=y;
}
int dep[N<<1];
int cur[N<<1];
int bfs(){
    memset(dep,0,sizeof(dep));
    queue<int> q;
    q.push(s);
    dep[s]=1;
    while(!q.empty()){
        int x=q.front();
        q.pop();
        for(int i=head[x];i;i=nxt[i]){
            int y = to[i];
            if(!val[i]||dep[y]) continue;
            dep[y]=dep[x]+1;
            q.push(y);
        }
    }
    return dep[t];
}
int dfs(int x,int flow){
    if(x==t) return flow;
    int ret=0;
    for(int i=cur[x];i&&flow;i=nxt[i]){
        cur[x]=i;
        int y=to[i];
        if(val[i]>0&&(dep[y]==dep[x]+1)){
            int tmp=dfs(y,min(flow,val[i]));
            if(tmp==0) dep[y]=0;
            val[i]-=tmp;
            val[i^1]+=tmp;
            ret+=tmp;
            flow-=tmp;
        }
    }
    return ret;
}
signed main(){
    cin>>n>>m>>s>>t;
    for(int i=1;i<=m;i++){
        int x,y,z;
        cin>>x>>y>>z;
        add(x,y,z);
        add(y,x,0);
    }
    int ans=0;
    while(bfs()){
        memcpy(cur,head,sizeof(head));
        ans+=dfs(s,1e18);
    }
    cout<<ans<<endl;
    return 0;
}
