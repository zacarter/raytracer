#ifndef SPHERE_H
#define SPHERE_H
#include "Renderable.h"
#include "Ray.h"

class Sphere: public Renderable {
	public:
		Sphere();
		Sphere(float rad);
		~Sphere();
		Vector getPos();
		float getRad();
		Color getColor();
		void setPos(float x, float y, float z);
		void setPos(Vector inputLocation);
		void setRad(float r);
		void setColor(Color color);
		void setColor(float r, float g, float b);
		Vector surfaceNormalAt(Vector Ri);
		Hit intersectsRay(Ray feelerRay);
		float solveQuadratic(float a, float b, float c);
		Vector getIntersectionPoint(Ray ray, float root);
	private:
		float _radius;
};

#endif
