#ifndef VECTOR_H
#define VECTOR_H
#include <math.h>
#include <string>

class Vector {
	public:
		Vector();
		Vector(float x, float y, float z);
		Vector(const Vector& clone);
		void setPoint(float x, float y, float z);	
		float getX(){return _x;};
		float getY(){return _y;};
		float getZ(){return _z;};
		Vector getNormalized();
		void normalize();
		float getNorm();
		void operator=(const Vector& rhs);
		bool operator==(const Vector& rhs);
		Vector operator-(const Vector& rhs);
		Vector operator+(const Vector& rhs);
		float operator*(const Vector& rhs); //scalar or dot product, XXX consider operator^
		Vector operator*(const float rhs);
		void toString();
		static Vector cross(Vector a, Vector b);
		static float getDist(Vector a, Vector b);
	private:
		float _x;
		float _y;
		float _z;
};

#endif
