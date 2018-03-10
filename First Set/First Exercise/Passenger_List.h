#ifndef __PASSENGER_LIST__
#define __PASSENGER_LIST__

#include "train_simulation.h"

class Passenger;

class Passenger_List_Node;

class Passenger_List{				//Linked List which contains Data of type passenger
private:
	
	class Passenger_List_Node{
	public:
		Passenger* Data;
		Passenger_List_Node* next;

		Passenger_List_Node();    //This function will initialize Data
		~Passenger_List_Node();	  //This function will destroy Data
	};

	Passenger_List_Node *first_node,*last_node;

public:
	Passenger_List();

	int InsertAtEnd();      //Inserts the new passengers and returns the money that payed for the ticket
							//because they already payed for it at the station so they will counted from now
							//as train income 

	int Check();		    //This function will traverse the list and it will <<save>> 
						    //the illegal passengers to disembark them in the next station and count them
						    //and return how many were caught

	int Delete_Random();    //This function will disembark a random passenger and check if he/she
				    	    //is illegal,because they escaped checking, so they will get counted

	int Delete_Illegals();  //This function will disembark the illegal passengers which get caught
							//between that station and the previous one and will return how many 
							//have been disembarked

	~Passenger_List();		//This function will destroy the list
};


#endif