#ifndef RAY_H
#define RAY_H
#include "Vector.h"
#include <iostream>

class Ray
{
	public:
		Ray();
		~Ray();
		void setPos(float x, float y, float z);
		void setDir(float x, float y, float z);
		void setPos(Vector pos);
		void setDir(Vector dir);
		Vector getPos(){return _pos;};
		Vector getDir(){return _dir;};
		void toString();
	private:
		Vector _pos;
		Vector _dir;
};

#endif
