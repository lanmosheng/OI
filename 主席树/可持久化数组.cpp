#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+10;
struct node{
	int l,r,val;
}tr[N*40];
int cnt,root[N];
int a[N];
void build(int l,int r,int &now){
	now=++cnt;
	if(l==r){
		tr[now].val=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,tr[now].l);
	build(mid+1,r,tr[now].r);
}
void update(int l,int r,int pre,int &now,int pos,int num){
	now=++cnt;
	tr[now]=tr[pre];
	if(l==r){
		tr[now].val=num;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid) update(l,mid,tr[pre].l,tr[now].l,pos,num);
	else update(mid+1,r,tr[pre].r,tr[now].r,pos,num);
}
int query(int l,int r,int now,int pos){
	if(l==r) return tr[now].val;
	int mid=(l+r)>>1;
	if(pos<=mid) return query(l,mid,tr[now].l,pos);
	else return query(mid+1,r,tr[now].r,pos);
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",a+i);
	}
	build(1,n,root[0]);
	for(int i=1;i<=m;i++){
		int v,op;
		scanf("%d%d",&v,&op);
		if(op==1){
			int x,y;
			scanf("%d%d",&x,&y);
			update(1,n,root[v],root[i],x,y);
		}
		else{
			int x;
			scanf("%d",&x);
			printf("%d\n",query(1,n,root[v],x));
			root[i]=root[v];
		}
	}
	return 0;
}
