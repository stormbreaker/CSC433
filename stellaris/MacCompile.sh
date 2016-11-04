g++ -c -o planet.o planet.cpp -w
g++ -c -o solar.o solar.cpp -w
g++ -c -o common.o common.cpp -w

g++ -std=c++14 -o solar planet.o solar.o common.o -framework OpenGL -framework GLUT

rm *.o

./solar
