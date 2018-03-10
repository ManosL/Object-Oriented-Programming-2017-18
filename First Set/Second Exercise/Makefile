Airport_Simulator: main.o Airport.o Flight.o Application.o
	g++ main.o Airport.o Flight.o Application.o -g -o Airport_Simulator

main.o: main.cpp
	g++ -c main.cpp

Airport.o: Airport.cpp
	g++ -c Airport.cpp

Flight.o: Flight.cpp
	g++ -c Flight.cpp

Application.o: Application.cpp
	g++ -c Application.cpp

.PHONY: clean

clean:
	rm 	Airport_Simulator main.o Airport.o Flight.o Application.o		