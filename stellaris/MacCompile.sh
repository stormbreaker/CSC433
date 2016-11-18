g++ -c -o planet.o planet.cpp -w
g++ -c -o solar.o solar.cpp -w
g++ -c -o common.o common.cpp -w
g++ -c -o imagemanip.o imagemanip.cpp -w
g++ -c -o events.o events.cpp -w

g++ -std=c++14 -o solar planet.o solar.o common.o imagemanip.o events.o -framework OpenGL -framework GLUT

rm *.o

./solar
