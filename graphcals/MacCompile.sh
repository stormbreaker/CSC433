#g++ -std=c++14 -c fractalview.cpp -w 
#g++ -std=c++14 fractalview.o -o fractalviewer  -framework OpenGL -framework GLUT

g++ -c -o fractalview.o fractalview.cpp -w
g++ -c -o mandelbrot.o mandelbrot.cpp -w
g++ -c -o julia.o julia.cpp -w
g++ -c -o common.o common.cpp -w

g++ -std=c++14 -o fractalviewer fractalview.o mandelbrot.o julia.o common.o -framework OpenGL -framework GLUT

#g++ -o fractalviewer fractalview.o mandelbrot.o julia.o common.o -lglut -lGLU -lGL -lm

rm *.o


./fractalviewer
