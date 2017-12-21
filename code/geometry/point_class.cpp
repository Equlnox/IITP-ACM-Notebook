struct Point{
    ll x,y;
    Point(){x=0;y=0;}
    Point(ll x,ll y):x(x),y(y){

    }
    ll operator*(Point b){
        return x*b.y-y*b.x;
    }
    Point operator-(Point b){
        return Point(x-b.x,y-b.y);
    }
    Point operator+(Point b){
        return Point(x+b.x,y+b.y);
    }
};
