#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>

#include "Airport.h"

using namespace std;

void read_applications(Airport* const,ifstream&);	           //Reads all the application which are on the file
void read_flights(Airport* const,ifstream&,int,time_t);        //Reads the number of flights that is necessary to fill all
									           				   //the terminals

int main(int argc,char* argv[]){
	ifstream flights("airportData.txt");
	ifstream applications("applicationData.txt");

	Airport* airport;
	time_t operation_time;
	int no_of_terminals;

	if(!flights.is_open() || !applications.is_open()){  //If some file doesn't open
		cout<<"Failed to open files"<<endl;
		return -1;
	}

	if(argc != 2){
		cout<<"Wrong input"<<endl;
		return -1;
	}
	else{
		operation_time = atoi(argv[1]);
	}

	cout<<"Please give me the number of terminals"<<endl;
	cin>>no_of_terminals;

	srand(time(NULL));
	
	airport = new Airport(no_of_terminals);

	cout<<"Current time is "<<airport->get_time()<<" and the airport has "<<no_of_terminals<<" terminals"<<endl<<endl;

	read_flights(airport,flights,airport->get_available_terminals(),airport->get_time());   //Filling terminals
	read_applications(airport,applications);												//Reading all the applications

	while(1){

		if(airport->how_many_people_waiting() == 0 && airport->get_available_terminals() == no_of_terminals){
			cout<<"Airport departed all the flights and has served all the passengers"<<endl;
			break;
		}

		airport->show_timetable();
		cout<<endl;
		airport->show_people_waiting();
		cout<<endl;

		airport->flow_time(operation_time);

		airport->cancel_flight(rand()%(no_of_terminals));   //It will delete a random flight if at these number there is a terminal with a flight

		//I don't call cancel application because I test it in flow time

		read_flights(airport,flights,airport->get_available_terminals(),airport->get_time()); //Filling empty terminals
		airport->add_to_flight();															  //Adding congruous applications
	}																						  //to a proper flight

	delete airport;

	flights.close();
	applications.close();

	return 0;
}

void read_applications(Airport* const airport,ifstream& applications){
	//Reading all the applications and puts them in the waiting list or to a matching
	//flight via Airport::add_application()

	int ID;
	string FN,LN,dest;
	time_t tta,dtd;
	string econ_or_luxury;
	string temp;

	while(1){
		applications>>temp;

		if(applications.eof()) break;

		ID = atoi(temp.c_str());

		applications>>FN>>LN>>dest;

		applications>>temp;

		tta = (time_t) atoi(temp.c_str());

		applications>>temp;

		dtd = (time_t) atoi(temp.c_str());

		applications>>econ_or_luxury;

		airport->add_application(ID,FN,LN,dest,tta,dtd,econ_or_luxury);
	}
}

void read_flights(Airport* const airport,ifstream& flights,int available,time_t curr_time){

	string dest;
	time_t depart,duration;
	int max_A,max_B;
	string temp;

	for(int i=0;i < available;i++){
		flights >> dest;

		if(flights.eof()) break;

		flights >> temp;
		depart = (time_t) atoi(temp.c_str());

		flights >> temp;
		duration = (time_t) atoi(temp.c_str());

		flights >> temp;
		max_B = atoi(temp.c_str());

		flights >> temp;
		max_A = atoi(temp.c_str());


		if(curr_time < depart){
			airport->add_flight(dest,depart,duration,max_A,max_B);				
		}
		else{
			i--;
		}
	}	
}