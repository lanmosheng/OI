#include<bits/stdc++.h>
using namespace std;
const int M = 5e5 + 1;
const int N = 1e5 + 1;
int head[N],to[M],nxt[M],w[M];
int tot=0;
int dist[N];
bool vis[N];
priority_queue<pair<int,int> >q;
void add(int x,int y,int z){
    to[++tot] = y;
    nxt[tot] = head[x];
    head[x] = tot;
    w[tot] = z;
}
void dij(int s){
    dist[s] = 0;
    q.push(make_pair(0,s));
    while(!q.empty()){
        int x = q.top().second;
        q.pop();
        if(vis[x]) continue;
        vis[x] = 1;
        for(int i = head[x];i;i=nxt[i]){
            int y = to[i];
            if(dist[y] > dist[x] + w[i]){
                dist[y] = dist[x] + w[i];
                q.push(make_pair(-dist[y],y));
            }
        }  
    }
}
int main(){
    int n,m,s;
    scanf("%d%d%d",&n,&m,&s);
    int x,y,z;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&x,&y,&z);
        add(x,y,z);
    }
    memset(dist,0x3f,sizeof(dist));
    dij(s);
    for(int i=1;i<=n;i++){
        printf("%d ",dist[i]);
    }
    return 0;
}
