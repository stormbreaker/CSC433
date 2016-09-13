# g++ -std=c++14 main.cpp Tank.h Tank.cpp -framework OpenGL -framework GLUT

g++ -std=c++14 -c TankWars.cpp -w
g++ -std=c++14 -c Tank.cpp -w
g++ -std=c++14 -c Terrain.cpp -w
g++ -std=c++14 TankWars.o Tank.o Terrain.o -o TankWars -framework OpenGL -framework GLUT

rm *.o

./TankWars
