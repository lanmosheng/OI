#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5+10;
int tr[N<<2];
int lz[N<<2];
#define lson p<<1
#define rson p<<1|1
int a[N];
void mark(int l,int r,int v,int p){
 lz[p]+=v;
 tr[p]+=v*(r-l+1);
}
void pushdown(int l,int r,int p){
 int mid=(l+r)>>1;
 mark(l,mid,lz[p],lson);
 mark(mid+1,r,lz[p],rson);
 lz[p]=0;
}

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

int query(int l,int r,int x,int y,int p){
 if(x<=l&&y>=r)
  return tr[p];
 int mid=(l+r)>>1;
 int ret=0;
 if(lz[p]) pushdown(l,r,p);
 if(x<=mid) ret+=query(l,mid,x,y,lson);
 if(y>mid) ret+=query(mid+1,r,x,y,rson);
 return ret; 
}

void update(int l,int r,int x,int y,int v,int p){
 if(x<=l&&y>=r){
  mark(l,r,v,p);
  return;
 }
 if(lz[p]) pushdown(l,r,p);
 int mid=(l+r)>>1;
 if(x<=mid) update(l,mid,x,y,v,lson);
 if(y>mid) update(mid+1,r,x,y,v,rson);
 tr[p]=tr[lson]+tr[rson];
}
signed main(){
 int n,m;
 cin>>n>>m;
 for(int i=1;i<=n;i++)
  cin>>a[i];
 build(1,n,1);
 while(m--){
  int op,x,y,k;
  cin>>op;
  switch(op){
   case 1:
    cin >> x >> y >> k;
    update(1,n,x,y,k,1);
    break;
   case 2:
    cin >> x >> y;
    printf("%lld\n",query(1,n,x,y,1));
    break;
  }
 }
 
 return 0;
}
// 有lazy标记的点的tr一定是对的
// 一定先pushdown才能对子区间进行查询和更新的操作
//  否则，在查询时，查询到的tr[son]并非真实值
//  在更新时，回溯时的tr[son]并非真实值，导致tr[p]也不对
