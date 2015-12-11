#ifndef SCENE_H_
#define SCENE_H_
#include "Vector.h"
#include "Ray.h"
#include "Camera.h"
#include "Color.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Light.h"
#include <list>
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class Scene {
	public:
		Scene(Camera* sceneCamera);
		~Scene();
		void addObject(Renderable* object);
		void addLight(Light* light);
		void renderScene(GLubyte* image, int cam_id);
	private:
		std::vector<Camera*> _cameras;
		//Renderable* objects[];
		std::list<Renderable*> _objects;
		std::list<Renderable*>::iterator _objects_iter;
		//will also have lights and other non-renderable objects
		std::list<Light*> _lights;
		std::list<Light*>::iterator _lights_iter;
		Color _bg;
		Color recursiveTrace(Vector inDir, Hit ip1, Renderable* object, int depth);
		bool isShadowedBy(Vector surfacePoint, Renderable* object, Light light);
};

#endif /*SCENE_H_*/
