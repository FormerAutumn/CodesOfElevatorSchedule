#include <queue>
#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;


class Passenger
{
	
	public:
			
			Passenger();
			~Passenger();
			int Judge( int floor );

			
			int fromfloor, tofloor;
			int asktime, usetime;
			int in;
			int ind;
			int id;
			int endtravel;
		
};


class Elevator
{
	
	public:
	
			Elevator();
			~Elevator();
			
			
			queue<Passenger> DestQueue;
			int curfloor, indicator;
			int sumtime;
			int contain;

			
			Passenger GetMember();
			void Print( int time, int floor, int id );
			void Pop();
			void Catch( Passenger& x );
	
};




