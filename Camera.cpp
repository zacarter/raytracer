#include "Camera.h"
#include <iostream>
#include <cassert>

//Constructors

Camera::Camera() {
	_pos.setPoint(0,0,0);
	_lookAt.setPoint(0,0,1);
	_up.setPoint(0,1,0);
	_nearPlane = new ImagePlane(_pos, _lookAt, _up, 45.0, 640, 480);
}

Camera::Camera(float x, float y, float z) {
	_pos.setPoint(x,y,z);
	_lookAt.setPoint(0,0,1);
	_up.setPoint(0,1,0);
	_nearPlane = new ImagePlane(_pos, _lookAt, _up, 45.0, 640, 480);			
}

Camera::Camera(float hfov, int pixw, int pixh) {
	_pos.setPoint(0,0,0);
	_lookAt.setPoint(0,0,1);
	_up.setPoint(0,1,0);
	_nearPlane = new ImagePlane(_pos, _lookAt, _up, hfov, pixw, pixh);
}

Camera::~Camera() {
	delete _nearPlane;
}

//Accessors

Vector Camera::getPos() {
	Vector tempLocation;
	tempLocation = _pos;
	return tempLocation;
}

Vector Camera::getLookAt() {
	Vector tempLookAt = _lookAt;
	return tempLookAt;
}

Vector Camera::getUp() {
	return _up;
}

//Mutators

void Camera::setPos(float x, float y, float z) {
	_pos.setPoint(x,y,z);
	_nearPlane->setOrigin(_pos);
}

void Camera::setLookAt(float x, float y, float z) {
	_lookAt.setPoint(x,y,z);
	_nearPlane->setNormal(_lookAt);
}

void Camera::setUp(float x, float y, float z) {
	_up.setPoint(x,y,z);
	_nearPlane->setUpV(_up);
}

void Camera::setPos(Vector inputLocation) {
	_pos = inputLocation;
	_nearPlane->setOrigin(_pos);
}

void Camera::setLookAt(Vector in_LookAt) {
	_lookAt = in_LookAt;
	_nearPlane->setNormal(_lookAt);
}

void Camera::setUp(Vector input_up) {
	_up = input_up;
	_nearPlane->setUpV(_up);
}

/* Compile with -D switch to run unit tests.
 *      Example : g++ -D __TEST_Camera__ -o TestCamera Camera.cpp
 */
#ifdef __TEST_Camera__ //unit testing

int main() {
	std::cout << "test 1" << std::endl;
	Camera myCam(45.0, 640, 480);
	std::cout << "test 2" << std::endl;
	Vector myVect;
	std::cout << "test 3" << std::endl;
	assert(myCam.getPos().getX() == 0);
	assert(myCam.getUp().getY() == 1);
	assert(myCam.getLookAt().getX() == 0);
	myCam.setPos(7,6,5);
	myCam.setUp(1,1,1);
	myVect.setPoint(5,6,7);
	myCam.setLookAt(myVect);
	assert(myCam.getPos().getZ() == 5);
	assert(myCam.getUp().getX() == 1);
	assert(myCam.getLookAt().getY() == 6);
	
	std::cout << "Camera Test Successfull" << std::endl;
	return 0;
}

#endif
