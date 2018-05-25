#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

class Elevator_3;
struct cmp_up;
struct cmp_down;

class Passenger
{
	friend Elevator_3;
	friend cmp_up;
	friend cmp_down;
	
	private:
				
				int wait_time;
				
				
	public:
				int in, out;
				//in the lift(in), arrive the aim_floor(out)
				int ask_time;
				int ask_floor, aim_floor;
				int dir_P;
				int id;
				
				Passenger();
				~Passenger();
};

struct cmp_up
{
	bool operator () (Passenger a, Passenger b)
	{
		if ( a.aim_floor == b.aim_floor )
			return a.ask_time > b.ask_time;
		return a.aim_floor < b.aim_floor;
	}
};
struct cmp_down
{
	bool operator () (Passenger a, Passenger b)
	{
		if ( a.aim_floor == b.aim_floor )
			return a.ask_time > b.ask_time;
		return a.aim_floor > b.aim_floor;
	}
};

class Elevator_3
{
	private:
				int dir_E;
				//dir
				int cur_time, cur_floor;
				//lastest time and floor
				int sum_men;
				
				priority_queue< Passenger, vector<Passenger>, cmp_up > up;
				//when the lift up, find max floor
				priority_queue< Passenger, vector<Passenger>, cmp_down > down;
				//when the lift down, find min floor
				queue<Passenger> normal_que;
				
				int pick( int cur_time, int cur_floor, Passenger now );
				int send( int cur_floor, Passenger now );
				//judge whether the lift arrives ask_floor or aim_floor or not
				
				void Catch( Passenger &cur_man, int dir_P, int name );
				//catch someone in
				void Print( int cur_time, int cur_floor, int name, Passenger now, char* argv[] );
				
	public:
				vector<Passenger> All;
				//all information of passengers
		
				Elevator_3();
				~Elevator_3();
				void Scan( int cur_time, int cur_floor, int dir_E, int name, char* argv[] );
				//decide where to go and how to go 
				void Run( int cur_time, int cur_floor, Passenger now );
				//goto somefloor to pick up someone or send someone
				
				
				//void Get( int n );
				//get all information of passenger
};
