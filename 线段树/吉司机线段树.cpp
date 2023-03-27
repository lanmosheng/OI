#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 550000;
const int inf = 2e9;
struct node{
    ll sum;
    int maxa,cnt,se,maxb;
    int add1,add2,add3,add4;
}tr[2000005];
int a[N];
#define lson p<<1
#define rson p<<1|1
void pushup(int p){
    tr[p].sum=tr[lson].sum+tr[rson].sum;
    tr[p].maxa=max(tr[lson].maxa,tr[rson].maxa);
    tr[p].maxb=max(tr[lson].maxb,tr[rson].maxb);
    if(tr[lson].maxa==tr[rson].maxa){
        tr[p].se=max(tr[lson].se,tr[rson].se);
        tr[p].cnt=tr[lson].cnt+tr[rson].cnt;
    }
    else if(tr[lson].maxa>tr[rson].maxa){
        tr[p].se=max(tr[lson].se,tr[rson].maxa);
        tr[p].cnt=tr[lson].cnt;
    }
    else{
        tr[p].se=max(tr[rson].se,tr[lson].maxa);
        tr[p].cnt=tr[rson].cnt;
    }
}
void change(int l,int r,int k1,int k2,int k3,int k4,int p){
    tr[p].sum+=1ll*tr[p].cnt*k1+1ll*k2*(r-l+1-tr[p].cnt);
    tr[p].maxb=max(tr[p].maxb,tr[p].maxa+k3);
    tr[p].maxa+=k1;
    if(tr[p].se!=-inf) tr[p].se+=k2;
    tr[p].add3=max(tr[p].add3,tr[p].add1+k3);
    tr[p].add4=max(tr[p].add4,tr[p].add2+k4);
    tr[p].add1+=k1;
    tr[p].add2+=k2;
}
void pushdown(int l,int r,int p){
    int maxn=max(tr[lson].maxa,tr[rson].maxa);
    int mid=(l+r)>>1;
    if(tr[lson].maxa==maxn) change(l,mid,tr[p].add1,tr[p].add2,tr[p].add3,tr[p].add4,lson);
    else change(l,mid,tr[p].add2,tr[p].add2,tr[p].add4,tr[p].add4,lson);
    if(tr[rson].maxa==maxn) change(mid+1,r,tr[p].add1,tr[p].add2,tr[p].add3,tr[p].add4,rson);
    else change(mid+1,r,tr[p].add2,tr[p].add2,tr[p].add4,tr[p].add4,rson);
    tr[p].add1=tr[p].add2=tr[p].add3=tr[p].add4=0;
}   
void build(int l,int r,int p){
    if(l==r){
        tr[p].sum=tr[p].maxa=tr[p].maxb=a[l];
        tr[p].cnt=1,tr[p].se=-inf;
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,lson);
    build(mid+1,r,rson);
    pushup(p);
}
ll query_sum(int l,int r,int x,int y,int p){
    if(x<=l&&y>=r)
        return tr[p].sum;
    int mid=(l+r)>>1;
    ll ret=0;
    pushdown(l,r,p);
    if(x<=mid) ret+=query_sum(l,mid,x,y,lson);
    if(y>mid) ret+=query_sum(mid+1,r,x,y,rson);
    return ret;
}
int query_maxa(int l,int r,int x,int y,int p){
    if(x<=l&&y>=r)  return tr[p].maxa;
    int mid=(l+r)>>1;
    int ret=-inf;
    pushdown(l,r,p);
    if(x<=mid) ret=max(ret,query_maxa(l,mid,x,y,lson));
    if(y>mid) ret=max(ret,query_maxa(mid+1,r,x,y,rson));
    return ret;
}
int query_maxb(int l,int r,int x,int y,int p){
    if(x<=l&&y>=r) return tr[p].maxb;
    int mid=(l+r)>>1;
    int ret=-inf;
    pushdown(l,r,p);
    if(x<=mid) ret=max(ret,query_maxb(l,mid,x,y,lson));
    if(y>mid) ret=max(ret,query_maxb(mid+1,r,x,y,rson));
    return ret;
}
void update_add(int l,int r,int x,int y,int v,int p){
    if(x<=l&&y>=r){
        tr[p].sum+=1ll*(r-l+1)*v;
        tr[p].maxa+=v;
        tr[p].maxb=max(tr[p].maxa,tr[p].maxb);
        if(tr[p].se!=-inf) tr[p].se+=v;
        tr[p].add1+=v,tr[p].add2+=v;
        tr[p].add3=max(tr[p].add3,tr[p].add1);
        tr[p].add4=max(tr[p].add2,tr[p].add4);
        return;
    }
    pushdown(l,r,p);
    int mid=(l+r)>>1;
    if(x<=mid) update_add(l,mid,x,y,v,lson);
    if(y>mid) update_add(mid+1,r,x,y,v,rson);
    pushup(p);
}
void update_min(int l,int r,int x,int y,int v,int p){
    if(v>=tr[p].maxa) return;
    if(x<=l&&y>=r&&tr[p].se<v){
        int k=tr[p].maxa-v;
        tr[p].sum-=1ll*tr[p].cnt*k;
        tr[p].maxa=v;
        tr[p].add1-=k;
        return;
    }
    pushdown(l,r,p);
    int mid=(l+r)>>1;
    if(x<=mid) update_min(l,mid,x,y,v,lson);
    if(y>mid) update_min(mid+1,r,x,y,v,rson);
    pushup(p);
}
void debug(int n){
    for(int i=1;i<=n;i++)
        cout << i <<":"<<query_sum(1,n,i,i,1) << ' ';
    cout << '\n';
    for(int i=1;i<=n;i++)
        cout << i <<":"<<query_maxb(1,n,i,i,1) << ' ';
    cout<<'\n';
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    //freopen("1.in","r",stdin);
    //freopen("1.ans","w",stdout);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    build(1,n,1);
    // for(int i=1;i<=n;i++){
    //     cout << a[i] << " ";
    // }
    // cout << '\n';
    while(m--){
        int op,l,r,k=0;
        cin>>op>>l>>r;
        if(op==1){
            cin>>k;
            update_add(1,n,l,r,k,1);
        }
        else if(op==2){
            cin>>k;
            update_min(1,n,l,r,k,1);
        }
        else if(op==3){
            cout<<query_sum(1,n,l,r,1)<<'\n';
        }
        else if(op==4){
            cout<<query_maxa(1,n,l,r,1)<<'\n';
        }
        else{
            cout<<query_maxb(1,n,l,r,1)<<'\n';    
       }
    //    cout << op << " " << l << " " << r << " " ;
    //    if(k) cout << k;
    //    cout << '\n';
    //     debug(n);
    //     cout << '\n';
    }
    return 0;
}
