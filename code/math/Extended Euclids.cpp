#include <bits/stdc++.h> 

using namespace std;
using LL = long long;

template<typename T> T gcd(T a , T b){return (a ? gcd(b % a , a): b);} //supposing a is small and b is large.
template<typename T> pair<T,T> extend_euclid(T a, T b){ //supposing a is small and b is large.
	pair<T,T> a_one = {1, 0} , b_one = {0 , 1}; 
	// b_one is just the second last step's coefficient, a_one is the last step's coefficient
	if(!b)return a_one;
	while(a){
		/* We first start from writing 
		b = 0(a) + 1(b), for which it's b_one
		a = 1(a) + 0(b), for which it's a_one
		b = b % a + (b / a)*a, then
		*/
		T q = b / a; T r = b % a;
		T dx = b_one.first - q*a_one.first; 
		T dy = b_one.second - q*a_one.second; 
		b = a; a = r;
		b_one = a_one; 
		a_one = {dx , dy}; 
	}
	return b_one;   
}

int main(){
	LL a, m; cin >> a >> m;
	auto ans = extend_euclid(a, m); 
	LL x = (ans.first + m)%m; //Inverse Modulo (m) $ ax=1 mod(m) and gcd(a,m) == 1
	cout << (ans.first + m) % m << endl; 
	return 0; 
}