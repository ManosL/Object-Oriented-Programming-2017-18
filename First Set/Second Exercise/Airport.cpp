#include <iostream>
#include <fstream>
#include <cstdlib>


#include "Airport.h"
#include "Application.h"
#include "Flight.h"


using namespace std;

void swap_ptr(Flight*& f1,Flight*& f2){
	Flight* temp;
	temp = f1;
	f1 = f2;
	f2 = temp;

	return;
}

Airport::Airport(int terminals): current_time(0),no_of_terminals(terminals),
cancelled_applications(0),available_terminals(no_of_terminals)
{
	for(int i = 0;i<no_of_terminals;i++){						//Initialize terminals
		(this->terminals).push_back(NULL);
	}
}

void Airport::flow_time(time_t time_units){     		//The terminals and the waiting list are full

	for(int i = 1;i <= time_units;i++){					//For each time unit

		for(int j = 0;j < no_of_terminals;j++){
			if(terminals[j] != NULL && terminals[j]->departs_at() == current_time){				//the flight departs with all its passengers
				list<Application*> passengers = terminals[j]->get_bookings();

				cout<<"A flight with destination "<<terminals[j]->get_destination()<<" has departed"<<endl;

				if(passengers.size() > 0)
					cout<<"The passengers are "<<endl;
				else{
					cout<<"Doesn't have any passengers"<<endl;
				}

				for(list<Application*>::iterator it = passengers.begin();it != passengers.end();it++){   //Prints the passengers
					cout<<(*it)->get_name()<<endl;
				}
				cout<<endl;

				delete terminals[j];						//deletes the flight
				terminals[j] = NULL;
				available_terminals++;				

				for(list<Application*>::iterator it = passengers.begin();it != passengers.end();){   //Traverses the list to find 
					list<Application*>::iterator temp;												 //if a passenger done extras 
																									 //applications and deletes them
					cancel_applications((*it)->get_ID());
					temp = it;
					it++;
					delete *temp;
				}				
			}
		}

		for(list<Application*>::iterator it = WaitingList.begin();it != WaitingList.end();){  //I traverse the waiting list
			list<Application*>::iterator temp;

			if(current_time > (*it)->arrived_by()){ 	  //If the current time is bigger than the desirable time to destination	
				temp = it;								  //delete the application
				it++;
				delete *temp;
				WaitingList.erase(temp);
				cancelled_applications++;
			}
			else{
				it++;
			}
		}
		
		current_time++;		
	}

	return;
}   

void Airport::add_application(int ID,const string FN,const string LN,const string dest,time_t tta,time_t dtd,const string type){
	Application* applct = new Application(ID,FN,LN,dest,tta,dtd,type);

	for(int i = 0;i < no_of_terminals;i++){
		if(terminals[i] != NULL){
			if(terminals[i]->add_passenger(*applct)){	//If the application entered successfully to a flight
				delete applct;							//because at add passenger I make another copy
				return;
			}
		}
	}

	WaitingList.push_back(applct);					//If the application doesn't entered to a flight
													//it will go to the waiting list

	return;
}

void Airport::cancel_applications(int ID){
	list<Application*>::iterator temp;

	for(list<Application*>::iterator it = WaitingList.begin();it != WaitingList.end();){   //Checks the waiting list
		if((*it)->get_ID() == ID){
			cancelled_applications++;
			temp = it;
			it++;
			delete *temp;
			WaitingList.erase(temp);
		}
		else{
			it++;
		}
	}

	for(int i = 0;i < no_of_terminals;i++){			//Checks if I find an application with the same ID in a flight 
		if(terminals[i] != NULL)
			cancelled_applications += terminals[i]->cancel_reservations(ID); //this function returns the number of
																			//applications that cancelled when they are
																			//on a flight
	}

	return;
}

int Airport::add_flight(const string dest,time_t depart,time_t dur,int max_A,int max_B){   //I already checked if there is a terminal available

	for(int i=0;i<no_of_terminals;i++){            //Search for the first empty terminal and add the flight
		if(terminals[i] == NULL){
			available_terminals--;
			terminals[i] = new Flight(dest,depart,dur,max_A,max_B,i);

			return i;
		}
	}
}

