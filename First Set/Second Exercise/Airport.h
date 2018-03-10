#ifndef __AIRPORT__
#define __AIRPORT__

#include <list>
#include <vector>
#include <string>


class Flight;
class Application;

class Airport{

private:
	time_t current_time;
	int no_of_terminals,available_terminals;
	int cancelled_applications;
	std::vector<Flight*> terminals;
	std::list<Application*> WaitingList;

public:
	Airport(int);
	void flow_time(time_t);
	void add_application(int,const std::string,const std::string,const std::string,time_t,time_t,const std::string);
	void cancel_applications(int);
	int add_flight(const std::string,time_t,time_t,int,int);
	void cancel_flight(int);
	void show_timetable();
	void add_to_flight();
	void show_people_waiting() const;
	inline int how_many_people_waiting(){ return WaitingList.size(); }	
	inline int failed_applications() const{ return cancelled_applications; }
	inline time_t get_time() const{ return current_time; }
	inline int get_available_terminals() const{ return available_terminals; }
	~Airport();

};

#endif