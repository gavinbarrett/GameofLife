gol: main.o Game.o Pixel.o
	g++ -Wall -Werror -std=c++11 -lSDL2_image -lSDL2main -lSDL2 -lm -o gol main.o Game.o Pixel.o

main.o: main.cc Game.h
	g++ -Wall -Werror -std=c++11 -lSDL2_image -lSDL2main -lSDL2 -lm -c main.cc

Game.o: Game.cc Game.h
	g++ -Wall -Werror -std=c++11 -lSDL2_image -lSDL2main -lSDL2 -lm -c Game.cc

Pixel.o: Pixel.cc Pixel.h
	g++ -Wall -Werror -std=c++11 -lSDL2_image -lSDL2main -lSDL2 -lm -c Pixel.cc

clean:
	rm gol main.o Game.o Pixel.o
