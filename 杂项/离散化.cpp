//注意，v数组在离散化后不可用，仅为离散化的辅助数组
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+10;
int a[N];
vector<int> v;
inline int getid(int x){
	return lower_bound(v.begin(),v.end(),x)-v.begin()+1;//防止有0，如果用数组可以不加
}
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		v.push_back(a[i]);
	}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());//去重，提高二分查找的效率
	for(int i=1;i<=n;i++){
		a[i]=getid(a[i]);
	}
	return 0;
}
