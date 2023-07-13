#include<bits/stdc++.h>
using namespace std;
#define maxn 1001000
int head[maxn],nxt[maxn],to[maxn],val[maxn],tot=0;
void add(int x,int y,int z)
{
	to[++tot]=y;
	nxt[tot]=head[x];
	val[tot]=z;
	head[x]=tot;
}
bool inq[maxn];
int dis[maxn];
int n;
void spfa(int s)
{
	for(int i=1;i<=n;i++)
	dis[i]=2147483647;
	memset(inq,0,sizeof(inq));
	queue<int> q;
	q.push(s);
	inq[s]=1;
	dis[s]=0;
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		inq[x]=0;
		for(int i=head[x];i;i=nxt[i])
		{
			int y=to[i];
			int z=val[i];
			if(dis[y]>dis[x]+z)
			{
				dis[y]=dis[x]+z;
				if(!inq[y])
				inq[y]=1,q.push(y);
			}
		}
	}
}
int main()
{
	int m,s;
	scanf("%d%d%d",&n,&m,&s);
	int x,y,z;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
	}	
	spfa(s);
	for(int i=1;i<=n;i++)
	printf("%d ",dis[i]);
	return 0;
}
