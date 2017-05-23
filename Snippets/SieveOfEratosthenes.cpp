// Sieve of Eratosthenes
// Time complexity: O(N×log(N))
#define N 100000
bitset<N+1> p;
void seive(){
	p.set();
	for(int i=2;i*i<=N;i++){
		if(p[i]){
			for(int j=i;j<=N;j+=i){
				p.reset(j);
			}
		}
	}
}