#include <iostream>

#include "Application.h"
#include "Flight.h"

using namespace std;

Flight::Flight(const string dest,time_t depart,time_t dur,int max_A,int max_B,int terminal_number):
destination(dest),departure_time(depart),duration(dur),max_seats_A(max_A),
max_seats_B(max_B),remaining_seats_A(max_A),remaining_seats_B(max_B),terminal_no(terminal_number)
{
	//Blank Body, I initialized the necessary fields and the curr_passengers list will be empty
}

Flight::Flight(const Flight& other): destination(other.destination),
departure_time(other.departure_time),duration(other.duration),max_seats_A(other.max_seats_A),
max_seats_B(max_seats_B),remaining_seats_A(other.remaining_seats_A),remaining_seats_B(other.remaining_seats_B),
terminal_no(other.terminal_no)
{
	curr_passengers = other.get_bookings(); // Because the list contains pointers
											//I make another copy and not bit by bit 
											//copy 
}

int Flight::add_passenger(const Application& application){
	Application* applctn = new Application(application);

	if(application.matches(*this)){						//If the application matches with the flight
		if(application.is_luxury_class()){				//and if there is a seat available
			if(remaining_seats_A > 0){					//I will pudh back the application
				remaining_seats_A--;
				curr_passengers.push_back(applctn);
				return 1;
			}
		}
		else{
			if(remaining_seats_B > 0){
				remaining_seats_B--;
				curr_passengers.push_back(applctn);
				return 1;
			}
		}
	}

	delete applctn;

	return 0;
}

int Flight::cancel_reservations(int ID){

	int cancelled_Applications = 0;

	for(list<Application*>::iterator it = curr_passengers.begin(); it != curr_passengers.end();){

		list<Application*>::iterator temp;

		if((*it)->get_ID() == ID){
			cancelled_Applications++;
			if((*it)->is_luxury_class()){
				remaining_seats_A++;
			}
			else{
				remaining_seats_B++;
			}
			
			temp = it;
			it++;
			delete *temp;					//delete the object
			curr_passengers.erase(temp);    //if I call only erase() I will have memory leak
										    //because only the pointer will be deleted and not
											//the application object that points to it
		}
		else{
			it++;
		}
	}

	return cancelled_Applications;
}

list<Application*>&  Flight::get_bookings() const{      //Does not return the bit by bit copy 
	list<Application*> new_list;			 		  //because If I do that I will probably
											          //try to delete something twice and get "Abort" error

	for(list<Application*>::const_iterator it = curr_passengers.begin(); it != curr_passengers.end(); it++){
		new_list.push_back(new Application(**it));
	}

	return new_list;
}

Flight::~Flight(){

	list<Application*>::const_iterator temp;

	for(list<Application*>::const_iterator it = curr_passengers.begin(); it != curr_passengers.end();){
		temp = it;
		it++;
		delete *temp;					//I explain why I do this at Flight::cancel_reservations()

		//I don't call list.erase because the pointers will be deleted automatically
		//by the destructor of list
	}

	//The rest fields will be deleted automatically because their scope ends
}
