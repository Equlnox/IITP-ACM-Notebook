random_device rd;
mt19937 gen(rd()); // mersenne twister (only for 32 bit unsigned numbers)
uniform_int_distribution<int> dis(1, 10000); // dis(L, R) uniformly generates [L, R] (inclusive)

/* For 64 bit numbers */
mt19937_64 gen2(rd());
uniform_int_distribution<LL> dis2((int)1e9 + 7, (int)1e10);
cout << dis2(gen) << endl << dis2(gen) << endl;
