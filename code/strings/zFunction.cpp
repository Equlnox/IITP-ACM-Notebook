vector<int> z_compute(string &S_) {
  int zn = S_.size();
  vector<int> z((int)S_.size() + 10);
  int l = 0, r = 0;
  z[0] = 0;
  for (int i = 1; i < zn; i++) {
    if (i <= r)
      z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < zn && S_[z[i]] == S_[i + z[i]])
      ++z[i];
    if (i + z[i] - 1 > r)
      l = i, r = i + z[i] - 1;
  }
  return z;
}
