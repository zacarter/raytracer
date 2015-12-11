#include "ImagePlane.h"
#include <math.h>
#include <iostream>
#include <cassert>

/*
ImagePlane::ImagePlane() {
	
}
*/
ImagePlane::ImagePlane(Vector camPos, Vector lookAt, Vector up, float hfov, int pixw, int pixh) {
	_pixelsW = pixw;
	_pixelsH = pixh;
	_aspectRatio = (float)pixw/pixh;
	_hfov = hfov*M_PI/180; //convert hfov from degs to rads
	_vfov = hfov/_aspectRatio;
	_width = 2*(tan(_hfov/2));
	_height = _width/_aspectRatio;
	_pixelWidth = _width/_pixelsW;
	_pixelHeight = _height/_pixelsH;
	_origin = camPos;
	_normal = lookAt;
	_points = new Vector*[pixw];
	for (int i = 0; i < pixw; i++) {
		_points[i] = new Vector[pixh];
	}
	_v = up;
	_u = Vector::cross(up, lookAt);
	_v.normalize();
	_u.normalize();
	update();
}

ImagePlane::~ImagePlane() {
	delete [] _points;
}

void ImagePlane::update() {
	for (int x = 0; x < _pixelsW; x++) {
		for(int y = 0; y < _pixelsH; y++) {
			_points[x][y] = _origin+_normal+((_v*_pixelHeight)*(y-(_pixelsH/2)))+((_u*_pixelWidth)*(x-(_pixelsW/2)));
		}
	}
}

void ImagePlane::setOrigin(Vector origin) {
	_origin = origin;
	update();
}

void ImagePlane::setNormal(Vector normal) {
	_normal = normal;
	update();
}

void ImagePlane::setUpV(Vector upV) {
	_v = upV;
	_u = Vector::cross(_v, _normal);
	_v.normalize();
	_u.normalize();
	update();
}

#ifdef __TEST_ImagePlane__ //unit testing

int main() {
	Vector camPos(0,0,-5);
	Vector lookAt(0,0,1);
	Vector up(0,1,0);
	ImagePlane testPlane(camPos, lookAt, up, 45.0, 640, 480);
	
	std::cout << "ImagePlane Tests passed" << std::endl;
	return 0;
}

#endif
