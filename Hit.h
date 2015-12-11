#ifndef HIT_H_
#define HIT_H_
#include "Vector.h"

class Hit {
	public: 
		Hit(bool hit);
		~Hit();
		operator bool();
		void operator=(const Hit& rhs);
		Vector getPos();
		Vector getNormal();
		void setHit(bool hit);
		void setPos(Vector pos);
		void setNormal(Vector normal);
		void toString();
	private:
		Vector _pos;
		Vector _normal;
		bool _hit;
		// Material _material;
		// double s;
};

#endif /*HIT_H_*/
