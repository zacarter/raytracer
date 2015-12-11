#include "Vector.h"
#include <stdlib.h>
#include <iostream>
#include <cassert>

Vector::Vector() {
	_x = 0; _y = 0; _z = 0;
}

Vector::Vector(float in_x, float in_y, float in_z){
	_x = in_x; _y = in_y; _z = in_z;
}

Vector::Vector(const Vector& clone){ //copy constructor
	_x = clone._x; _y = clone._y; _z = clone._z;
}

//operations

void Vector::setPoint(float in_x, float in_y, float in_z){
	_x = in_x; _y = in_y; _z = in_z;

}

//return the unit vector of v
Vector Vector::getNormalized(){
	Vector vp;
	float normFactor = 1/this->getNorm();
	vp.setPoint(_x*normFactor,_y*normFactor,_z*normFactor);
	return vp;
}

//make unit vector
void Vector::normalize() {
	float normFactor = 1/this->getNorm();
	_x = _x*normFactor;
	_y = _y*normFactor;
	_z = _z*normFactor;	
}

//return the norm of the vector v
float Vector::getNorm(){
	return sqrt(pow(_x,2)+pow(_y,2)+pow(_z,2));
}

//overloaded operators

void Vector::operator=(const Vector& rhs) {
	_x = rhs._x;
	_y = rhs._y;
	_z = rhs._z;
}

bool Vector::operator==(const Vector& rhs) {
	return (_x == rhs._x && _y == rhs._y && _z == rhs._z);
}

Vector Vector::operator-(const Vector& rhs) {
	Vector result(_x-rhs._x, _y-rhs._y, _z-rhs._z);
	return result;
}

Vector Vector::operator+(const Vector& rhs) {
	Vector result(_x+rhs._x, _y+rhs._y, _z+rhs._z);
	return result;
} 

float Vector::operator*(const Vector& rhs) { //scalar or dot product
	return (_x*rhs._x + _y*rhs._y + _z*rhs._z);	
}

Vector Vector::operator*(const float rhs) {
	Vector result(_x*rhs, _y*rhs, _z*rhs);
	return result;
}

void Vector::toString() {
	std::cout << _x << "," << _y << "," << _z << std::endl; 
}

Vector Vector::cross(Vector a, Vector b) {
	Vector result((a.getY()*b.getZ())-(b.getY()*a.getZ()),
					(a.getZ()*b.getX())-(b.getZ()*a.getX()),
					(a.getX()*b.getY())-(b.getX()*a.getY()));
	return result;
}

float Vector::getDist(Vector a, Vector b) {
	return sqrt(pow(a._x-b._x,2)+pow(a._y-b._y,2)+pow(a._z-b._z,2));
}	

/* Compile with -D switch to run unit tests.
 *      Example : g++ -D __TEST_Vector__ -o TestVector Vector.cpp
 */
#ifdef __TEST_Vector__ //unit testing
#include <iostream>
#include <assert.h>

int main() {
	Vector v1(5.0,4.0,3.0);
	Vector v2(7,8,9);
	Vector v3 = v1+v2;
	Vector v4 = v1-v2;
	float fred = v1*v2;
	
	assert(v3.getX() == 12);
	assert(v4.getX() == -2);
	assert(fred == 94);
	assert(v1.getX() == 5.0);
	assert(v2.getX() == 7);
	v1 = v2;
	assert(v1==v2);
	Vector v5(v1); //test copy constructor
	assert(v5==v1);
	v5.setPoint(4.4,3.3,2.2);
	assert(!(v5==v1));
	v5 = v1+v3;
	assert(v5==(v1+v3));
	v5 = v5-v1;
	v5.normalize();
	Vector v6;
	v6 = v5.getNormalized();
	v6.setPoint(1,0,0);
	v5.setPoint(0,1,0);
	v4 = Vector::cross(v5,v6);
	fred = v5*v6;
	assert(fred == 0);
	fred = 4;
	Vector v7(1,2,3);
	v7 = v7*fred;
	assert(v7.getX() == 4);
	float bob = v2.getNorm();
	assert(bob >= 0);
	
	//test static functions cross() and getDist()
	Vector a(1,0,0);
	Vector b(-1,0,0);
	Vector c(0,0,0);
	assert(Vector::getDist(a,b) == 2);
	assert(Vector::cross(a,b) == c);
	b.setPoint(0,0,1);
	c.setPoint(0,-1,0);
	assert(Vector::cross(a,b) == c);
	Vector foo(0,0,5);
	foo.normalize();
	assert(foo.getZ() == 1);
	
	
	std::cout << "Vector Test Successfull" << std::endl;
	return 0;
}

#endif
