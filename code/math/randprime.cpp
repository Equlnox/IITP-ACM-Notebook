V<int> A{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};

bool Miller(long long p){
	if(p < 2){
		return false;
	}
	if(p != 2 && p % 2 == 0){
		return false;
	}
	long long s = p - 1;
	while(s % 2 == 0){
		s /= 2;
	}
	for(auto & a : A){
		long long temp = s;
		long long mod = power(a, temp, p);
		while(temp != p - 1 && mod != 1 && mod != p-1){
			mod = mulmod(mod, mod, p);
			temp *= 2;
		}
		if(mod != p - 1 && temp % 2 == 0){
			return false;
		}
	}
	return true;
}