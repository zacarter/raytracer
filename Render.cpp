#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "Camera.h"
#include "Color.h"
#include "Ray.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Vector.h"
#include "Scene.h"
#include "Light.h"
//#include "/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers/gl.h"
//#include "/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers/glu.h"
//#include "/System/Library/Frameworks/GLUT.framework/Versions/A/Headers/glut.h"

using namespace std;

GLubyte *image;
GLuint textures[1];
GLuint texture = 0;
int pixelsWide; 
int pixelsHigh;
float hfov;
Camera* sceneCam;
Scene* myScene;

GLvoid InitGL(GLvoid){};
GLvoid DrawGLScene(GLvoid){};
GLvoid ReSizeGLScene(int Width, int Height){};

float* parseVertex(string line);
float* parseSphere(string line);
void getFormat(string line); // set pixelsWide and pixelsHigh
void getProjection(string line);
Renderable* makeTri(string line);

void parseScene(ifstream* inputFile) {
	string line;
	float *tokens;
	char buffer[256];
	Renderable* object;
	//need also a list of vertices for obj
    while (! inputFile->eof() ) {
      inputFile->getline(buffer,256);
      line = buffer;
      if (line.find("Sphere") != string::npos) {
      	tokens = parseSphere(line);
      	object = new Sphere(tokens[0]);
      	object->setPos(tokens[1], tokens[2], tokens[3]);
      	object->setColor(0.8,0.8,0.2);
      	myScene->addObject(object);
      }
      else if (line.find("Format") != string::npos) {
      	getFormat(line);
      }
      else if (line.find("Projection") != string::npos) {
      	getProjection(line);
      	sceneCam = new Camera(hfov,pixelsWide,pixelsHigh);
      	myScene = new Scene(sceneCam);
      	image = new GLubyte[pixelsWide*pixelsHigh*3];
      }
      else if (line.find("Tri") != string::npos) {
      	myScene->addObject(makeTri(line));
      }
      //else if(line.find("v") != string::npos) {
      	//float *components = parseVertex(line);
      	//vertexList.push_back(new Vector(components[0],components[1],components[2]));
      //}
      else if (line.find("Light") != string::npos) {
      	myScene->addLight(new Light(30,30,-35));
      }
    }
    inputFile->close();
    sceneCam->setPos(0,0,-30);
    sceneCam->setLookAt(0,0,1);
}

