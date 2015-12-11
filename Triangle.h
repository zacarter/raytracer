#ifndef TRIANGLE_H_
#define TRIANGLE_H_
#include "Renderable.h"
#include <math.h>

class Triangle : public Renderable {
public:
	Triangle(Vector p1, Vector p2, Vector p3, Vector pos);
	~Triangle();
	Vector getPos(void){return _pos;};
	Color getColor(){return _color;};
	void setColor(float, float, float);
	void setPos(float, float, float);
	void setPos(Vector pos);
	float getArea(){return _area;};
	Hit intersectsRay(Ray);
	Vector getNormal(){return _normal;};
	
private:
	Vector _p1, _p2, _p3; //3 points
	Vector _u, _v;
	Vector _pos; //pivot point
	Vector _normal;
	Color _color;
	float _area;
	void computeArea();

};

#endif /*TRIANGLE_H_*/
