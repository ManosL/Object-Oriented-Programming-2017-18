#ifndef __TRAIN_SIMULATION__
#define __TRAIN_SIMULATION__

#include "Passenger_List.h"

const int ticket_fine = 60;
const int ticket_price = 2;
const int reduced_price = 1;

class Waggon;
class Passenger;
class Passenger_List;

class Train{

private:
	Waggon** totalWaggons;    		//Needs double pointer because constructor has arguments
	const size_t stations,waggons;
	size_t money;					//This is the train statistic

public:
	Train(const size_t&,const size_t&);
	void printStatistics() const;
	void operate();
	~Train();
};

class Waggon{

private:
	Passenger_List* passengers;
	const int maxCapacity;
	size_t collected_money;
	int no_of_passengers; 					   //no = number
	int illegal_passengers, escaped_checking;  //This are the waggon statistics
	int To_Check;							   //1 if the waggon will be checked

public:
	Waggon(const int&);
	void inStation(int);
	void betweenStations();

	inline size_t getMoney(){			//It is an accessor but after the money go to the
		size_t temp = collected_money;  //train budget the wagon budget empties
		collected_money = 0;
		return temp; 
	}
	void printStatistics() const;
	~Waggon();
};

class Passenger{

private:
	const int ticket;				//Informs if the passenger has a ticket
	const int can_have_reduced;	//Informs if the passenger can have reduced ticket
	int To_Disembark;       // 1 if the checker caught him without ticket 

public:
	Passenger(const int&,const int&);
	inline int has_ticket() const{ return ticket; }
	inline int Rights_reduced() const{ return can_have_reduced; }
	inline int To_be_Disembarked() const{ return To_Disembark; }

	inline void Caught_Illegal(){ To_Disembark = 1; }
	
	~Passenger(){} //Destructor doesn't need to do anything
};

#endif