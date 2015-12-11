#include "Sphere.h"
#include <iostream>
#include <cassert>

Sphere::Sphere() {
	_radius = 1;
	_diffuse = 1.0;
}

Sphere::Sphere(float rad) {
	_radius = rad;
	_diffuse = 1.0;
}

Sphere::~Sphere() {
	
}

Vector Sphere::getPos() {
	return _pos;
}

float Sphere::getRad() {
	return _radius;
}

Color Sphere::getColor() {
	return _color;
}

void Sphere::setPos(float in_x, float in_y, float in_z) {
	_pos.setPoint(in_x, in_y, in_z);
}

void Sphere::setPos(Vector inputLocation) {
	_pos = inputLocation;
}

void Sphere::setRad(float r) {
	_radius = r;
}

void Sphere::setColor(Color color) {
	_color = color;
}

void Sphere::setColor(float r, float g, float b) {
	_color.setColor(r,g,b);
}

//return the unit surface normal to a sphere at intersection point Ri
Vector Sphere::surfaceNormalAt(Vector Ri) {
	float Sri = 1/_radius;
	Vector SN;
	
	SN.setPoint((Ri.getX()-_pos.getX())*Sri,
			(Ri.getY()-_pos.getY())*Sri,
			(Ri.getZ()-_pos.getZ())*Sri);
	SN.normalize();
	return SN;
}

//return the intersection point of ray with sphere, otherwise return NULL
Hit Sphere::intersectsRay(Ray feelerRay) {
	float a, b, c;
	float root;
	Hit sphereHit(false);
	
	feelerRay.getDir().normalize(); //make ray direction into unit vector
	//calculate a,b,c
	a = pow(feelerRay.getDir().getX(),2) +
		pow(feelerRay.getDir().getY(),2) +
		pow(feelerRay.getDir().getZ(),2);
	b = 2*(feelerRay.getDir().getX()*(feelerRay.getPos().getX() - _pos.getX()) +
		feelerRay.getDir().getY()*(feelerRay.getPos().getY()-_pos.getY()) +
		feelerRay.getDir().getZ()*(feelerRay.getPos().getZ()-_pos.getZ()));
	c = pow(feelerRay.getPos().getX()-_pos.getX(),2) + 
		pow(feelerRay.getPos().getY()-_pos.getY(),2) +
		pow(feelerRay.getPos().getZ()-_pos.getZ(),2) - pow(_radius,2);
	root = solveQuadratic(a,b,c);
	if (root == -1) {
		return sphereHit;
	}
	sphereHit.setPos(getIntersectionPoint(feelerRay, root));
	sphereHit.setNormal(surfaceNormalAt(sphereHit.getPos()));
	sphereHit.setHit(true);
	return sphereHit;
}

//solve a*t^2+b*t+c=0 for t
//assume normalized |Rd| = 1, so a = 1
//return the smallest positive real root if there is an intersection
//otherwise return -1
float Sphere::solveQuadratic(float a, float b, float c) {
	float t1; //first root
	float t2; //second root
	float discrim = pow(b,2)-(4*a*c);
	
	if (discrim < 0.0) { //miss
		return -1;
	}

	t1 = ((-1)*b - sqrt(discrim))/(2*a); //hit
	if (t1 > 0.0) {	
		return t1;
	}
	
	t2 = ((-1)*b + sqrt(discrim))/(2*a); //hit
	return t2;
}

//return the intersection point of a ray with a surface given the real root of the quadratic equation
Vector Sphere::getIntersectionPoint(Ray ray, float root) {
	Vector ip;
	ip = ray.getPos() + (ray.getDir()*root);
	return ip;
}

/*
 * Unit Testing
 */
#ifdef __TEST_Sphere__

int main() {
	Sphere s1;
	Ray myRay;
	Hit myHit(false);
	
	myRay.setPos(0,0,-5);
	myRay.setDir(0,0,1);
	assert(s1.getRad() == 1);
	s1.setRad(2.3);
	myHit = s1.intersectsRay(myRay);
	assert(myHit); // can remove > -1
	myRay.setDir(0,1,0);
	myHit = s1.intersectsRay(myRay);
	assert(!myHit); // can remove == -1
	myRay.setDir(0.1,0.1,1);
	myHit = s1.intersectsRay(myRay);
	assert(myHit);
	myRay.setPos(0,5,0);
	myRay.setDir(0,-1,0);
	myHit = s1.intersectsRay(myRay);
	assert(myHit);
	myRay.setPos(-3,0,0);
	myRay.setDir(1,0.2,0.2);
	myHit = s1.intersectsRay(myRay);
	assert(myHit);
	myRay.setDir(1,9,9);
	myHit = s1.intersectsRay(myRay);
	assert(!myHit);
	myRay.setPos(0,0,-20);
	Vector foo(0.99,0.74,-19);
	Vector bar;
	bar = foo - myRay.getPos();
	myRay.setDir(bar);
	myHit = s1.intersectsRay(myRay);
	assert(!myHit);
	
	std::cout << "Sphere tests successfull" << std::endl;
	return 0;
}

#endif
