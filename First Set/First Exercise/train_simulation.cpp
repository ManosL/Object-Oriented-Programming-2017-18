#include <iostream>
#include <cstdlib>

#include "train_simulation.h"

using namespace std;

Train::Train(const size_t& stations_num,const size_t& waggons_num) : stations(stations_num), waggons(waggons_num),money(0)
{
	int maxCapacity = rand()%151 + 150;  				//Because I think that a regular train waggon cannot
								  						// have more than 300 passengers or less than 150 passengers

	totalWaggons = new Waggon*[waggons];				//Moreover every waggon has the same capacity with the others
	for(int i = 0;i < waggons;i++){
		totalWaggons[i] = new Waggon(maxCapacity); 
	}

	cout<<"A metro train with "<<waggons<<" waggons, was created"<<endl;
}

void Train::operate(){

	for(int i = 1;i < stations;i++){				//For each station, except the last one 
		for(int j = 0;j < waggons;j++){				//In station, for each waggon
			totalWaggons[j]->inStation(0);
			money += totalWaggons[j]->getMoney();
		}

		for(int j = 0;j < waggons;j++){				//Between stations, for each waggon

			totalWaggons[j]->betweenStations();

			money += totalWaggons[j]->getMoney();
		}
	}

	for(int i = 0;i < waggons;i++){					//St the last station, for each waggon
		totalWaggons[i]->inStation(1);
	}
}

void Train::printStatistics() const {
	cout<<endl<<"The train collected "<<money<<" euros from legal and illegal passengers"<<endl<<endl;

	for(int i = 0;i < waggons;i++){
		cout<<"Waggon "<< i+1 <<endl;           //For each waggon, I will print their statistics

		totalWaggons[i]->printStatistics(); 
	}
}

Train::~Train(){

	cout<<"A train was destroyed"<<endl;

	for(int i = 0;i < waggons;i++){			 //I destroy each waggon
		delete totalWaggons[i];
	}
	delete[] totalWaggons;

}

Waggon::Waggon(const int& maxCap) : maxCapacity(maxCap),no_of_passengers(0),illegal_passengers(0),escaped_checking(0),
							 collected_money(0),To_Check(0)
{
	passengers = new Passenger_List;
	cout<<"A waggon with capacity for "<<maxCapacity<<" passengers, was created"<<endl;
}

void Waggon::inStation(int Last_Station){
	int disembark_passengers;

	no_of_passengers -= passengers->Delete_Illegals(); //Force Dissembark of the illegal passengers that have been caught 

	if(Last_Station){									//If I were at the last station
		escaped_checking += passengers->Check();		//I check for illegal passengers and count them as passengers
														//which escaped checking because all passengers will disembark
		return;
	}

	disembark_passengers = rand() % (no_of_passengers + 1);  	 //Determine the number of passengers that will disembark

	for(int i=0;i < disembark_passengers;i++){       		 	 //I do first the disembarkment because in the metro stations
		escaped_checking += passengers->Delete_Random();		 // it is done like that

		no_of_passengers--;
	}

	int embark_passengers = rand() % (maxCapacity - no_of_passengers + 1);  //Determine the number of passengers the will embark

	for(int i=0;i < embark_passengers;i++){
		collected_money += passengers->InsertAtEnd();

		no_of_passengers++;
	}

	To_Check =  rand() % 2;    //Decide if the waggon will be checked

	return;

}

void Waggon::betweenStations(){    
	
	if(To_Check){											//If the waggon choosed to be checked,
		int new_illegal_passengers = passengers->Check();	//Check it.

		illegal_passengers += new_illegal_passengers;		//add to illegal_passengers the no.
															//of passengers that the checker caught

		collected_money = new_illegal_passengers*ticket_fine; //All the illegals have the same fine

		To_Check = 0;
	}

	return;
}

void Waggon::printStatistics() const{								//Print Wagon statistics
	cout<<"Found "<<illegal_passengers<<" illegal passengers and,"<<endl;
	cout<<escaped_checking << " illegal passengers escaped checking"<<endl<<endl;
}

Waggon::~Waggon(){

	delete passengers;
	cout<<"A waggon was destroyed"<<endl;
}

Passenger::Passenger(const int& tickt,const int& reduced) : ticket(tickt), can_have_reduced(reduced), To_Disembark(0)
{
	//Blank Body, because I initialized the fields in the initializer list
} 