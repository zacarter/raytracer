#ifndef LIGHT_H_
#define LIGHT_H_
#include "Color.h"
#include "Vector.h"

class Light {
	public:
		Light();
		Light(float x, float y, float z);
		virtual ~Light();
		void setPos(float x, float y, float z);
		void setColor(float r, float g, float b);
		void setIntensity(float intensity);
		Vector getPos(){return _pos;};
		float getIntensity(){return _intensity;};
		Color getColor(){return _color;};
		
	private:
		Vector _pos;
		float _intensity;
		Color _color;
};

#endif /*LIGHT_H_*/
