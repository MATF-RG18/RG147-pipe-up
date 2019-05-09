PRG = pipe_up
CC = g++
CFLAGS = -g -Wall -std=c++11
GL = -lglut -lGL -lGLU

$(PRG):
	$(CC) -o $(PRG) main.cpp $(CFLAGS) $(GL)

.PHONY: clean

clean:
	rm $(PRG)
