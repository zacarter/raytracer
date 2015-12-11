#ifndef RENDERABLE_H_
#define RENDERABLE_H_
#include "Object.h"
#include "Color.h"
#include "Ray.h"
#include "Hit.h"

class Renderable : Object {
	public:
		Renderable(){};
		virtual ~Renderable(){};
		virtual Vector getPos(void) = 0;
		virtual void setPos(float, float, float) = 0;
		// XXX create an Intersection class that stores
		// position, normal, material properties, etc.
		virtual Hit intersectsRay(Ray) = 0;
		virtual void setColor(float, float, float) = 0;
		virtual Color getColor() = 0;
		void setDiffuse(float diffuse){_diffuse = diffuse;};
		float getDiffuse(){return _diffuse;};
		
	protected:
		Vector _pos;	
		Color _color;
		float _diffuse;
};
#endif /*RENDERABLE_H_*/
