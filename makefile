OBJECTS = Render.o Vector.o
UNIT_TESTS = TestVector TestImagePlane TestSphere TestCamera TestTriangle TestScene TestRender
DRIVERS = Render
CC = g++ # compile with GNU C++ compiler
CFLAGS = -g -Wall # create symbol table for debugging and print all warnings

Test: $(UNIT_TESTS) 

build: $(DRIVERS)

all: $(DRIVERS)

TestRender: Vector.o Ray.o Color.o Hit.o Light.o Triangle.o Sphere.o ImagePlane.o Camera.o Scene.o
	$(CC)$(CFLAGS) -D __TEST_Render__ Vector.o Ray.o Color.o Hit.o Light.o Triangle.o Sphere.o ImagePlane.o Camera.o Scene.o -o TestRender Render.cpp -lGL -lglut -lpthread
TestScene: Vector.o Ray.o Color.o Hit.o Light.o Triangle.o Sphere.o ImagePlane.o Camera.o Scene.o
	$(CC)$(CFLAGS) -D __TEST_Scene__ Vector.o Color.o Ray.o Hit.o Light.o Triangle.o Sphere.o ImagePlane.o Camera.o -o TestScene Scene.cpp
TestTriangle: Vector.o Ray.o Color.o Hit.o Triangle.o
	$(CC)$(CFLAGS) -D __TEST_Triangle__ Vector.o Color.o Ray.o Hit.o -o TestTriangle Triangle.cpp
TestSphere: Vector.o Ray.o Color.o Hit.o Sphere.o
	$(CC)$(CFLAGS) -D __TEST_Sphere__ Vector.o Color.o Ray.o Hit.o -o TestSphere Sphere.cpp
TestVector: Vector.o
	$(CC)$(CFLAGS) -D __TEST_Vector__ -o TestVector Vector.cpp 
TestImagePlane: Vector.o Ray.o ImagePlane.o
	$(CC)$(CFLAGS) -D __TEST_ImagePlane__ Vector.o -o TestImagePlane ImagePlane.cpp
TestCamera:  Vector.o Ray.o ImagePlane.o Camera.o
	$(CC)$(CFLAGS) -D __TEST_Camera__ Vector.o ImagePlane.o -o TestCamera Camera.cpp
Render: Render.cpp Vector.o Ray.o Color.o Hit.o Light.o ImagePlane.o Triangle.o Sphere.o Camera.o Scene.o
	$(CC)$(CFLAGS) Vector.o Color.o Ray.o Sphere.o ImagePlane.o Hit.o Light.o  Triangle.o Camera.o Scene.o -o Render Render.cpp -lGL -lglut -lpthread

Render.o: Vector.o Ray.o Color.o Hit.o ImagePlane.o Camera.o Renderable.h Sphere.h Triangle.h Scene.h Render.cpp
	$(CC)$(CFLAGS) -c Render.cpp -lGL -lglut -lpthread
Scene.o: Vector.o Ray.o Color.o Hit.o ImagePlane.o Camera.o Triangle.o Sphere.o Scene.h Scene.cpp
	$(CC)$(CFLAGS) -c Scene.cpp -lGL -lglut
Triangle.o: Vector.o Color.o Ray.o Hit.o Renderable.h Triangle.h Triangle.cpp
	$(CC)$(CFLAGS) -c Triangle.cpp
Sphere.o: Vector.o Color.o Hit.o Renderable.h Sphere.h Sphere.cpp
	$(CC)$(CFLAGS) -c Sphere.cpp
Vector.o: Vector.h Vector.cpp
	$(CC)$(CFLAGS) -c Vector.cpp
ImagePlane.o: Vector.o Ray.o ImagePlane.h ImagePlane.cpp
	$(CC)$(CFLAGS) -c ImagePlane.cpp
Color.o: Color.h Color.cpp
	$(CC)$(CFLAGS) -c Color.cpp
Ray.o: Vector.o Ray.h Ray.cpp
	$(CC)$(CFLAGS) -c Ray.cpp
Camera.o: Vector.o Ray.o ImagePlane.o Camera.h Camera.cpp
	$(CC)$(CFLAGS) -c Camera.cpp
Hit.o: Vector.o Ray.o Color.o Hit.h Hit.cpp
	$(CC)$(CFLAGS) -c Hit.cpp
Light.o: Vector.o Color.o Light.h Light.cpp
	$(CC)$(CGLAGS) -c Light.cpp


clean: 
	rm -f *.o *~ core.* *.a

# clean and recompile as defined in Build
