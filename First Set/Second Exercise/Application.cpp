#include <iostream>

#include "Application.h"
#include "Flight.h"

using namespace std;

Application::Application(int ID,const string FN,const string LN,const string dest,time_t tta,time_t dtd,const string type):
passenger_ID(ID),first_name(FN),last_name(LN),destination(dest),time_to_airport(tta),
desirable_time_to_destination(dtd),economical_or_luxury(type)
{
	//Blank body, I initialized the necessary fields
}

Application::Application(const Application& other):passenger_ID(other.passenger_ID),first_name(other.first_name),
last_name(other.last_name),destination(other.destination),time_to_airport(other.time_to_airport),
desirable_time_to_destination(other.desirable_time_to_destination),economical_or_luxury(other.economical_or_luxury)
{
	//Blank body, I copied all the fields
}

int Application::matches(const Flight& flight) const{	//just checks the details of the application and not if I have an available seat
	return ( (destination == flight.get_destination()) && (time_to_airport < flight.departs_at()) && ( desirable_time_to_destination >= flight.arrives_at()));
}

string Application::get_name() const{
	string returned_str(first_name);

	returned_str += " ";
	returned_str += last_name;

	return returned_str;
}

Application::~Application(){
	//Blank body, doesn't need to delete them because 
	//the fields will get automatically deleted
	//because their scope ends
}

