all: compile link

compile:
	g++ -c *.cpp 					-I "D:\SFML-2.5.1\include" -I "D:\boost_1_82_0" -DSFML_STATIC -O2 -Wall -pedantic -Wno-unknown-pragmas
	g++ -c "./Map/*.cpp" 			-I "D:\SFML-2.5.1\include" -I "D:\boost_1_82_0" -DSFML_STATIC -O2 -Wall -pedantic -Wno-unknown-pragmas
	g++ -c "./Simulation/*.cpp" 	-I "D:\SFML-2.5.1\include" -I "D:\boost_1_82_0" -DSFML_STATIC -O2 -Wall -pedantic -Wno-unknown-pragmas

	g++ -c "./IMGui Stuffs/*.cpp" 	-I "D:\SFML-2.5.1\include" -DSFML_STATIC -O2

link: 
	g++ *.o -o main -L "D:\SFML-2.5.1\lib" -L "D:\boost_1_82_0\libs" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -lsfml-main 
