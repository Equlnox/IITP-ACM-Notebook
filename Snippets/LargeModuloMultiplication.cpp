// Finds (a*b)%m when either can be as big as 10^18
#define ll long long
#define ld long double
ll mulmod(ll a, ll b, ll m){ 
	a%=m;b%=m;
	ll q = (ll)(((ld)a*(ld)b) / (ld)m); 
	ll r = a*b - q*m; 
	if (r > m)r %= m; 
	if (r < 0)r += m; 
	return r; 
}
