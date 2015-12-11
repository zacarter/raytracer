#include "Ray.h"

Ray::Ray() {
	_pos.setPoint(0,0,0);
	_dir.setPoint(0,0,0);	
}

Ray::~Ray() {
	
}

void Ray::setPos(float x, float y, float z) {
	_pos.setPoint(x,y,z);
}

void Ray::setDir(float x, float y, float z) {
	_dir.setPoint(x,y,z);
}
	
void Ray::setPos(Vector pos) {
	_pos = pos;
}

void Ray::setDir(Vector dir) {
	_dir = dir;
}

void Ray::toString() {
	std::cout << "Ray Position: ";
	_pos.toString();
	std::cout << "Ray Direction: ";
	_dir.toString();
}
