vector<Point> half_hull(vector<Point> &pts,int t){
    vector<Point> hull;
    hull.pb(pts[0]);
    hull.pb(pts[1]);
    for(int i=2;i<n;i++){
        while((int)hull.size()>1){
            Point p1=hull[(int)hull.size()-2];
            Point p2=hull.back();
            if((((p1-pts[i])*(p2-pts[i]))*t)>=0){
                hull.pop_back();
            }
            else
                break;
        }
        hull.pb(pts[i]);
    }
    return move(hull);
}
vector<Point> convex_hull(vector<Point> &pts){
    sort(pts.begin(), pts.end(),[](Point &a,Point &b){
        if(a.x==b.x)
            return a.y<b.y;
        return a.x<b.x;
    });
    vector<Point> uh,lh;
    uh=half_hull(pts,1);
    lh=half_hull(pts,-1);
    lh.pop_back();
    reverse(lh.begin(), lh.end());
    uh.insert(uh.end(),lh.begin(), lh.end());
    return move(uh);
}
