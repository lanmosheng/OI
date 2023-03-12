#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
typedef long long ll;
int n,m,mod;
int rt;
int head[N<<1],nxt[N<<1],to[N<<1];
int tot=0;
void add(int x,int y){
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
int son[N],fa[N],top[N],dfn[N],sz[N],tim,dep[N];
int a[N],v[N];

void dfs1(int x,int f){
	fa[x]=f;
	sz[x]=1;
	dep[x]=dep[f]+1;
	for(int i=head[x];i;i=nxt[i]){
		int y=to[i];
		if(y==f) continue;
		dfs1(y,x);
		sz[x]+=sz[y];
		if(sz[son[x]]<sz[y]) son[x]=y;
	}
}

void dfs2(int x,int t){
	dfn[x]=++tim;
	top[x]=t;
	a[tim]=v[x];
	if(!son[x]) return;
	dfs2(son[x],t);
	for(int i=head[x];i;i=nxt[i]){
		int y=to[i];
		if(y==fa[x]||y==son[x])	continue;
		dfs2(y,y);
	}
}

int tr[N<<2],lz[N<<2];
#define lson p<<1
#define rson p<<1|1
void build(int l,int r,int p){
	if(l==r){
		tr[p]=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,lson);
	build(mid+1,r,rson);
	tr[p]=tr[lson]+tr[rson];
}
void mark(int l,int r,int v,int p){
	lz[p]+=(v%mod);
	ll tmp = ((tr[p]%mod)+((r-l+1)%mod)*(v%mod)%mod)%mod;
	tr[p]=tmp;
}
void pushdown(int l,int r,int p){
	int mid=(l+r)>>1;
	mark(l,mid,lz[p],lson);
	mark(mid+1,r,lz[p],rson);
	lz[p]=0;
}
void update(int l,int r,int x,int y,int v,int p){
	if(x<=l&&y>=r){
		mark(l,r,v,p);
		return;
	}
	int mid=(l+r)>>1;
	if(lz[p]) pushdown(l,r,p);
	if(x<=mid) update(l,mid,x,y,v,lson);
	if(y>mid) update(mid+1,r,x,y,v,rson);
	ll tmp = (tr[lson] + tr[rson])%mod;
	tr[p]=tmp;
}
int query(int l,int r,int x,int y,int p){
	if(x<=l&&y>=r){
		return tr[p];
	}
	int mid=(l+r)>>1;
	if(lz[p]) pushdown(l,r,p);
	ll ret=0;
	if(x<=mid) ret+=query(l,mid,x,y,lson);
	if(y>mid) ret+=query(mid+1,r,x,y,rson);
	ret%=mod;
	return ret;
}
void add_line(int x,int y,int z){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		update(1,n,dfn[top[x]],dfn[x],z,1);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	update(1,n,dfn[y],dfn[x],z,1);
}
int query_line(int x,int y){
	ll ret = 0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		ret+=query(1,n,dfn[top[x]],dfn[x],1);
		ret%=mod;
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	ret+=query(1,n,dfn[y],dfn[x],1);
	ret%=mod;
	return ret;
}
void add_tree(int x,int z){
	update(1,n,dfn[x],dfn[x]+sz[x]-1,z,1);
}
int query_tree(int x){
	return query(1,n,dfn[x],dfn[x]+sz[x]-1,1);
}
int main(){
	cin >> n >> m >> rt >> mod;
	for(int i=1;i<=n;i++){
		int x;
		cin >> v[i];
	}
	for(int i=1;i<n;i++){
		int x,y;
		cin >> x >> y;
		add(x,y);
		add(y,x);
	}
	dfs1(rt,0);
	dfs2(rt,rt);
	build(1,n,1);
	while(m--){
		int op,x,y,z;
		cin >> op;
		switch(op){
			case 1:
				cin >> x >> y >> z;
				add_line(x,y,z);
				break;
			case 2:
				cin >> x >> y;
				printf("%d\n",query_line(x,y));
				break;
			case 3:
				cin >> x >> z;
				add_tree(x,z);
				break;
			case 4:
				cin >> x;
				printf("%d\n",query_tree(x));
		}
	}
	return 0;
}
