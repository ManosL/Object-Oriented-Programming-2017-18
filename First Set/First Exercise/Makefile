Train_Simulator: main.o Passenger_List.o train_simulation.o
	g++ main.o Passenger_List.o train_simulation.o -o Train_Simulator

main.o: main.cpp
	g++ -c main.cpp

Passenger_List.o: Passenger_List.cpp
	g++ -c Passenger_List.cpp

train_simulation.o: train_simulation.cpp
	g++ -c train_simulation.cpp

.PHONY: clear

clean:
	rm Train_Simulator main.o Passenger_List.o train_simulation.o				