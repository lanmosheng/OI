template<class T>
inline void write(T x){
	if(x==0){
		putchar('0');
		return ;
	}
	if(x<0){
		putchar('-');
		x=-x;
	}
	char buf[20];
	int pos=0;
	while (x){
		buf[pos++]=x%10+'0';
		x/=10;
	}
	while(pos>0){
		putchar(buf[--pos]);
	}
	
}	
