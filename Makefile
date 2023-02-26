build:
	g++ -o main *.cpp -lSDL2 -lSDL2_ttf -lSDL2_mixer
run:
	g++ -o main *.cpp -lSDL2 -lSDL2_ttf -lSDL2_mixer && ./main && clear
