#include<bits/stdc++.h>
using namespace std;
int f[100001];
int find(int x)
{
	if(f[x]==0)
	return x;
	else
		return f[x]=find(f[x]);
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	int p;
	scanf("%d",&p);
	memset(f,0,sizeof(f));
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		int fx=find(x);
		int fy=find(y);
		f[fx]=fy;	
	}
	
	for(int i=1;i<=p;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		int fa=find(a),fb=find(b);
		if(fa==fb)
		printf("Yes\n");
		else
		printf("No\n");
	}
} 
