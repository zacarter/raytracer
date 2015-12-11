#include "Light.h"

Light::Light()
{
	_intensity = 1.0;
	_pos.setPoint(0,0,0);
	_color.setColor(1,1,1);
}

Light::Light(float x, float y, float z) {
	_intensity = 1.0;
	_pos.setPoint(x,y,z);
	_color.setColor(1,1,1);
}

Light::~Light()
{

}

void Light::setPos(float x, float y, float z) {
	_pos.setPoint(x,y,z);
}


void Light::setColor(float r, float g, float b) {
	_color.setColor(r,g,b);
}


void Light::setIntensity(float intensity) {
	_intensity = intensity;
}
