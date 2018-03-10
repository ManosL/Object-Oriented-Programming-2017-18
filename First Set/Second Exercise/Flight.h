#ifndef __FLIGHT__
#define __FLIGHT__

#include <list>
#include <string>


class Application;

class Flight{

private:
	const std::string destination;
	const time_t departure_time;
	const time_t duration;
	const int max_seats_A,max_seats_B;
	const int terminal_no;
	int remaining_seats_A,remaining_seats_B;
	std::list<Application*> curr_passengers;

public:
	Flight(const std::string,time_t,time_t,int,int,int);
	Flight(const Flight&);       //copy constructor
	int add_passenger(const Application&);
	int cancel_reservations(int);
	std::list<Application*> get_bookings() const;
	inline time_t departs_at() const{ return departure_time; }
	inline time_t arrives_at() const{ return (departure_time + duration); }
	inline std::string get_destination() const{ return destination; }
	inline int get_terminal_no() const{ return terminal_no; }
	inline void get_available(int& available_A,int& available_B) const{ available_A = remaining_seats_A; available_B = remaining_seats_B; }
	~Flight();
};

#endif