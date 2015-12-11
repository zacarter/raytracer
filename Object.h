#ifndef OBJECT_H
#define OBJECT_H
#include "Vector.h"

class Object {
	public:
		Object(){};
		virtual ~Object(){};
		virtual Vector getPos(void) = 0;
		virtual void setPos(float, float, float) = 0;
	protected:
		Vector _pos;			
};

#endif
