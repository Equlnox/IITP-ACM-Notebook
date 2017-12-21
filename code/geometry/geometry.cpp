const int eps = 0;

class Point
{
public:
	int x, y;
	Point(int x, int y) : x(x), y(y){}
	Point(){}
	Point operator + (Point t){
		return Point(x + t.x, y + t.y);
	}
	Point operator - (Point t){
		return Point(x - t.x, y - t.y); 
	}
	bool operator == (Point t){
		return (abs(t.x - x) < eps && abs(t.y - y) < eps);
	}

	/* returns the dot product a.b*/
	int operator * (Point b){
		return (x * b.x) + (y * b.y);		
	}

	/* returns cross Product A cross B */
	int operator ^ (Point b){
		return ((x) * (b.y) - (b.x) * (y));
	}

	friend istream & operator >> (istream & in, Point & t);
	int cross(Point a, Point b);
	bool ccw(Point a, Point b, Point c);
	LD distance(Point a, Point b);
};

istream & operator >> (istream &in, Point & t){
	cin >> t.x >> t.y;
	return in;
}

/*Returns the orientation of Point C wrt line from B to A
 * It returns :-
 * -1 if C lies to left
 * +1 if C lies to the right of the line
 * 0 if C lies on the line
 */

int ccw(Point a, Point b, Point c){
	int ans = (a - c) ^ (b - c);
	return ans < 0 ? -1 : ans > 0;
}

LL sqr(int a){
	return a * 1LL * a;
}

LD distance(Point a, Point b){
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

/* 0 means outside, 1 means looselyinside the polygon(include on the edges of the polygon)*/

/* To change it strictly inside
 * change the type of this function to int
 * 0 means on the edge / point
 * +1 means strictly inside
 * -1 means strictly outside
 * winding number = 0 means outside
 * winding number != 0 means inside
 */

bool is_inside(auto & p, auto & pt){
	 int n = (int)p.size();
	 int cnt = 0;

	 for(int i = 0; i < n; i++){
	 	if(p[i] == pt) return true;
	 	int j = (i + 1) % n;
	 	if(p[i].y == pt.y && p[j].y == pt.y){
	 		if(pt.x >= min(p[i].x, p[j].x) && pt.x <= max(p[i].x, p[j].x))
	 			return true;
	 	}else{
	 		bool below = p[i].y < pt.y;
	 		if(below != (p[j].y < pt.y)){
	 			auto orientation = ccw(p[i], p[j], pt);
	 			if(!orientation) return true;
	 			if(below == (orientation > 0)) cnt += below ? 1 : -1;
	 		}
	 	}
	 }

	 return (cnt != 0);
}