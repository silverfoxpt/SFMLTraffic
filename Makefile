SFML_INCLUDE_PATH = ./SFML-2.5.1/include
SFML_LIB_PATH = ./SFML-2.5.1/lib

all: compile link

compile:
	g++ -c *.cpp -I$(SFML_INCLUDE_PATH) -DSFML_STATIC -O2 -Wall -pedantic -Wno-unknown-pragmas
	g++ -c ./Map/*.cpp -I$(SFML_INCLUDE_PATH) -DSFML_STATIC -O2 -Wall -pedantic -Wno-unknown-pragmas
	g++ -c ./Simulation/*.cpp -I$(SFML_INCLUDE_PATH) -DSFML_STATIC -O2 -Wall -pedantic -Wno-unknown-pragmas
	g++ -c ./IMGUI/*.cpp -I$(SFML_INCLUDE_PATH) -DSFML_STATIC -O2

link:
	g++ *.o -o main -L$(SFML_LIB_PATH) -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -lsfml-main
