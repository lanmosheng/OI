#include<bits/stdc++.h>
using namespace std;
#define lowbit(x) ((x)&(-x))
const int N = 5e5+10; 
int tr[N];
int n,m;
void update(int x,int v){
	for(;x<=n;x+=lowbit(x)){
		tr[x]+=v;
	}
}
int query(int x){
	int ret=0;
	for(;x;x-=lowbit(x)){
		ret+=tr[x];
	}
	return ret;
}
int main(){
	cin >> n >> m;
	for(int i=1;i<=n;i++){
		int x;
		cin >> x;
		update(i,x);
	}
	while(m--){
		int op,x,y;
		cin >> op >> x >> y;
		if(op==1){
			update(x,y);
		}
		else{
			printf("%d\n",query(y)-query(x-1));
		}
	}
	return 0;
}
