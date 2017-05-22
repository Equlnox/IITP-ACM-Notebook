// Uses LargeModuloMultiplication for fast exponentiation
// m can be as big as 10^18
// Time complexity O(log(e))
#define ll long long
#define ld long double
ll mulmod(ll a, ll b, ll m){ 
	ll q = (ll)(((ld)a*(ld)b) / (ld)m); 
	ll r = a*b - q*m; 
	if (r > m)r %= m; 
	if (r < 0)r += m; 
	return r; 
}
ll modex(ll b,ll e,ll m){
	ll r=1;
	b%=m;
	while(e){
		if(e&1)	r=mulmod(r,b,m);
		e>>=1;
		b=mulmod(b,b,m)%m;
	}
	return r;
}