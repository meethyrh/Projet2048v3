output: my2048.o BasePlateau.o EtatPlateau.o OpperationPlateau.o test_jeu.o
	g++ -std=c++11 BasePlateau.o EtatPlateau.o OpperationPlateau.o test_jeu.o my2048.o -lncurses -o my2048

my2048.o: my2048.cpp
	g++ -c my2048.cpp

BasePlateau.o: BasePlateau.cpp Jeu2048.h
	g++ -c -std=c++11 BasePlateau.cpp

OpperationPlateau.o: OpperationPlateau.cpp Jeu2048.h
	g++ -c -std=c++11 OpperationPlateau.cpp

EtatPlateau.o: EtatPlateau.cpp Jeu2048.h
	g++ -c -std=c++11 EtatPlateau.cpp

test_jeu.o: test_jeu.cpp Jeu2048.h
	g++ -c -std=c++11 test_jeu.cpp

clean:
	rm *.o my2048