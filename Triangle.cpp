#include "Triangle.h"
#define EPSILON 0.000001

Triangle::Triangle(Vector p1, Vector p2, Vector p3, Vector pos){
	_p1 = p1;
	_p2 = p2;
	_p3 = p3;
	_pos = pos;
	_color.setColor(0.5,0.5,0.2);
	_diffuse = 1.0;
	_u = _p2 - _p1;
	_v = _p3 - _p1;
	_normal = Vector::cross(_u, _v);
	_normal.normalize();
	computeArea();
}

//private function tracks triangle's area
void Triangle::computeArea() {
	float base = Vector::getDist(_p1,_p2);
	float height = Vector::cross((_p2 - _p1),(_p1-_p3)).getNorm()/(_p2 - _p1).getNorm();
	_area = (base*height)/2;
}

Triangle::~Triangle(){
	
}

void Triangle::setColor(float r, float g, float b) {
	_color.setColor(r,g,b);
}

void Triangle::setPos(float x, float y, float z) {
	_pos.setPoint(x,y,z);
}

void Triangle::setPos(Vector pos){
	_pos = pos;
}

//return a hit object with intersection point and surface normal if ray intersects
Hit Triangle::intersectsRay(Ray ray) {
	float inv_det, u, v;
	Vector tvec, pvec, qvec;
	Hit ip(false);

	pvec = Vector::cross(ray.getDir(),_v);
	inv_det = _u*pvec;
	if (inv_det < EPSILON) {
		return ip; //no intersection; triangle is degenerate
	}
	
	inv_det = 1.0 / inv_det;
	tvec = ray.getPos() - _p1;
	u = (tvec*pvec)*inv_det;
	if ( u < 0.0 || u > 1.0 ) {
		return ip; //no intersection; ray goes away from triangle
	}

	qvec = Vector::cross(tvec,_u);
	v = (ray.getDir()*qvec)*inv_det;
	if ( v < 0.0 || u + v > 1.0 ) {
		return ip; //no intersection
	}

	float t;
	t = (_v*qvec)*inv_det;
	if ( t < 0 ) {
		return ip; //intersects plane, but outside of triangle
	}
	
	ip.setPos(ray.getPos() + (ray.getDir() * t));
	ip.setNormal(_normal);
	// Ensure that the normal is pointing in the right direction
	if (ip.getNormal() * ray.getDir() > 0) {
		ip.setNormal(ip.getNormal()*-1);
	}
	ip.setHit(true);
	return ip;
}

/*
Hit Triangle::intersectsRay(Ray ray) {
	//T.V1 is _p2
	//T.V2 is _p3
	//T.V0 is _p1
    Vector dir, w0, w;  // ray vectors
    float r, a, b; // params to calc ray-plane intersect
	Hit ip(true);
	
    // get triangle edge vectors and plane normal
    if (_normal == Vector(0,0,0)) { // triangle is degenerate
        ip.setHit(false);
        return ip;
    }

    dir = ray.getDir() - ray.getPos(); // ray direction vector
    w0 = ray.getPos() - _p1;
    a = -1*(_normal*w0);
    b = _normal*dir;
    if (fabs(b) < SMALL_NUM) { 
    		ip.setHit(false);
    		return ip;
    }
    
    // get intersection point of ray with triangle plane
    r = a / b;
    if (r < 0.0) { //ray diverges from triangle's plane
        ip.setHit(false); // => no intersect
    		return ip;
    }
    // for a segment, also test if (r > 1.0) => no intersect

	ip.setPos(ray.getPos() + (dir*r)); // intersect point of ray and plane

    // is I inside T?
    float uu, uv, vv, wu, wv, D;
    uu = _u*_u;
    uv = _u*_v;
    vv = _v*_v;
    w = ip.getPos() - _p1;
    wu = w*_u;
    wv = w*_v;
    D = uv * uv - uu * vv;

    // get and test parametric coords
    float s, t;
    s = (uv * wv - vv * wu) / D;
    if (s < 0.0 || s > 1.0) {        // I is outside T
        ip.setHit(false);
        return ip;
    }
    t = (uv * wu - uu * wv) / D;
    if (t < 0.0 || (s + t) > 1.0) {  // I is outside T
        ip.setHit(false);
        return ip;
    }

	ip.setNormal(_normal);
    return ip;                      // I is in T
}
*/
//Returns the point of intersection (ray with triangle)
//returns NULL if no intersection
/*
Hit Triangle::intersectsRay(Ray ray) {
	float ri, s, t;
	Vector pi; //not ratio of circumference to radius, but intersection point
	Vector w;
	Hit ip(false);
	ray.toString();
	
	float denom = _normal*(ray.getDir()-ray.getPos());
	//First test for intersection with the triangle's plane
	//the plane through _p1 with _normal intersects ray if ri >=0
	if (denom == 0) { //if denom == 0, the line is parallel to the plane
		return ip; //no intersection w/ plane
	}
	ri = (_normal*(_p1-ray.getPos()))/denom;
	if (ri < 0 || ri > 1.0) {
		return ip; //no intersection w/ plane
	}
	pi = ray.getPos() + (ray.getDir()-ray.getPos())*ri; //intersection point of ray with plane, is it in the triangle?
	//plane defined parametrically by _p1 + s(_p2-_p1) + t(_p3-_p1) = _p1 + su + tv = P(s,t), where s and t are floats
	// w == su + tv if intersects triangle
	w = pi - _p1;
	denom = ((pow(_u*_v,2))-((_u*_u)*(_v*_v)));
	s = ((_u*_v)*(w*_v)-(_v*_v)*(w*_u))/denom; //avoiding cross products
	t = ((_u*_v)*(w*_u)-(_u*_u)*(w*_v))/denom;
	//pi is in the triangle when s>=0, t>=0, and s+t<=1
	if (s >= 0 && t >= 0 && (s+t) <= 1.0) {
		ip.setHit(true); //intersects triangle
		ip.setPos(pi);
		ip.setNormal(_normal);
		return ip;
	}
	else {
		return ip; //no intersection triangle
	}
}
*/

#ifdef __TEST_Triangle__ //unit testing
#include <cassert>

int main() {
	Ray myRay;
	Vector v1(-1,0,1);
	Vector v2(1,0,1);
	Vector v3(0,1,1);
	Vector pos(0,0,1);
	Triangle tri(v1,v2,v3,pos);
	Hit myHit(false);
	
	myRay.setPos(0,0,0);
	myRay.setDir(0.5,0,1);
	myHit = tri.intersectsRay(myRay);
	assert(myHit);
	myRay.setDir(1,1,1);
	myHit = tri.intersectsRay(myRay);
	assert(!myHit);
	v1.setPoint(-0.1,0,0.1);
	v2.setPoint(0.1,0,0.1);
	v3.setPoint(0,0.1,0.1);
	pos.setPoint(0,0,0.1);
	Triangle tri2(v1,v2,v3,pos);
	myRay.setDir(0.1,0.1,0);
	myHit = tri.intersectsRay(myRay);
	assert(!myHit);
	v1.setPoint(-1,0,1);
	v2.setPoint(1,0,1);
	v3.setPoint(0,1,1);
	Triangle tri3(v1,v2,v3,pos);
	assert(tri3.getArea() == 1.0);
	
	std::cout << "Triangle Tests passed" << std::endl;
	return 0;
}

#endif
