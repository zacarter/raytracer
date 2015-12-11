#include "Hit.h"
#include <iostream>

Hit::Hit(bool hit){
	_pos.setPoint(0,0,0);
	_normal.setPoint(0,0,0);
	_hit = hit;
}

Hit::~Hit(){
	
}

Hit::operator bool() {
	return _hit;
}

void Hit::operator=(const Hit& rhs) {
	_normal = rhs._normal;
	_pos = rhs._pos;
	_hit = rhs._hit;
}

Vector Hit::getPos(){
	return _pos;
}

Vector Hit::getNormal(){
	return _normal;
}

void Hit::setHit(bool hit) {
	_hit = hit;
}

void Hit::setPos(Vector pos){
	_pos = pos;
}

void Hit::setNormal(Vector normal){
	_normal = normal;
}

void Hit::toString() {
	_pos.toString();
	_normal.toString();
	std::cout << "_hit is: " << _hit << std::endl;
} 