void init() {
	myScene->renderScene(image,0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures( 1, textures);
	glBindTexture( GL_TEXTURE_RECTANGLE_ARB, textures[0] );
	glTexImage2D( GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGB8, pixelsWide, pixelsHigh, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
    glEnable( GL_TEXTURE_RECTANGLE_ARB );
    glMatrixMode( GL_TEXTURE );
    glScalef( pixelsWide, pixelsHigh, 1 );
    glMatrixMode(GL_MODELVIEW);

	/*
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glClearColor(0.0,0.0,0.0,0.0);
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    glShadeModel(GL_FLAT);
    myScene->renderScene(image,0);
	*/
}

void display() {
	/*
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glRasterPos2i(0,0);
    gluOrtho2D( 0, pixelsWide, 0, pixelsHigh );
    glMatrixMode( GL_MODELVIEW );
    glDrawPixels(pixelsWide, pixelsHigh, GL_RGB, GL_UNSIGNED_BYTE, image);
    glFlush();
	*/
	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glBindTexture( GL_TEXTURE_RECTANGLE_ARB, textures[0] );

    glBegin( GL_QUADS );
            glTexCoord2f( 0.0, 0.0 );
            glVertex2i( 0, 0 );
            glTexCoord2f( 1.0, 0.0 );
            glVertex2i( pixelsWide, 0 );
            glTexCoord2f( 1.0, 1.0 );
            glVertex2i( pixelsWide, pixelsHigh );
            glTexCoord2f( 0.0, 1.0 );
            glVertex2i( 0, pixelsHigh );
    glEnd();
    glutSwapBuffers();
	
}

void reshape( int swidth, int sheight )
{
        glViewport( 0, 0, swidth, sheight );

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        gluOrtho2D( 0, swidth, 0, sheight );
        glMatrixMode( GL_MODELVIEW );
}


#ifndef __TEST_Render__

int main(int argc, char** argv) 
{
    ifstream inputFile;
    ofstream outputImage;
            
    if (argc != 3)
    {
    		cout << "Usage: Render inputFile outputImage\n";
    		exit(1);
    }
    inputFile.open(argv[1]);
    outputImage.open(argv[2]);
    
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	parseScene(&inputFile);
	glutInitWindowSize(pixelsWide, pixelsHigh);
	glutInitWindowPosition(250,250);
	glutCreateWindow("Render View");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	
	glutMainLoop();

	return 0;
}

#endif

// given a string in the form: (v x y z), where x,y,z are floats, return a pointer to a float array: array [x,y,z]
float* parseVertex(string line) {
	float* vertex = new float[3];
	int leftBorder = line.find(' ',0);
	int rightBorder = line.find(' ', leftBorder+1);
	vertex[0] = (float)atof(line.substr(leftBorder+1,rightBorder-1).c_str());
	leftBorder = rightBorder;
	rightBorder = line.find(' ',leftBorder+1);
	vertex[1] = (float)atof(line.substr(leftBorder+1,rightBorder-1).c_str());
	vertex[2] = (float)atof(line.substr(rightBorder+1,line.length()-1).c_str());
	return vertex;
}

// given a string in the form: (Sphere r x y z), where r,x,y,z are floats, return a pointer to a float array: [r,x,y,z]
float* parseSphere(string line) {
	float* vertex = new float[4];
	int leftBorder = line.find(' ',0);
	int rightBorder = line.find(' ', leftBorder+1);
	vertex[0] = (float)atof(line.substr(leftBorder+1,rightBorder-1).c_str());
	leftBorder = rightBorder;
	rightBorder = line.find(' ',leftBorder+1);
	vertex[1] = (float)atof(line.substr(leftBorder+1,rightBorder-1).c_str());
	leftBorder = rightBorder;
	rightBorder = line.find(' ',leftBorder+1);
	vertex[2] = (float)atof(line.substr(leftBorder+1,rightBorder-1).c_str());
	vertex[3] = (float)atof(line.substr(rightBorder+1,line.length()-1).c_str());
	return vertex;
}

Renderable* makeTri(string line) {
	Vector v1;
	Vector v2;
	Vector v3;
	Vector pos(0,0,0);
	int leftBorder = 0;
	int rightBorder;
	float vertices[9];
	for (int count = 0; count < 3; count++) {
		leftBorder = line.find('(',leftBorder);
		rightBorder = line.find(',', leftBorder+1);
		vertices[3*count] = ((float)atof(line.substr(leftBorder+1,rightBorder-1).c_str()));
		leftBorder = rightBorder+1;
		rightBorder = line.find(',',leftBorder);
		vertices[3*count+1] = ((float)atof(line.substr(leftBorder,rightBorder-1).c_str()));
		leftBorder = rightBorder+1;
		rightBorder = line.find(')',leftBorder);
		vertices[3*count+2] = ((float)atof(line.substr(leftBorder,rightBorder-1).c_str()));
	}
	v1.setPoint(vertices[0],vertices[1],vertices[2]);
	v2.setPoint(vertices[3],vertices[4],vertices[5]);
	v3.setPoint(vertices[6],vertices[7],vertices[8]);
	return new Triangle(v1, v2, v3, pos);
}

void getFormat(string line) {
	int leftBorder = line.find(' ',0);
	int rightBorder = line.find(' ', leftBorder+1);
	pixelsWide = atoi(line.substr(leftBorder+1,rightBorder-1).c_str());
	pixelsHigh = atoi(line.substr(rightBorder+1,line.length()-1).c_str());
}

void getProjection(string line) {
	hfov = (float)atof(line.substr(line.rfind(' ',line.length()+1),line.length()-1).c_str());
}

#ifdef __TEST_Render__ //unit testing

int main(int argc, char** argv) {
	
}

#endif
