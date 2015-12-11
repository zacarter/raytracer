#ifndef CAMERA_H
#define CAMERA_H
#include "Object.h"
#include "Color.h"
#include "Vector.h"
#include "ImagePlane.h"

// XXX camera should do image plane computation
// i.e. Ray getRay(Vector2d);
// write unit tests for nontrivial functions
class Camera: public Object {
	public:
		Camera();
		Camera(float x, float y, float z);
		Camera(float hfov, int pixw, int pixh);
		~Camera();
		int getPixWide(){return _nearPlane->getPixWide();};
		int getPixHigh(){return _nearPlane->getPixHigh();};
		Vector getPos();
		Vector getLookAt();
		Vector getUp();
		Vector** getImagePoints(){return _nearPlane->getPoints();};
		void setPos(float x, float y, float z);
		void setLookAt(float x, float y, float z);
		void setUp(float x, float y, float z);
		void setPos(Vector inputLocation);
		void setLookAt(Vector in_LookAt);
		void setUp(Vector input_up);
	private:
		Vector _lookAt, _up;
		ImagePlane *_nearPlane;
};

#endif

