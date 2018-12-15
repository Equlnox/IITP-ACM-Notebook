// Segmented Seive
// N=sqrt(b)
// Time complexity: O(N.log(B-A))
#define A 1000000000000LL
#define B 1000000100000LL
bitset<B-A> p;
void seive(){
	p.set();
	for(ll i=2;i*i<=B;i++){
		for(ll j=((A+i-1)/i)*i;j<=B;j+=i){
			p.reset(j-A);
		}
	}
}
