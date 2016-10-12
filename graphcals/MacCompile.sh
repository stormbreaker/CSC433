#g++ -std=c++14 -c fractalview.cpp -w 
#g++ -std=c++14 fractalview.o -o fractalviewer  -framework OpenGL -framework GLUT

g++ -c -o fractalview.o fractalview.cpp
g++ -c -o mandelbrot.o mandelbrot.cpp
g++ -c -o julia.o julia.cpp
g++ -c -o common.o common.cpp

g++ -std=c++14 fractalviewer fractalview.o mandelbrot.o julia.o common.o -framework OpenGL - framework GLUT

#g++ -o fractalviewer fractalview.o mandelbrot.o julia.o common.o -lglut -lGLU -lGL -lm

rm *.o


./fractalviewer
