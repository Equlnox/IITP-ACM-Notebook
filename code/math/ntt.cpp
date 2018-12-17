const ll mod = 163577857, root = 8*23; // = 998244353
 
 
ll modpow(ll x,ll y)
{
	ll ret=1;
	for (; y; y >>= 1, x = x*x%mod)
	    if (y&1) ret = x*ret%mod;
	return ret;
}

ll modinv(ll a)
{
    return modpow(a,mod-2);
}

// https://arxiv.org/pdf/1708.01873.pdf
void BitReverse(vl& vec,int n) {
    int L = 31 - __builtin_clz(n);
    int rev = 0;
	rep(i,0,n) 
    {
		if (i < rev) swap(vec[i], vec[rev]);
		int tail = i ^ (i + 1), shift = 32 - __builtin_clz(tail);
		rev ^= tail << (L - shift);
	}
}


// For p < 2^30 there is also e . g . (5 << 25, 3) , (7 << 26, 3) ,
// (479 << 21, 3) and (483 << 21, 5) . The last two are > 10^9.
void ntt(vl& x, vl roots) {
    int n = x.size();
    if (n == 1) return;
    BitReverse(x,n);
    
    int L = 31 - __builtin_clz(n);
    int mask = (1<<L)-1;

    for (int s=1; s<=L; ++s){
        int m = 1<<s;
        int dx = n/m;
        for (int k = 0; k<n; k+=m){
            int index = 0;
            for (int j = 0; j<m/2;++j)
            {
                ll t = roots[index]*(x[k+j+m/2]%mod);
                ll u = x[k+j];
                x[k+j] = (u+t);
                x[k+j+m/2] = (u-t);
                index = (index+dx)&mask;
            }
        }

    }
    for (int i=0; i<n; ++i)
        x[i]%=mod;
}

// Remember roots to speed up fft
vl precalced_roots[30][2];

void ntt(vl& x, bool inv = false) {
    int L = sz(x);
    int s = 31 - __builtin_clz(L);

    if (precalced_roots[s][inv].size()==0)
    { 
        ll e = modpow(root, (mod-1) / L);
        if (inv)
            e = modpow(e, mod-2);
        vl roots(L,1);
        rep(i,1,L) 
        {
            roots[i] = roots[i-1] * e % mod;
        }
        precalced_roots[s][inv]=roots;
    }
    ntt(x, precalced_roots[s][inv]);        
}

vl conv(vl a, vl b) {
    int s = sz(a) + sz(b) - 1; if (s <= 0) return {};
    int L = s > 1 ? 32 - __builtin_clz(s - 1) : 0, n = 1 << L;
    if (s <=100 || sz(a)<100 || sz(b)<100) { // ( factor 10 optimization for jaj , j b j = 10) 
        vl c(s);
        rep(i,0,sz(a)) rep(j,0,sz(b))
        {
            c[i+j] = (c[i + j] + a[i] * b[j]) % mod;
        }
        return c;
    }
    a.resize(n); ntt(a);
    b.resize(n); ntt(b);
    
    ll d = modpow(n, mod-2);
    rep(i,0,n) a[i]=a[i]*b[i]%mod*d%mod;//c[i] = a[i] * b[i] % mod * d % mod;
    ntt(a, true); 
    a.resize(s); 
    return a;
}
