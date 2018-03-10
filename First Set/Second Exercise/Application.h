#ifndef __APPLICATION__
#define __APPLICATION__

#include <ctime>
#include <string>


class Flight;
class Application{

private:
	const int passenger_ID;
	const std::string first_name;
	const std::string last_name;
	const std::string destination;
	const time_t time_to_airport;
	const time_t desirable_time_to_destination;
	const std::string economical_or_luxury;

public:
	Application(int,const std::string,const std::string,const std::string,time_t,time_t,const std::string);
	Application(const Application&);         //copy constructor
	int matches(const Flight&) const;
	std::string get_name() const;
	inline int get_ID() const{ return passenger_ID; }
	inline time_t arrived_by() const{ return desirable_time_to_destination; }
	inline int is_luxury_class() const{ return economical_or_luxury == "A"; }
	~Application();

};

#endif