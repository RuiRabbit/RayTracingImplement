CC = g++
CPPFLAGS = -g -Wall

SOURCE = main.cpp algebra3.cpp Camera.cpp PPM.cpp Ray.cpp Sphere.cpp Triangle.cpp
OBJ = $(SOURCE:.cpp=.o)

all: main

main: $(OBJ)
	$(CC) $^ -o hw1

clean:
	rm *.o	
	rm hw1