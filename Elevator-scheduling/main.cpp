#include "Elevator.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

const int MAX_INF = 0x3f3f3f3f;
const int MIN_INF = -0x3f3f3f3f;
int Cas = 1, num = 0;

Elevator Lift;
vector<Passenger> Men;
int nowtime = 0, nowfloor = 0;

int SCan( int time, int floor);
void Run();

void init()
{
	
	int num;
	
	nowtime = nowfloor = 0;
	cin >> num;
	
	for ( int i = 1; i <= num; i ++ )
	{
		
		Passenger now;
		
		cin >> now.asktime >> now.fromfloor >> now.tofloor;
		now.id = i;
		now.ind = now.fromfloor - now.tofloor > 0 ? 0 : 1;
		
		Men.push_back( now );
		
	}
	
}



// y is the former aim and x is the maybe target
int JudgeCan ( Passenger x, Passenger y, int ind, int time, int floor )
{
	
	if ( ind )
	{
		if ( x.fromfloor <= y.fromfloor
				   && x.asktime <= time + fabs( floor - x.fromfloor ) 
				   && !x.in )
			return 1;
		return 0;
	}
	else
	{
		if ( x.fromfloor >= y.fromfloor
					&& x.asktime <= time + fabs( floor - x.fromfloor )
					&& !x.in )
			return 1;
		return 0;
	}
	
}



Passenger findbetter( Passenger& x, int ind, int& time, int floor )
{
	
	int betterdown = MIN_INF;
	int betterup = MAX_INF;
	int mark = -1;
	
	
	for ( int i = 0; i < Men.size(); i ++ )
	{
		if ( ind )
		{
			if ( JudgeCan( Men[i], x, ind, time, floor ) )
			{
				if ( betterup > Men[i].fromfloor )
				{
					betterup = Men[i].fromfloor;
					mark = i;
				}
			}
		}
		else
		{
			if ( JudgeCan( Men[i], x, ind, time, floor ) )
			{
				if ( betterdown < Men[i].fromfloor )
				{
					betterdown = Men[i].fromfloor;
					mark = i;
				}
			}
		}
	}
	
	
	if ( ind ) 
	{
		if ( betterup != MAX_INF ) 
		{
			Lift.Catch( Men[mark] );
//			cout << " now catch in find id:" << Men[mark].id << endl;
			if ( SCan( time + fabs( floor - Men[mark].fromfloor ) , betterup) ) time += num;
			else 
			{
				time += fabs( floor - Men[mark].fromfloor );
				Lift.Print( time , Men[mark].fromfloor, Men[mark].id );
//				cout << "Before is pick expect scan and time:" << time << endl;
			}
			
			time ++;
			
		}
		else
		{
			
			Lift.Catch( x );
//			cout << " now catch in find id:" << x.id << endl;
			if ( SCan( time + fabs( floor - x.fromfloor ) , floor ) ) time += num;
			else 
			{
				time += fabs( floor - x.fromfloor );
				Lift.Print( time , x.fromfloor, x.id );
//				cout << "Before is pick expect scan and time" << time << endl;
			}
			
			time ++;
			
		}
		//return betterup == MIN_INF ? x.fromfloor : betterup;
	}
	else 
	{
		if ( betterdown != MIN_INF ) 
		{
			
			Lift.Catch( Men[mark] );
//			cout << " now catch in find id:" << Men[mark].id << endl;
			if ( SCan( time + fabs( floor - Men[mark].fromfloor ) , floor ) ) time += num;
			else 
			{
				time += fabs( floor - Men[mark].fromfloor );
				Lift.Print( time , Men[mark].fromfloor, Men[mark].id);
//				cout << "Brfore is pick expect scan and time:" << time << endl;
			}
			
			time ++;
			
		}
		else 
		{
			
			Lift.Catch( x );
//			cout << " now catch in find id:" << x.id << endl;
			if ( SCan( time + fabs( floor - x.fromfloor ) , floor ) ) time += num;
			else
			{
				time += fabs( floor - x.fromfloor );
				Lift.Print( time + fabs( floor - x.fromfloor ) , x.fromfloor, x.id );
//				cout << "Before is pick expect scan and time:" << time << endl;
			}
			
			time ++;
			
		}
//		return betterdown == MAX_INF ? x.fromfloor : betterdown;
	}
	
	/*cout << "Case:#" << Cas++ << " nowtime:" << time << endl;
	cout << "after findbetter time:" << time << endl;*/
	return mark == -1 ? x : Men[mark];
	
}



