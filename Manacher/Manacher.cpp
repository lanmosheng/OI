#include<bits/stdc++.h>
using namespace std;
const int N = 22000005;
namespace manacher{

int n,m,cnt,p[N],mid,mr,ans;
char c[N],s[N];
void manacher(){
    for(int i=2;i<cnt;i++){
        if(i<=mr) p[i]=min(p[mid*2-i],mr-i+1);
        else p[i]=1;
        while(s[i-p[i]]==s[i+p[i]]) p[i]++;
        if(i+p[i]>mr) mr=i+p[i]-1,mid=i;
        ans=max(ans,p[i]);
    }
    cout<<ans-1<<endl;
}
void init(){//转换成s
    cin>>(c+1);
    n=strlen(c+1);
    s[++cnt]='~';
    s[++cnt]='#';
    for(int i=1;i<=n;i++){
        s[++cnt]=c[i];
        s[++cnt]='#';
    }
    s[++cnt]='!';
}

}
int main(){
    manacher::init();
    manacher::manacher();
    return 0;
}
