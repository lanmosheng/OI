#include<bits/stdc++.h>
using namespace std;
int n,k,len1,len2;
const int maxn=1e6+10;
int nxt[maxn];
char s1[maxn];
char s2[maxn];
void get_nxt(){
	int t1=0,t2;
	nxt[0]=t2=-1;
	while(t1<len2){
		if(t2==-1||s2[t1]==s2[t2])
		nxt[++t1]=++t2;
		else t2=nxt[t2];
	}
}
void KMP(){
	int t1=0,t2=0;
	while(t1<len1){
		if(t2==-1||s1[t1]==s2[t2])
		t1++,t2++;
		else t2=nxt[t2];
		if(t2==len2)printf("%d\n",t1-len2+1),t2=nxt[t2];
	}
}
int main(){
	scanf("%s",s1);
	scanf("%s",s2);
	len1=strlen(s1);
	len2=(strlen(s2));
	get_nxt();
	KMP();
	for(int i=1;i<=len2;i++){
		printf("%d ",nxt[i]);
	}
	return 0;
}
