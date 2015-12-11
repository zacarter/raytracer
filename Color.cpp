#include "Color.h"

Color::Color() {
	_r = 0; _g = 0; _b = 0;
}

Color::Color(float r, float g, float b) {
	_r = r; _g = g; _b = b;
}

Color::~Color() {

}

float Color::getR() {
	return _r;
}

float Color::getG() {
	return _g;
}

float Color::getB() {
	return _b;
}

void Color::setColor(float r, float g, float b) {
	_r = r; _g = g; _b = b;
}

void Color::operator=(const Color& rhs) {
	_r = rhs._r;
	_g = rhs._g;
	_b = rhs._b;
}

Color Color::operator+(const Color& rhs) {
	Color temp(_r+rhs._r,_g+rhs._g,_b+rhs._b);
	return temp;
}

Color Color::operator*(const Color& rhs) {
	Color temp(_r*rhs._r,_g*rhs._g,_b*rhs._b);
	return temp;	
}

Color Color::operator*(const float& rhs) {
	Color temp(_r*rhs,_g*rhs,_b*rhs);
	return temp;
}
