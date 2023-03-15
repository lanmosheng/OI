#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct node{
	int ch[2];
	int cnt;
	int val;
	int fa;
	int sz;	
}spl[N];
int rt;
int tot=0;
#define lson(x) spl[x].ch[0]
#define rson(x) spl[x].ch[1]
void inline update(int x){
	spl[x].sz=spl[lson(x)].sz+spl[rson(x)].sz+spl[x].cnt;
}
void connect(int x,int f,int s){
	spl[f].ch[s]=x;
	spl[x].fa=f;
}
#define ident(x,f) (x==spl[f].ch[1])
void rotate(int x){
	int f=spl[x].fa,ff=spl[f].fa,k=ident(x,f);
	connect(spl[x].ch[k^1],f,k);
	connect(x,ff,ident(f,ff));
	connect(f,x,k^1);
	update(f),update(x);
}
void splay(int x,int top){
	if(!top) rt=x;
	while(spl[x].fa!=top){
		int f=spl[x].fa,ff=spl[f].fa;
		if(ff!=top) ident(x,f)^ident(f,ff)?rotate(x):rotate(f);
		rotate(x);
	}
	//一样就不一样 不一样就一样
}
void newnode(int &now,int f,int v){
	now=++tot;
	spl[now].val=v;
	spl[now].fa=f;
	spl[now].sz=spl[now].cnt=1;
}
void delnode(int x){
	splay(x,0);
	if(spl[x].cnt>1) spl[x].cnt--,spl[x].sz--;
	else if(rson(x)){
		int p=rson(x);
		while(lson(p)) p=lson(p);
		splay(p,x);
		connect(lson(x),p,0);
		rt=p;
		spl[p].fa=0;
		update(p);
	}
	else rt=lson(x),spl[rt].fa=0;
}
void ins(int v,int &now=rt,int f=0){
	if(!now) newnode(now,f,v),splay(now,0);
	else if(v<spl[now].val) ins(v,lson(now),now);
	else if(v>spl[now].val) ins(v,rson(now),now);
	else spl[now].cnt++,splay(now,0);
}
void del(int v,int now=rt){
	if(v==spl[now].val) delnode(now);
	else if(v<spl[now].val) del(v,lson(now));
	else del(v,rson(now)); 
}
int getrank(int v){
	int now=rt,rank=1;
	while(now){
		if(spl[now].val==v){
			rank+=spl[lson(now)].sz;
			splay(now,0);
			break;
		}
		else if(v<spl[now].val)
			now=lson(now);
		else{
			rank+=spl[lson(now)].sz+spl[now].cnt;
			now=rson(now);
		}
	}
	return rank;
}
int getnum(int rank){
	int now=rt;
	while(now){
		int lsz=spl[lson(now)].sz;
		if(lsz+1<=rank&&rank<=lsz+spl[now].cnt){
			splay(now,0);
			break;
		}else if(lsz>=rank){
			now=lson(now);
		}else{
			rank-=lsz+spl[now].cnt;
			now=rson(now);
		}
	}
	return spl[now].val;
}
template<class T>
inline void read(T &x){
	int flag=1;
	x=0;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-') flag=-1;
		c=getchar();
	}
	while(isdigit(c)){
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	x*=flag;
}
template<class T>
inline void write(T x){
	if(x==0){
		putchar('0');
		return;
	}
	if(x<0){
		putchar('-');
		x=-x;
	}
	char buf[20];
	int pos=0;
	while(x){
		buf[pos++]=x%10+'0';
		x/=10;
	}
	while(pos>0){
		putchar(buf[--pos]);
	}
}
int main(){
	int n;
	read(n);
	while(n--){
		int op,x;
		read(op);
		read(x);
		if(op==1){
			ins(x);
		}else if(op==2){
			del(x);
		}else if(op==3){
			write(getrank(x));
			putchar('\n');
		}else if(op==4){
			write(getnum(x));
			putchar('\n');
		}else if(op==5){
			write(getnum(getrank(x)-1));
			putchar('\n');
		}else{
			write(getnum(getrank(x+1)));
			putchar('\n');
		}
	}
	return 0;
}
