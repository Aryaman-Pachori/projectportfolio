CC = g++
CFLAGS = -g -std=c++11 -Wall -Wno-deprecated-declarations 
INCFLAGS = -I./glm-0.9.7.1 -I/usr/local/include
LDFLAGS = -L/usr/local/lib -lfreeimage
  
all : raytracer

scene1: raytracer
	./raytracer testscenes/scene1.test

scene2: raytracer
	./raytracer testscenes/scene2.test

scene3: raytracer
	./raytracer testscenes/scene3.test

scene4-ambient: raytracer
	./raytracer testscenes/scene4-ambient.test

scene4-emission: raytracer
	./raytracer testscenes/scene4-emission.test

scene4-diffuse: raytracer
	./raytracer testscenes/scene4-diffuse.test

scene4-specular: raytracer
	./raytracer testscenes/scene4-specular.test

scene5: raytracer
	./raytracer testscenes/scene5.test

scene6: raytracer
	./raytracer testscenes/scene6.test

scene7: raytracer
	./raytracer testscenes/scene7.test

custom: raytracer
	./raytracer testscenes/custom.test

raytracer : main.o readfile.o film.o scene.o camera.o raytracer.o geometry.o Transform.o Light.o variables.h readfile.h  Film.h Scene.h ray.h Raytracer.h Geometry.h Transform.h Light.h # UniformGrid.h
	${CC} ${CFLAGS} -o raytracer main.o scene.o film.o readfile.o camera.o raytracer.o geometry.o Transform.o Light.o ${INCFLAGS} ${LDFLAGS}

main.o : main.cpp variables.h Scene.h readfile.h ray.h 
	${CC} ${CFLAGS} ${INCFLAGS} -c main.cpp

scene.o: Scene.cpp Scene.h variables.h ray.h Camera.h
	${CC} ${CFLAGS} ${INCFLAGS} -c scene.cpp

readfile.o : readfile.cpp readfile.h variables.h Geometry.h Transform.h Light.h
	${CC} ${CFLAGS} ${INCFLAGS} -c readfile.cpp

film.o: Film.cpp Film.h variables.h Color.h
	${CC} ${CFLAGS} ${INCFLAGS} -c film.cpp

camera.o: Camera.cpp Camera.h variables.h ray.h
	${CC} ${CFLAGS} ${INCFLAGS} -c camera.cpp

raytracer.o : Raytracer.cpp variables.h Color.h ray.h
	${CC} ${CFLAGS} ${INCFLAGS} -c Raytracer.cpp

geometry.o: Geometry.cpp Geometry.h ray.h variables.h Color.h
	${CC} ${CFLAGS} ${INCFLAGS} -c Geometry.cpp

Transform.o: Transform.cpp Transform.h variables.h
	${CC} ${CFLAGS} ${INCFLAGS} -c Transform.cpp

Light.o: Light.cpp Light.h variables.h ray.h
	${CC} ${CFLAGS} ${INCFLAGS} -c Light.cpp

clean:
	rm -rf *.o *~ raytracer