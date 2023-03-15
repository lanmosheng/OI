#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
struct Node{
	int fa,ch[2],val,res;
	bool tag;
}spl[N];
int rt;
#define ls(x) (spl[x].ch[0])
#define rs(x) (spl[x].ch[1])
#define fa(x) (spl[x].fa)
#define ident(x,f) (rs(f)==x)
#define connect(x,f,k) (spl[spl[x].fa=f].ch[k]=x)
#define update(x) spl[x].res=spl[ls(x)].res^spl[rs(x)].res^spl[x].val
#define ntroot(x) (rs(fa(x))==x||ls(fa(x))==x)
#define reverse(x) swap(ls(x),rs(x)),spl[x].tag^=1
void pushdown(int x){
	if(spl[x].tag){
		reverse(ls(x));
		reverse(rs(x));
	}
	spl[x].tag=0;
}
void rotate(int x){
	int f=fa(x),ff=fa(f),k=ident(x,f);
	connect(spl[x].ch[k^1],f,k);
	fa(x)=ff;
	if(ntroot(f)) spl[ff].ch[ident(f,ff)]=x;
	connect(f,x,k^1);
	update(f),update(x);
}
void pushall(int x){
	if(ntroot(x)) pushall(fa(x));
	pushdown(x);
}
void splaying(int x){
	pushall(x);
	while(ntroot(x)){
		int f=fa(x),ff=fa(f);
		if(ntroot(f)) ident(x,f)^ident(f,ff)?rotate(x):rotate(f); 
		rotate(x);
	}
}

void access(int x){
	for(int y=0;x;x=fa(y=x)){
		splaying(x);
		rs(x)=y;
		update(x);
	}
}
void mkroot(int x){
	access(x);
	splaying(x);
	reverse(x);
}
int findroot(int x){
	access(x);
	splaying(x);
	while(ls(x)){
		pushdown(x);
		x=ls(x);
	}
	splaying(x);
	return x;
}
void link(int x,int y){
	mkroot(x);
	if(findroot(y)==x)	return;
	fa(x)=y;//仅仅连了虚边，所以不用update
}
void cut(int x,int y){
	mkroot(x);
	if(findroot(y)!=x||fa(y)!=x||ls(y)) return;
	rs(x)=0;
	fa(y)=0;
	update(x);//在一条splay中断开，需要更新
}
void split(int x,int y){
	mkroot(x);
	access(y);
	splaying(y);
	//此时y一定没有右儿子
}
template<class T>
void read(T &x){
	x=0;
	char ch=getchar();
	int flag=1;
	while(!isdigit(ch)){
		if(ch=='-') flag=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	x*=flag;
}
template<class T>
void write(T x){
	if(!x){
		putchar('0');
		return;
	}else if(x<0){
		putchar('-');
	}
	char buf[20];
	int pos=0;
	while(x){
		buf[pos++]=x%10+48;
		x/=10;
	}
	while(pos>0){
		putchar(buf[--pos]);
	}
}
int main(){
	int n,m;
	read(n);
	read(m);
	for(int i=1;i<=n;i++){
		read(spl[i].val);
		spl[i].res=spl[i].val;
	}
	while(m--){
		int op,x,y;
		read(op);
		read(x);
		read(y);
		if(op==0){
			split(x,y);
			write(spl[y].res);
			putchar('\n');
		}else if(op==1){
			link(x,y);
		}else if(op==2){
			cut(x,y);
		}else{
			split(x,x);
			spl[x].val=y;
			update(x);			
		}
	}
	return 0;
}
