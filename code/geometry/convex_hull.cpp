/*
 * This implementation passes this https://open.kattis.com/problems/convexhull
 */
long long ccw(Point a, Point b, Point c) { return (b - a) * (c - b); }

vector<Point> convex_hull(vector<Point>& pts)
{
  sort(begin(pts), end(pts), [](const Point& a, const Point& b) {
    return (a.x < b.x || (a.x == b.x && a.y < b.y));
  });

  int n = (int)pts.size();
  if (n == 1)
    return pts;
  vector<Point> ans;
  int sz = (int)ans.size();

  for (int i = 0; i < n; ++i, ++sz) {
    while (sz > 1 && (ccw(ans[sz - 2], ans[sz - 1], pts[i]) <= 0)) {
      sz--;
      ans.pop_back();
    }
    ans.push_back(pts[i]);
  }

  int temp = sz;
  for (int i = n - 2; i >= 0; --i, ++sz) {
    while (sz > temp && (ccw(ans[sz - 2], ans[sz - 1], pts[i]) <= 0)) {
      sz--;
      ans.pop_back();
    }
    ans.push_back(pts[i]);
  }

  while ((int)ans.size() > 1 && ans[0] == ans.back())
    ans.pop_back();
  return ans;
}
