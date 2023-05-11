#include<bits/stdc++.h>
using namespace std;
#define maxn 100000010
bool v[maxn];
int prime[1000010],cnt=0;
void euler(int n)
{
	for(int i=2;i<=n;i++)
	{
		if(!v[i])
		prime[++cnt]=i;
		for(int j=1;j<=cnt&&i*prime[j]<=n;j++)
		{
			v[i*prime[j]]=1;
			if(i%prime[j]==0)
			break;
		}
	}
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	euler(n);
	while(m--)
	{
		int x;
		scanf("%d",&x);
		printf("%d\n",prime[x]);
	}
	return 0;
}
