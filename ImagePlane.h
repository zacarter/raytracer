#ifndef IMAGEPLANE_H
#define IMAGEPLANE_H
//#include "Ray.h"
#include "Vector.h"

class ImagePlane {
	public:
		//ImagePlane();
		ImagePlane(Vector camPos, Vector lookAt, Vector up, float hfov, int pixw, int pixh);
		~ImagePlane();
		Vector** getPoints(){return _points;};
		int getPixWide(){return _pixelsW;};
		int getPixHigh(){return _pixelsH;};
		void setOrigin(Vector origin);
		void setNormal(Vector normal);
		void setUpV(Vector upV);
		void update(); //refresh the image plane after change in camera orientation
	private: 
		int _pixelsW;
		int _pixelsH;
		float _aspectRatio;
		float _hfov;
		float _vfov;
		float _width;
		float _height;
		float _pixelWidth;
		float _pixelHeight;
		Vector _u, _v; //image plane uv vectors
		Vector _origin; //camera center
		Vector _normal;
		Vector **_points;
};

#endif
