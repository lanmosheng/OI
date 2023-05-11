#define MOD 998244353
#define MAXC 10000000
int Inv[MAXC+5];
void GetInv(int n){
    Inv[1]=1;
    for(int i=2;i<=n;i++)
        Inv[i]=(LL)Inv[MOD%i]*(MOD-MOD/i)%MOD;
}
