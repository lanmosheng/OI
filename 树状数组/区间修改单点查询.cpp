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
	int pre=0;
	for(int i=1;i<=n;i++){
		int x;
		cin >> x;
		update(i,x-pre);
		pre=x;
	}
	while(m--){
		int op,x,y,k;
		cin >> op;
		if(op==1){
			cin >> x >> y >> k;
			update(x,k);
			update(y+1,-k);
		}
		else{
			cin >> x;
			printf("%d\n",query(x));
		}
	}
	return 0;
}
