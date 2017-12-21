
const int MOD = (int)1e9 + 7;

int add(){ return 0; }

template<typename... T> int add(int a, T... arg){
	int b = add(arg...);
	return (a + b >= MOD ? a + b - MOD : a + b);
}

int multiply(){return 1;}

template<typename... Args> int multiply(int a, Args... arg){
	return (a * 1LL * multiply(arg...)) % MOD;
}