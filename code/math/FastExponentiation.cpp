// Takes a base 'b', exponent 'e' and modulo 'm'
// m should be less than 3e9
// Complexity O(log(e))
#define ll long long
ll modex(ll b,ll e,ll m){
	ll r=1;
	b%=m;
	while(e){
		if(e&1)	r=(r*b)%m;
		e>>=1;
		b=(b*b)%m;
	}
	return r;
}
