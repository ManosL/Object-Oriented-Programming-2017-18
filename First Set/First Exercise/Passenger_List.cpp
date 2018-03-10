#include <iostream>
#include <cstdlib>
#include <cassert>

#include "Passenger_List.h"

using namespace std;

Passenger_List::Passenger_List(){
	first_node = NULL;
	last_node = NULL;
} 

int Passenger_List::InsertAtEnd(){                 //Returns the money that the passenger payed for the ticket

	if(first_node == NULL && last_node == NULL){   //if the list is empty
		last_node = new Passenger_List_Node;
		first_node = last_node;
	}
	else{
		last_node->next = new Passenger_List_Node;
		last_node = last_node->next;
	}

	if(last_node->Data->has_ticket()){      		//If the passenger bought a ticket
		if(last_node->Data->Rights_reduced()){		//If the passenger bought reduced ticket
			return reduced_price;
		}
		else{
			return ticket_price;
		}
	}

	return 0;    									//If the passenger doesn't bought a ticket
}

int Passenger_List::Check(){						//Check for illegal passengers
	Passenger_List_Node* current = first_node;
	int illegals = 0;

	while(current != NULL){							//List Traversal
		if(!(current->Data)->has_ticket()){			//If I caught an illegal
			(current->Data)->Caught_Illegal();		//Save them for force disembarkment at the next station 
			illegals++;								//Increase the no of illegals
		}

		current = current->next;
	}

	return illegals;								//Return how many illegal passengers were caught
}

int Passenger_List::Delete_Random(){						//Delete a random passenger from the list
	Passenger_List_Node* current = first_node, *prev = NULL;
	int escaped_checking = 0;

	if(first_node == NULL && last_node == NULL) return 0;  //if the list is empty

	if(first_node == last_node){           				   //If the list has one node
		if(!(current->Data)->has_ticket()) 				   //This node must be deleted 
			escaped_checking++;

		delete current;
		first_node = last_node = NULL;

		return escaped_checking;
	}

	while(current != last_node){                  //else, I will delete a random passenger
		if((rand() % 2) == 1){					  //If rand() gives me 1 I will delete him
			if(!(current->Data)->has_ticket())	  //If he hasn't ticket he escaped checking so he will be counted
				escaped_checking++;

			if(prev != NULL){					  //If I delete a middle-node
				prev->next = current->next;
			}
			else{								  //If I delete the last node
				first_node = current->next;
			}

			delete current;

			return escaped_checking;
		}
		else{
			prev = current;
			current = current->next;
		}
	}

	if(!(current->Data)->has_ticket())        //If the rand doesn't return 1 I will delete the last passenger
		escaped_checking++;
	prev->next = NULL;
	last_node = prev;
	delete current;

	
	return escaped_checking;                 //return  1 if the passenger has escaped checking
}

int Passenger_List::Delete_Illegals(){							//I will delete all the passengers that caught as illegals
	Passenger_List_Node* current = first_node , *prev = NULL;
	int illegals = 0;

	while(current != NULL){										//I will traverse the list
		if((current->Data)->To_be_Disembarked()){				//If the passenger must be disembarked
			illegals++;											//count him

			if(first_node == last_node){						//After I just delete the nodes 
				delete first_node;
				first_node = last_node = NULL;
				current = NULL;
			}
			else
			if(current == first_node){
				prev = current;
				current = current->next;
				delete prev;
				first_node = current;
				prev = NULL;
			}
			else{
				if(current == last_node){
					prev->next = NULL;					
					delete current;
					current = NULL;
					last_node = prev;
				}
				else{
					prev->next = current->next;
					delete current;
					current = prev->next;
				}
			}
		}
		else{
			prev = current;
			current = current->next;
		}
	}

	return illegals;			//Return how many illegals have caught between this station and the previous one
}

Passenger_List::~Passenger_List(){
	Passenger_List_Node* current = first_node,*temp;

	while(current != NULL){						//Deleting the list
		temp = current;
		current = current->next;
		delete temp;
	}

	first_node = last_node = NULL;
}

Passenger_List::Passenger_List_Node::Passenger_List_Node(){         //Initialize the node

	Data = new Passenger(rand() % 2,rand() % 2);	//call the Passenger constructor
	next = NULL;
}

Passenger_List::Passenger_List_Node::~Passenger_List_Node(){
	delete Data;
}
