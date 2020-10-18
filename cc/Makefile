gol: main.o
	g++ -Wall -Werror -std=c++11 -lSDL2_image -lSDL2main -lSDL2 -lm -o gol main.o

main.o: main.cc
	g++ -Wall -Werror -std=c++11 -lSDL2_image -lSDL2main -lSDL2 -lm -c main.cc

clean:
	rm gol main.o
