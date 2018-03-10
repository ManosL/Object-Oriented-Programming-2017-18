Artifact: main.o Artifact.o
	g++ main.o Artifact.o -o Artifact

main.o: main.cpp
	g++ -c main.cpp

Artifact.o: Artifact.cpp
	g++ -c Artifact.cpp

.PHONY: clear

clear:
	rm -rf main.o Artifact.o Artifact			