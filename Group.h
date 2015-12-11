#ifndef GROUP_H_
#define GROUP_H_
#include "Renderable.h"
#include "Ray.h" 

class Group : public Renderable {
	//set<Renderable*> _children;
	// Box _bounds; // XXX do bounding box optimization at some point
public:
	Group();
	virtual ~Group();
	/*
	void add(Renderable* obj) { _children.insert(obj); }
	void rm(Renderable* obj) { _children.remove(obj); }
	
	Hit intersect(Ray) {
	
		 FOR_EACH(i, _chidren) {
		 	
		 }	
	}
	*/
};

#endif /*GROUP_H_*/
