#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <fstream>
#include "elevator.h"
using namespace std;

Elevator_3 Lift_1, Lift_2, Lift_3;

//Lift_1 odd 
//Lift_2 any
//Lift_3 1 and even

//vector<Passenger> v_1, v_2, v_3;

void Get( int n )
{
	for ( int i = 0; i < n; i ++ )
	{
		Passenger now;
		cin >> now.ask_time >> now.ask_floor >> now.aim_floor;
		if ( now.ask_floor > now.aim_floor ) now.dir_P = 0;
										else now.dir_P = 1;
		now.id = i + 1;
										
		if ( now.ask_floor % 2 && now.aim_floor % 2 )
		{
			Lift_1.All.push_back(now);
		}
		else if ( 
					(now.ask_floor % 2 == 0 && now.aim_floor % 2 == 0)
					|| (now.ask_floor == 1 && now.aim_floor % 2 == 0)
			   		|| (now.ask_floor % 2 == 0 && now.aim_floor == 1) 
				)
		{
			Lift_3.All.push_back(now);
		}
		else
		{
			Lift_2.All.push_back(now);
		}
	}
}

int judge( int argc )
{
	/*if ( argc == 0 )
	{
		cout << "There is no operations" << endl;
		return 0;
	} 
	else*/ if ( argc == 1 )
	{
		cout << "There is no input which should like:input.txt..." << endl;
		return 0; 
	}
	else if ( argc < 5 )
	{
		cout << "There lack some output txt" << endl;
		return 0;
	}
}

int main( int argc, char* argv[] )
{
	
	if ( !judge(argc) ) return 0;
	
	ifstream fin(argv[1]);
	if ( !fin )
	{
		cout << "There is no such txt exist, it's name:" << argv[1] << endl;
		return 0;
	}
	
	argv[2] = "output1.txt"; argv[3] = "output2.txt"; argv[4] = "output3.txt";
	freopen(argv[1], "r", stdin);
	int n;
	cin >> n;
	
	Get(n);
	
	/*cout << Lift_1.All.size() << endl;
	cout << Lift_2.All.size() << endl;
	cout << Lift_3.All.size() << endl;*/
	
//	如果该电梯的需求数组不为空，则运行该电梯 
	if ( Lift_1.All.size() != 0 )
		Lift_1.Scan( 0, 1, 1, 1, argv );
	else
	{
		freopen(argv[2], "w", stdout);
		
		fclose(stdout);
	}
		
	if ( Lift_2.All.size() != 0 )
		Lift_2.Scan( 0, 1, 1, 2, argv );
	else
	{
		freopen(argv[3], "w", stdout);
		
		fclose(stdout);
	}
		
	if ( Lift_3.All.size() != 0 )
		Lift_3.Scan( 0, 1, 1, 3, argv );
	else
	{
		freopen(argv[4], "w", stdout);
		
		fclose(stdout);
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}

/*

5
1 2 3
7 8 9
10 6 4
15 7 3
19 1 10

2
1 1 2
1 2 1

*/
