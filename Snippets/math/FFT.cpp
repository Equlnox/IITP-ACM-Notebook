const long double PI=acos(-1.0);
typedef long long ll;
typedef long double ld;
typedef vector<ll> VL;
int bits(int x){
	int r=0;
	while(x){
		r++;
		x>>=1;
	}
	return r;
}
int reverseBits(int x,int b){
	int r=0;
	for(int i=0;i<b;i++){
		r<<=1;
		r|=(x&1);
		x>>=1;
	}
	return r;
}
class Complex{
	public:
	ld r,i;
	Complex(){r=0.0;i=0.0;}
	Complex(ld a,ld b){r=a;i=b;}
};
Complex operator*(Complex a,Complex b){
	return Complex(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r);
}
Complex operator-(Complex a,Complex b){
	return Complex(a.r-b.r,a.i-b.i);
}
Complex operator+(Complex a,Complex b){
	return Complex(a.r+b.r,a.i+b.i);
}
Complex operator/(Complex a,ld b){
	return Complex(a.r/b,a.i/b);
}
Complex EXP(ld theta){
	return Complex(cos(theta),sin(theta));
}

typedef vector<Complex> VC;

void FFT(VC& A,int inv){
	int l=A.size();
	int b=bits(l)-1;
	VC a(A);
	for(int i=0;i<l;i++){
		A[reverseBits(i,b)]=a[i];
	}
	for(int i=1;i<=b;i++){
		int m=(1<<i);
		int n=m>>1;
		Complex wn=EXP((ld)inv*(ld)2.0*PI/(ld)m);
		for(int j=0;j<l;j+=m){
			Complex w(1.0,0.0);
			for(int k=j;k<j+n;k++){
				Complex t1=A[k]+w*A[k+n];
				Complex t2=A[k]-w*A[k+n];
				A[k]=t1;
				A[k+n]=t2;
				w=w*wn;
			}
		}
	}
	if(inv==-1){
		for(auto &i:A){
			i=i/(ld)l;
		}
	}
}

VL Convolution(VL & a,VL & b){
	int tot_size = (int)a.size() + (int)b.size();
	int bit = bits(tot_size);
	int l = 1 << bit;
	VC A, B, C;
	A.reserve(l); B.reserve(l); C.reserve(l);
	for(int i = 0; i < l; i ++) {
		if(i < (int)a.size()) A.pb({(ld)a[i], 0.0});
		else A.pb({0.0, 0.0});
		if(i < (int)b.size()) B.pb({(ld)b[i], 0.0});
		else B.pb({0.0, 0.0});		
	}
	FFT(A, 1);
	FFT(B, 1);
	for(int i = 0; i < l; i ++) {
		C.pb(A[i] * B[i]);
	}
	FFT(C, -1);
	VL c;
	for(auto & i : C) {
		c.pb(round(i.r));
	}
	return c;
}
