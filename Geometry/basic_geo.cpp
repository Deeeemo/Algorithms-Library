#include<bits/stdc++.h>

using namespace std;

typedef long double ld;
typedef complex<ld> Point;

#define X real()
#define Y imag()

#define F first
#define S second

// Translate <p> about <o>
Point translate(Point p, Point x) { return p + x; }

// Scale <p> w.r.t. <o> by a factor of <factor>
Point scale(Point p, ld factor, Point o = {0, 0}) { return o + (p - o) * factor; }

// Rotate <p> about <o> by <degree> degrees
Point rotate(Point p, ld degree, Point o = {0, 0}) { return o + (p - o) * polar(1.l, degree); }

// Rotate <p> about <o> by 90 degrees
Point rotate90(Point p, Point o = {0, 0}) { return o + Point(-(p-o).imag(), (p-o).real()); }

ld dot(Point u, Point v, Point o = {0, 0}) {
	u -= o;
	v -= o;
	return u.X * v.X + u.Y * v.Y; 
}

ld cross(Point u, Point v, Point o = {0, 0}) {
	u -= o;
	v -= o;
	return u.X * v.Y - u.Y * v.X;
}

bool orthogonal(Point u, Point v) { return dot(u, v) == 0; }

// Return the smaller angle between <u> and <v>
ld angle(Point u, Point v, Point o = {0, 0}) { 
	u -= o;
	v -= o;
	return acos(clamp<ld>(dot(u, v)/ abs(u)/ abs(v), -1, 1)); 
}

ld turnAngle(Point u, Point v, Point o = {0, 0}) {
	if (cross(u, v, o) >= 0)
		return angle(u, v, o);
	return 2*M_PI - angle(u, v, o);
}

// Is <p> in the smaller angle between vectors <u> and <v>?
bool inAngle(Point p, Point u, Point v, Point o = {0, 0}) { 
	if (cross(u, v, o) < 0)
		swap(u, v);
	return 0 <= cross(u, p, o) && 0 <= cross(p, v, o);
}

int half(Point p) {
	assert(p.X || p.Y);
	return p.Y > 0 || (p.Y == 0 && p.X < 0);
}

void polarSort(vector<Point> &points, Point o = {0, 0}) {
	sort(points.begin(), points.end(), [o](Point u, Point v) {
		return make_tuple(half(u - o), 0, dot(u-o, u-o)) < make_tuple(half(v - o), cross(u, v, o), dot(v-o, v-o));
	});
}

struct Line {
	Point v;
	ld c;

	// ========= Constructors ========
	Line(Point v, ld c): v(v), c(c) {}

	Line(ld a, ld b, ld c): v(Point(b, -a)), c(c) {}

	Line(Point p, Point q): v(q - p), c(cross(v, p)) {}
	// ========= Constructors ========


	// ========= Methods =========
	ld side(Point p) { return cross(v, p) - c; }

	ld dist(Point p) { return abs(side(p))/ abs(v); }

	ld distSquared(Point p) { return side(p)*side(p) / dot(v, v); }

	Line perpThrough(Point p) { return {p, p + rotate90(v)}; }

	bool cmpProj(Point p, Point q) { return dot(p, v) < dot(q, v); }

	Line translate(Point p) { return {v, c + cross(v, p)}; }

	Line shiftLeft(ld d) { return {v, c + d * abs(v)}; }

	Point proj(Point p) { return p - rotate90(v) * side(p) / dot(v, v); }

	Point refl(Point p) { return p - 2.L * rotate90(v) * side(p) / dot(v, v); }
};

pair<bool, Point> inter(Line a, Line b) {
	auto crs = cross(a.v, b.v);
	if (crs == 0)
		return {false, NULL};
	return {true, (a.c*b.v - b.c*a.v)/ crs};
}

Line bisector(Line a, Line b, bool interior = true) {
	assert(cross(a.v, b.v) != 0);
	ld sign = interior? 1: -1;
	return {b.v/ abs(b.v) + sign * a.v/ abs(a.v), b.c/ abs(b.v) + sign * a.c/ abs(a.v)};
}

bool inDisk(Point a, Point b, Point p) { return dot(a-p, b-p) <= 0; }

bool onLineSegment(Point a, Point b, Point p) { return inDisk(a, b, p) && cross(p, b, a) == 0; }

int sign(ld x) {
	if (x == 0)
		return 0;
	return x < 0? -1: 1;
}

pair<bool, Point> properSegmentInter(Point a, Point b, Point c, Point d) {
	ld oa = cross(d, a, c),
	   ob = cross(d, b, c),
	   oc = cross(b, c, a),
	   od = cross(b, d, a);

	if (sign(oa) != sign(ob) && sign(oc) != sign(od))
		return {true, (a*ob - b*oa)/ (ob - oa)};
	return {false, NULL};
}

