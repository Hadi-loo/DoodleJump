CC = g++ --std=c++11
CFLAGS = -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
EXE_FILE = doodleJump.out

$(EXE_FILE): main.o doodle.o platform.o monster.o spring.o rsdl.o
	$(CC) main.o doodle.o platform.o monster.o spring.o rsdl.o $(CFLAGS) -o $(EXE_FILE)

main.o: main.cpp doodle.hpp platform.hpp monster.hpp spring.hpp
	$(CC) -c main.cpp $(CFLAGS) -o main.o

doodle.o: doodle.cpp doodle.hpp consts.hpp
	$(CC) -c doodle.cpp $(CFLAGS) -o doodle.o

platform.o: platform.cpp platform.hpp consts.hpp
	$(CC) -c platform.cpp $(CFLAGS) -o platform.o

monster.o: monster.cpp monster.hpp consts.hpp
	$(CC) -c monster.cpp $(CFLAGS) -o monster.o

spring.o: spring.cpp spring.hpp consts.hpp
	$(CC) -c spring.cpp $(CFLAGS) -o spring.o

rsdl.o: rsdl.cpp rsdl.hpp
	$(CC) -c rsdl.cpp $(CFLAGS) -o rsdl.o

clean:
	rm *.o