void choose( int ind, int& time, int& floor )
{
	
	int tmptime, nowsize;
	int maxtime = MAX_INF;
	
	for ( int i = 0; i < Men.size(); i ++ )
	{
		if ( !Men[i].in ) 
		{
			
			tmptime = time ;
			nowsize = Lift.contain;
			
			Passenger tmp = findbetter( Men[i], ind, tmptime, floor );

			
			tmptime += fabs( floor - tmp.fromfloor );
			
			SCan( tmptime, tmp.tofloor );
			
			if ( nowsize != Lift.contain )
			{
				if ( tmptime < maxtime )
				{
					maxtime = tmptime;
					nowfloor = tmp.fromfloor;
				}
				time += Lift.contain - nowsize;
				
				Run();
				
			}
			
		}
	}
	
	if ( maxtime != MAX_INF )
	{
		time += maxtime;
		floor = nowfloor;
	}
	
	
}



int SCan( int time, int floor )
{
	
	int flag = 0;
	num = 0;
	int isprt = 0;
	
//	cout << "scan time:" << time << " floor:" << floor << endl;
	for ( int i = 0; i < Men.size(); i ++ )
	{
		
		if ( Men[i].tofloor == floor && Men[i].in && !Men[i].endtravel )
		{
			
			flag = 1;
			num ++;
			
			Men[i].endtravel = 1;
			
			if ( !isprt ) 
			{
				Lift.Print( time, floor, Men[i].id );
				isprt = 1;
			}
			/*cout << "id:" << Men[i].id << " leave:" << Men[i].endtravel << endl;
			cout << " in scan to == floor" << endl;*/
			
			
		}
		
		
		if ( Men[i].fromfloor == floor && !Men[i].in && Men[i].asktime <= time )
		{
			
			flag = 1;
			num ++;
			
			if ( !isprt )
			{
				Lift.Print( time, floor, Men[i].id );
				isprt = 1;
			}
			Lift.Catch( Men[i] );
			/*cout << " now is scan catch id:" << Men[i].id << endl;
			cout << " in scan from == floor" << endl;*/
			
			
		}
	}

	return flag;
	
}

void Run()
{
	
	
	
	
	int iii = 0;
	while ( Lift.contain != 0 )
	{
		
		Passenger CurMan = Lift.GetMember();
		
		for ( int surp = 0; surp < Men.size(); surp ++ )
			if ( Men[surp].id == CurMan.id )
				CurMan.endtravel = Men[surp].endtravel;
				
		/*cout << "the head id:" << CurMan.id << " endtravel:" << CurMan.endtravel << endl;
		cout << "the head id of vec:" << Men[iii].id << " and the endtravel:" << Men[iii].endtravel << endl;
		cout << "now is contain:" << Lift.contain << endl;
		cout << "Case:#" << Cas++ << "---time:"<< nowtime << "  floor:" << nowfloor << " indicatoe:" << Lift.indicator << endl;*/
		
		Lift.Pop();
		
		
		if ( CurMan.Judge( nowfloor ) )
		{
			Lift.Print( nowtime, CurMan.tofloor, CurMan.id );
			nowtime ++;
		}
		else
		{
			nowtime += fabs( CurMan.tofloor - nowfloor );
			nowfloor = CurMan.tofloor;
			if ( CurMan.endtravel == 0 )
			{
				Lift.Print( nowtime, CurMan.tofloor, CurMan.id );
				CurMan.endtravel = 1;
			}
			nowtime ++;
		}
		
		/*if ( Lift.contain == 0 )
		{
			Lift.indicator = CurMan.ind ^ 1;
			choose( Lift.indicator, nowtime, nowfloor );
		}*/
		if ( Lift.indicator != Lift.GetMember().ind )
		{
			Lift.indicator = Lift.indicator ^ 1;
			choose(Lift.indicator, nowtime, nowfloor );
		}
		
	}
	
//	cout << "All passengers arrived. Success!" << endl; 
	
	
}



main()
{
	
	freopen( "input.txt",  "r", stdin  );
	freopen( "output.txt", "w", stdout );
	
	init();
	
	nowtime = nowfloor = 0;
	
	choose( 1, nowtime, nowfloor );
	
//	Run();

	fclose(stdin);
	fclose(stdout);
	
	return 0;
	
}
