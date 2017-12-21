ll fmod(ll x,ll md,ll p){
	V<ll> pre(md);
	pre[0]=1;
	for(ll i=1;i<md;i++){
		if(i%p!=0)
			pre[i]=(pre[i-1]*i)%md;
		else
			pre[i]=pre[i-1];
	}
	ll r=1;
	while(x){
		ll cy=x/md;
		r=(r*modex(pre[md-1],cy,md))%md;
		r=(r*pre[x%md])%md;
		x/=p;
	}
	return r;
}
