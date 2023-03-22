#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+10;
struct node{
	int l,r,sum;
}tr[N*40];
int cnt,root[N];
int a[N];
vector<int> v;
int getid(int x){
	return lower_bound(v.begin(),v.end(),x)-v.begin()+1;
}
void insert(int l,int r,int pre,int &now,int v){//插入p，并新建版本
	tr[++cnt]=tr[pre];
	now=cnt;
	tr[now].sum++;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(v<=mid) insert(l,mid,tr[pre].l,tr[now].l,v);
	else insert(mid+1,r,tr[pre].r,tr[now].r,v);
	//不需更新，上面已经++
}
int query(int l,int r,int L,int R,int k){
	if(l==r) return l;
	int mid=(l+r)>>1;
	int tmp=tr[tr[R].l].sum-tr[tr[L].l].sum;
	if(k<=tmp)	return query(l,mid,tr[L].l,tr[R].l,k);
	else return query(mid+1,r,tr[L].r,tr[R].r,k-tmp);
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",a+i);
		v.push_back(a[i]);
	}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	for(int i=1;i<=n;i++){
		insert(1,n,root[i-1],root[i],getid(a[i]));
	}
	while(m--){
		int l,r,k;
		scanf("%d%d%d",&l,&r,&k);
		printf("%d\n",v[query(1,n,root[l-1],root[r],k)-1]);
	}
	return 0;
}
