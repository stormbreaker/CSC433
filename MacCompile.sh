# g++ -std=c++14 main.cpp Tank.h Tank.cpp -framework OpenGL -framework GLUT

g++ -std=c++14 -c main.cpp
g++ -std=c++14 -c Tank.cpp
g++ -std=c++14 main.o Tank.o -o TankWars -framework OpenGL -framework GLUT

rm main.o
rm Tank.o