vector<Point> segmentInter(Point a, Point b, Point c, Point d) {
	vector<Point> res;
	auto maybe = properSegmentInter(a, b, c, d);
	if (maybe.F) {
		res.push_back(maybe.S);
		return res;
	}

	if (onLineSegment(a, b, c))
		res.push_back(c);
	if (onLineSegment(a, b, d))
		res.push_back(d);
	if (onLineSegment(c, d, a))
		res.push_back(a);
	if (onLineSegment(c, d, b))
		res.push_back(b);
	return res;
}

ld segPointDistance(Point a, Point b, Point p) {
	if (a != b) {
		Line l(a, b);
		if (l.cmpProj(a, p) && l.cmpProj(p, b))
			return l.dist(p);
	}
	return min(abs(p-a), abs(p-b));
}

ld segSegDistance(Point a, Point b, Point c, Point d) {
	if (properSegmentInter(a, b, c, d).F) return 0;
	
	return min({segPointDistance(a, b, c), segPointDistance(a, b, d), segPointDistance(c, d, a), segPointDistance(c, d, b)});
}

ld triangleArea(Point a, Point b, Point c) { return abs(cross(a, b, c))/ 2.; }

ld polygonArea(vector<Point> vec) {
	ld res = 0;
	for (int i = 0; i < (int)vec.size(); i++)
		res += cross(vec[i], vec[i+1==(int)vec.size()? 0: i+1]);

	return abs(res)/ 2.;
}

// Is the y-coordinate of <q> at least as big as <p>'s?
bool above(Point p, Point q) { return q.Y >= p.Y; }

bool crossesRay(Point a, Point p, Point q) { return (above(p, a) - above(q, a)) * cross(p, q, a) > 0; }

bool inPolygon(vector<Point> vec, Point p, bool strict = true) {
	int num = 0;
	for (int i = 0; i < (int)vec.size(); i++) {
		int nxt = i+1 == (int)vec.size()? 0: i+1;
		if (onLineSegment(vec[i], vec[nxt], p))
			return !strict;

		num += crossesRay(p, vec[i], vec[nxt]);
	}
	return num & 1;
}

struct Angle {
	Point d;
	int t = 0;

	Angle t180() { return {-d, t + half(d)}; }
	Angle t360() { return {d, t+1}; }
};

bool operator < (Angle a, Angle b) {
	return make_tuple(a.t, half(a.d), 0) < make_tuple(b.t, half(b.d), cross(a.d, b.d));
}

Point circumCentre(Point a, Point b, Point c) {
	b -= a;
	c -= a;
	assert(cross(b, c) != 0);
	return a + rotate90(b*dot(c, c) - c*dot(b, b))/ cross(b, c)/ (ld)2;
}

// Returns all the intersections of the circle defined by <o> and <r> with line <l>
vector<Point> circleLine(Point o, ld r, Line l) {
	vector<Point> res;

	double moveSq = r*r - l.distSquared(o);
	if (moveSq >= 0){
		Point p = l.proj(o);
		Point moveDir = l.v * (ld)sqrt(moveSq) / abs(l.v);
		res.push_back(p + moveDir);
		if (moveSq > 0)
			res.push_back(p - moveDir);
	}
	return res;
}

vector<Point> circleCirlce(Point o1, ld r1, Point o2, ld r2) {
	vector<Point> res;

	Point d = o2 - o1;
	ld dSq = dot(d, d);
	if (dSq == 0){
		assert(r1 != r2);
		return res;
	}

	ld pd = (dSq + r1*r1 - r2*r2)/ 2;
	ld hSq = r1*r1 - pd*pd/ dSq;
	if (hSq  >= 0) {
		Point p = o1 + d*pd/ dSq;
		Point hDir = rotate90(d)*sqrt(hSq/ dSq);
		res.push_back(p+hDir);
		if (hSq > 0)
			res.push_back(p-hDir);
	}
	return res;
}

vector<pair<Point, Point>> twoCircleTangents(Point o1, ld r1, Point o2, ld r2, bool inner) {
	vector<pair<Point, Point>> res;

	if (inner) r2 = -r2;
	Point d = o2 - o1;
	ld dr = r1 - r2;
	ld d2 = dot(d, d);
	ld h2 = d2 - dr*dr;
	if (d2 == 0 || h2 < 0) {
		assert(h2 != 0);
		return res;
	}

	vector<ld> signs;
	signs.push_back(1);
	if (h2 > 0)
		signs.push_back(-1);

	for (auto sign: signs) {
		Point v = (d*dr + rotate90(d) * sqrt(h2) * sign)/ d2;
		res.push_back({o1 + v*r1, o2 + v*r2});
	}
	return res;
}

int main() {
	return 0;
}
