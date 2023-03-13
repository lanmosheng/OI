#include<bits/stdc++.h>
#define int __int128
using namespace std;
#define lowbit(x) ((x)&(-x))
const int N = 1e5+10;
int t1[N];
int t2[N];
int n,m;

int query(int x,int t[]){
	int ret=0;
	for(;x;x-=lowbit(x))
		ret+=t[x];
	return ret;
}

void update(int x,int v,int t[]){
	for(;x<=n;x+=lowbit(x))
		t[x]+=v;
}
__int128 read()
{
	//直接在函数里面实现读字符串操作更简洁
	__int128 res=0;//初始结果赋值0
	char scan[1005];
	scanf("%s",scan);
	for(int i=0;i<strlen(scan);i++)
		res*=10,res+=scan[i]-'0';//实现进位
	return res;//返回__int128类型
}
void print(__int128 num)
{//递归调用，实现从高位向低位输出
	if(num>9) 
		print(num/10);
	putchar(num%10+'0');
}
signed main(){
	n=read();
	m=read();
	int pre=0,x;
	for(int i=1;i<=n;i++){
		x=read();
		update(i,x-pre,t1);
		update(i,i*(x-pre),t2);
		pre=x;
	}
	while(m--){
		int op,x,y,k;
		op=read();
		switch(op){
			case 1:
				x=read();
				y=read();
				k=read();
				update(x,k,t1);
				update(y+1,-k,t1);
				update(x,x*k,t2);
				update(y+1,-(y+1)*k,t2);
				break;
			case 2:
				x=read();
				y=read();
				x--;
				int ans=(query(y,t1)*(y+1)-query(y,t2)) - (query(x,t1)*(x+1)-query(x,t2));
				print(ans);
				puts("");
				break;
		}
	}
	return 0;
}
//设差分数组为b[]，则经过推导可知sum[x]=(x)Sum(b[i])+Sum(b[i]*i) 其中Sum从1跑到x 所以需要维护b[i]与i*b[i]的前缀和
