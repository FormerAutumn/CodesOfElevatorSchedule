#include "Elevator.h"
#include <queue>
#include <cstring>
#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;


// Some function of Passenger

Passenger:: Passenger()
{
	fromfloor = tofloor = 0;
	asktime = usetime = 0;
	endtravel = 0;
	in = 0;
	ind = 1;
	id = -1;
}

Passenger:: ~Passenger(){}

int Passenger:: Judge( int floor )
{
	
	if ( ind )
	{
		if ( tofloor <= floor && !endtravel )
		{
		
			endtravel = 1;
			in = 0;
		
			return 1;
		}
		else return 0;
	}
	else
	{
		if ( tofloor >= floor && !endtravel )
		{
			
			endtravel = 1;
			in = 0;
			
			return 1;
		}
		else return 0;
		
	}
	
	
		
}



// Some functions of Elevator

Elevator:: Elevator()
{
	
	curfloor = sumtime = contain = 0;
	indicator = 1;
	while ( !DestQueue.empty() ) DestQueue.pop();
	
}

Elevator:: ~Elevator(){}


void Elevator:: Print( int time, int floor, int id )
{
	cout << time << " " << floor /*<< " ID:" << id*/ << endl;
	//contain --;
}


Passenger Elevator:: GetMember()
{
	return DestQueue.front();
}


void Elevator:: Pop()
{
	DestQueue.pop();
	contain --;
}


void Elevator:: Catch( Passenger& x )
{
	
	x.in = 1;
	DestQueue.push( x );
	contain ++;
	
}

