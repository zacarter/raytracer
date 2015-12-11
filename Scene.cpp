#include "Scene.h"

Scene::Scene(Camera* sceneCamera){
	_cameras.push_back(sceneCamera);
	_bg.setColor(0,0,0);
}

Scene::~Scene(){
	
}

void Scene::addObject(Renderable* object) {
	_objects.push_back(object);
}

void Scene::addLight(Light* light) {
	_lights.push_back(light);
}
		
void Scene::renderScene(GLubyte* image, int cam_id = 0) {
	Ray ray;
	Ray lightRay;
	Hit ip(false); //intersection point
	float Kd = 1; //diffuse coefficient
	float diffuse;
	int pixelsWide = _cameras[cam_id]->getPixWide();
	int pixelsHigh = _cameras[cam_id]->getPixHigh();
	Color ac_Acc(0,0,0); //set to background color
	Color diffuseTerm(0,0,0);
	float testDist = 0;
	float leastDist = 0;
	//Renderable* closest;
	Vector** imagePlane = _cameras[cam_id]->getImagePoints();
	ray.setPos(_cameras[cam_id]->getPos());
	int offset = 0;
	for(int y = 0; y < pixelsHigh; y++) {
		for (int x = 0; x < pixelsWide; x++) {
			ray.setDir(imagePlane[x][y] - ray.getPos());
			leastDist = 0;
			offset = 3*(x+pixelsWide*y);
			ac_Acc.setColor(0,0,0);
			for (_objects_iter=_objects.begin(); _objects_iter != _objects.end(); _objects_iter++) {
				ip = (*_objects_iter)->intersectsRay(ray);
				if (ip) { //if the ray intersects the object
					testDist = Vector::getDist(ip.getPos(),ray.getPos());
					if (testDist < leastDist || leastDist == 0) {
						leastDist = testDist;
						ac_Acc.setColor(0,0,0); //set this to background color
						diffuseTerm.setColor(0,0,0);
						for (_lights_iter=_lights.begin(); _lights_iter != _lights.end(); _lights_iter++) {
							if (!isShadowedBy(ip.getPos(),(*_objects_iter),(**_lights_iter))) {	
								lightRay.setDir((*_lights_iter)->getPos()-ip.getPos());
								Kd = lightRay.getDir().getNormalized()*ip.getNormal(); //this is (N dot L)
								if (Kd < 0.0) { Kd = 0.0; }
								diffuse = (*_objects_iter)->getDiffuse() * Kd;
								diffuseTerm = diffuseTerm + ((*_objects_iter)->getColor() * diffuse * (*_lights_iter)->getColor());
							}
						}
						//ac_Acc = recursiveTrace(ray.getDir(), ip, *_objects_iter, 0)*0.1 + diffuseTerm;
						ac_Acc = (*_objects_iter)->getColor()*(1.0)*(0.1) + diffuseTerm;
					}
				}
			}
			*(image + offset) = (GLubyte)(int)(ac_Acc.getR() < 1 ? ac_Acc.getR()*255 : 255 );
			*(image + offset+1) = (GLubyte)(int)(ac_Acc.getG() < 1 ? ac_Acc.getG()*255 : 255 );
			*(image + offset+2) = (GLubyte)(int)(ac_Acc.getB() < 1 ? ac_Acc.getB()*255 : 255 );
		}
	}
}

Color Scene::recursiveTrace(Vector inDir, Hit ip1, Renderable* object, int depth) {
	Vector reflectDir;
	Ray ray;
	Hit ip2(false);
	float leastDist = -1;
	Renderable* closest;
	std::list<Renderable*>::iterator _objects_iterTemp;
	
	ray.setPos(ip1.getPos());
	reflectDir = inDir*(inDir*ip1.getNormal());
	ray.setDir(reflectDir);
	for (_objects_iterTemp=_objects.begin(); _objects_iterTemp != _objects.end(); _objects_iterTemp++) {
		if ((*_objects_iterTemp) == object) { continue; }
		ip2 = (*_objects_iterTemp)->intersectsRay(ray);
		if (ip2) {
			if (Vector::getDist(ip1.getPos(),ip2.getPos()) < leastDist || leastDist == -1) {
				leastDist = Vector::getDist(ip2.getPos(),ip1.getPos());
				closest = (*_objects_iterTemp);
			}
		}		
	}
	if(ip2) {
		if (depth < 3) {
			return recursiveTrace(reflectDir, ip2, closest, depth+1);
		}
		else {
			return closest->getColor();
		}
	}
	else {
		return _bg;
	}
}

bool Scene::isShadowedBy(Vector surfacePoint, Renderable* object, Light light) {
	Ray ray;
	ray.setPos(surfacePoint);
	ray.setDir(light.getPos()-surfacePoint);
	float lightDist = Vector::getDist(surfacePoint, light.getPos());
	Hit ip(false);
	std::list<Renderable*>::iterator _objects_iterTemp;
	
	for (_objects_iterTemp=_objects.begin(); _objects_iterTemp != _objects.end(); _objects_iterTemp++) {
		if ((*_objects_iterTemp) == object) { continue; }
		ip = (*_objects_iterTemp)->intersectsRay(ray);
		if (ip) {
			if (Vector::getDist(ip.getPos(),surfacePoint) < lightDist) {
				return true;
			}
		}		
	}
	return false;
}
		
/* Compile with -D switch to run unit tests.
 *      Example : g++ -D __TEST_Scene__ -o TestVector Vector.cpp
 */
#ifdef __TEST_Scene__ //unit testing
#include <iostream>
#include <assert.h>

#define RED_CHANNEL(x, y) image[ 3*(y * pixelsWide + x) ]
#define GREEN_CHANNEL(x, y) image[ 3*(y * pixelsWide + x) + 1]
#define BLUE_CHANNEL(x, y) image [ 3*(y * pixelsWide + x) + 2 ]

int main() {
	int pixelsWide = 320;
	int pixelsHigh = 240;
	Camera sceneCam(45.0, pixelsWide, pixelsHigh);
	Scene myScene(&sceneCam);
	Sphere s1(2.5);
	s1.setPos(0,0,10);
	s1.setColor(0.8,0.8,0.8);
	myScene.addObject(&s1);
	GLubyte *image;
	image = new GLubyte[pixelsWide*pixelsHigh*3];
	myScene.renderScene(image,0);
    for (int y = 0; y < pixelsHigh; y++) {
    		for (int x = 0; x < pixelsWide; x++){
	    		assert((int)RED_CHANNEL(x,y) == 0.08 || (int)RED_CHANNEL(x,y) == 0);
	    		assert((int)GREEN_CHANNEL(x,y) == 0.08 || (int)GREEN_CHANNEL(x,y) == 0);
	    		assert((int)BLUE_CHANNEL(x,y) == 0.08 || (int)BLUE_CHANNEL(x,y) == 0);
      	}
    }
	std::cout << "Scene Test Successfull" << std::endl;
	return 0;
}

#endif
