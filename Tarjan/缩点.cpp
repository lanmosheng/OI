#include<bits/stdc++.h>
using namespace std;
#define maxn 1000100
int head[maxn],nxt[maxn],to[maxn],v[maxn],tot=0;
int n,m;
struct edge
{
	int l,r;
}e[maxn];
queue<int> q;
int dp[maxn];
void add(int x,int y)
{
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
int low[maxn],dfn[maxn],tim=0;
stack<int> s;
bool ins[maxn];
int scc[maxn];
int V[maxn];
int cnt=0;
void tarjan(int x)
{
	dfn[x]=low[x]=++tim;
	s.push(x);
	ins[x]=1;
	for(int i=head[x];i;i=nxt[i])
	{
		int y=to[i];
		if(!dfn[y])
		{
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(ins[y])
		low[x]=min(low[x],low[y]);
	}
	if(low[x]==dfn[x])
	{
		int cur;
		++cnt;
		do
		{
			cur=s.top();
			s.pop();
			ins[cur]=0;
			scc[cur]=cnt;
			V[cnt]+=v[cur];
		}while(cur!=x);
	}
}
int deg[maxn];
int topo()
{
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=nxt[i])
		{
			int y=to[i];
			dp[y]=max(dp[y],dp[x]+V[y]);
			deg[y]--;
			if(!deg[y])
			q.push(y);
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	ans=max(ans,dp[i]);
	return ans;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	scanf("%d",&v[i]);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		e[i].l=x,e[i].r=y;
	}
	for(int i=1;i<=n;i++)
	{
		if(dfn[i]==0)
		tarjan(i);
	}
	memset(head,0,sizeof(head));
	memset(to,0,sizeof(to));
	memset(nxt,0,sizeof(nxt));
	tot=0;
	for(int i=1;i<=m;i++)
	{
		int x=e[i].l;
		int y=e[i].r;
		if(scc[x]==scc[y])
		continue;
		add(scc[x],scc[y]);
		deg[scc[y]]++;
	}
	for(int i=1;i<=cnt;i++)
	if(!deg[i])q.push(i),dp[i]=V[i];
	int sr=topo();
	printf("%d",sr);	
	return 0;
}