void Airport::cancel_flight(int terminal_no){
	if(terminal_no >= no_of_terminals || terminal_no < 0 || terminals[terminal_no] == NULL){ //If the value of terminal_no is invalid
		return;
	}

	list<Application*> temp = terminals[terminal_no] -> get_bookings();    //I get the bookings list of that flight

	temp.splice(temp.end(),WaitingList);       //I put its elements in front of the waiting list

	WaitingList = temp;

	cout<<"Flight to "<<terminals[terminal_no]->get_destination()<<" cancelled"<<endl<<endl;

	delete terminals[terminal_no];

	terminals[terminal_no] = NULL;

	available_terminals++;

	return;
}

void Airport::show_timetable(){
	time_t min_departure_time,min_pos,curr_departure_time;
	int available_B,available_A;
	vector<Flight*> temp = terminals;    //I have a copy of the terminals vector because I don't
										 //want a permanent change of this vector

	if(available_terminals == no_of_terminals){
		cout<<"There aren't any flights at terminals"<<endl;
		return;
	}

	for(int i = 0;i < no_of_terminals;i++){                   //sorting the flights with selection sort
		if(temp[i] != NULL){
			curr_departure_time = temp[i]->departs_at();
			min_departure_time = curr_departure_time;
			min_pos = i;
		}
		else{
			min_departure_time = 100000000000;
			min_pos = i;
		}	

		for(int j = i+1;j < no_of_terminals;j++){
			if(temp[j] != NULL && temp[j]->departs_at() < min_departure_time){
				min_departure_time = temp[j]->departs_at();
				min_pos = j;
			}
		}

		swap_ptr(temp[i],temp[min_pos]);
	}

	cout<<"The next flights are"<<endl;						//printing all the flights that are on terminals
	for(int i = 0;i < no_of_terminals;i++){
		if(temp[i] != NULL){
			temp[i]->get_available(available_A,available_B);

			cout<<"Terminal "<<temp[i]->get_terminal_no() + 1<<" ";
			cout<<temp[i]->get_destination()<<" "<<temp[i]->departs_at()<<" ";
			cout<<temp[i]->arrives_at()<<" "<<available_A<<" "<<available_B<<endl;
		}
	}

	cout<<endl<<"Available Flights are"<<endl;				//printing the available flights
	for(int i = 0;i < no_of_terminals;i++){
		if(temp[i] != NULL){
			temp[i]->get_available(available_A,available_B);
			if(available_A > 0 || available_B > 0){
				cout<<"Terminal "<<temp[i]->get_terminal_no() + 1<<" ";
				cout<<temp[i]->get_destination()<<" "<<temp[i]->departs_at()<<" ";
				cout<<temp[i]->arrives_at()<<" "<<available_A<<" "<<available_B<<endl;
			}
		}
	}

	return;
}

void Airport::show_people_waiting() const{

	if(WaitingList.size() == 0){
		cout<<"There aren't any passengers on the waiting list"<<endl;
		return;
	}

	cout<<"The passenger with this names are on the waiting list"<<endl;

	for(list<Application*>::const_iterator it = WaitingList.begin(); it != WaitingList.end(); it++){
		cout<<(*it)->get_name()<<endl;
	}
}


void Airport::add_to_flight(){				//Adds people fron waiting list to a matching flight
	list<Application*>::iterator temp;
	int flag = 0;

	for(list<Application*>::iterator it = WaitingList.begin();it != WaitingList.end();){
		flag = 0;

		for(int i = 0;i < no_of_terminals;i++){
			if(terminals[i] != NULL){
				if(terminals[i]->add_passenger(**it)){			//If the application added to flight
					temp = it;									//it will be deleted from waiting list
					it++;
					flag = 1;
					delete *temp;
					WaitingList.erase(temp);
					break;
				}
			}
		}

		if(flag == 0) it++;
	}
}

Airport::~Airport(){						//Destroys the airport

	for(int i = 0;i < no_of_terminals;i++){
		delete terminals[i];
	}

	list<Application*>::iterator temp;
	for(list<Application*>::iterator it = WaitingList.begin();it != WaitingList.end();){
		temp = it;
		it++;
		delete *temp;
	}
}