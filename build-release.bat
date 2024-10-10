g++ -c src/*.cpp -std=c++14 -O3 -Wall -m64 -I include -I D:\Documents\Code\cpp\SDL2\include && g++ *.o -o debug/game -s -L D:\Documents\Code\cpp\SDL2\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
pause