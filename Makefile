# Change the following values to suit your system.

CFLAGS=`sdl-config --cflags` -g -W -Wall -Weffc++ -Wextra -pedantic -O0
SDL_LIB=`sdl-config --libs` -lSDL_ttf -lSDL_image
CCC=g++

OBJECTS = generateFrames.o controller.o pixie.o

run: main.o $(OBJECTS)
	$(CCC) $(CFLAGS) main.cpp -o run $(OBJECTS) $(SDL_LIB)

main.o: main.cpp generateFrames.h controller.h
	$(CCC) $(CFLAGS) -c main.cpp

generateFrames.o: generateFrames.cpp generateFrames.h
	$(CCC) $(CFLAGS) -c generateFrames.cpp
    
controller.o: controller.cpp controller.h pixie.h
	$(CCC) $(CFLAGS) -c controller.cpp
    
pixie.o: pixie.cpp pixie.h
	$(CCC) $(CFLAGS) -c pixie.cpp

clean:
	rm -f run *.o
	rm -f *~
	rm -f frames/*.bmp
