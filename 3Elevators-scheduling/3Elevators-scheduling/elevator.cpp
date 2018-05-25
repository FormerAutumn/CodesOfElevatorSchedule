#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
#include "elevator.h"
using namespace std;


Passenger::Passenger()
{
	wait_time = 0;
	in = out = 0;
}
Passenger::~Passenger(){}


int print_1, print_2, print_3;

Elevator_3::Elevator_3()
{
	dir_E = 1;
	cur_time = cur_floor = 0;
	sum_men = 0;
}
Elevator_3::~Elevator_3(){}

void Elevator_3::Print( int cur_time, int cur_floor, int name, Passenger now, char* argv[] )
{
	//判断在哪个文件输出 
	if ( name == 1 )
	{
		print_1 ++;
		if ( print_1 == 1 ) freopen(argv[2], "w", stdout);
		else freopen(argv[2], "a", stdout);
		cout << cur_time << " " << cur_floor << endl; //<< now.id << endl;
	}
	if ( name == 2 )
	{
		print_2 ++;
		if ( print_2 == 1 ) freopen(argv[3], "w", stdout);
		else freopen(argv[3], "a", stdout);
		cout << cur_time << " " << cur_floor << endl; //<< now.id << endl;
	}
	if ( name == 3 )
	{
		print_3 ++;
		if ( print_3 == 1 ) freopen(argv[4], "w", stdout);
		else freopen(argv[4], "a", stdout);
		cout << cur_time << " " << cur_floor << endl; //<< now.id << endl;
	}
}

//本来为到达某指定楼层与抓取某一乘客，后并无使用 
/*void Elevator_3::Run( int cur_time, int cur_floor, Passenger now )
{
	cur_time += fabs( cur_floor - now.aim_floor );
	cur_floor = now.aim_floor;
}

void Elevator_3::Catch( Passenger &cur_man, int dir_P , int name)
{
	if ( dir_P ) up.push(cur_man);
	else down.push(cur_man);
}*/

//该乘客是否符合进入电梯条件 
int Elevator_3::pick( int cur_time, int cur_floor, Passenger now )
{
	if ( cur_time >= now.ask_time
		&& cur_floor == now.ask_floor
		&& !now.in ) return 1;
	return 0;
}

//该乘客是否已经由电梯送达目的地 
int Elevator_3::send( int cur_floor, Passenger now )
{
	if ( cur_floor == now.aim_floor
		&& now.in && !now.out ) return 1;
	return 0;
}

//扫描请求，并且运行电梯 
void Elevator_3::Scan( int cur_time, int cur_floor, int dir_E, int name, char* argv[] )
{
	int cnt_out = 0;
	
	
	print_1 = print_2 = print_3 = 0;

	int flag = 0;
	//判断电梯当前是否需要移动，1==移动， 0==静止 等待下个（波）请求 
	
	Passenger tmp_man;
	tmp_man.id = -1;
		
	while ( 1 )
	{	
//		int tmp_time = cur_time;
//		int cnt_1 = 0, cnt_2 = 0;
//		int tmp_max = 1, tmp_min = 10;
		//cnt_1 cnt the num of passenger who can't get in lift curtime
		//cnt_2 cnt the num of passenger who doesn't in lift
		
		
		for ( int i = 0; i < All.size(); i ++ )
		{
			//如果当前时间比请求时间大，电梯随即开始准备移动 
			if ( !All[i].in && All[i].ask_time <= cur_time )
			{
//				cout << "now is : " << cur_time << endl;
				flag = 1;
			}
			
//			如果当前乘客可以抓取（进入电梯） ，便抓取并进行相应操作（标记、输出、加时间、加电梯内总人数） 
			if ( pick(cur_time, cur_floor, All[i]) )
			{
				if ( tmp_man.id == -1 ) tmp_man = All[i];
//				tmp_man为电梯中最先进入的乘客，如果其id==-1说明其已出电梯，可以向下一个人的需求移动 
				All[i].in = 1;
				Print( cur_time, cur_floor, name, All[i], argv );
				cur_time ++;
				sum_men ++;
			}
//			如果当前乘客已由电梯送达目的地，进行相应操作（标记、输出、加时间、加输出总人数） 
			else if ( send( cur_floor, All[i]) )
			{
				All[i].out = 1;
				Print( cur_time, cur_floor, name, All[i], argv );
				cur_time ++;
				cnt_out ++;
				sum_men --;
			}
		}
		
		if ( cnt_out == All.size() ) break;
//		如果已经出电梯的人等于总人数，那么结束运行 
		
		/*if ( cnt_1 != cnt_2 )
		{
			cur_floor = ( cur_floor + 1 ) % tmp_max;
			if ( !cur_floor ) cur_floor = tmp_max; 
		}
		else if ( cnt_1 == cnt_2 && cnt_1 == 0 )
		{
			cur_floor = ( cur_floor + 1 ) % tmp_max;
			if ( !cur_floor ) cur_floor = tmp_max;
		}*/
		if ( flag )
		{
			dir_E = tmp_man.dir_P;
//			拿到当前乘客的运动方向 
			
			if ( dir_E )
			{
				cur_floor ++;
//				如果达到了目的地，更新tmp_nan和flag，下同 
				if ( cur_floor == tmp_man.aim_floor )
				{
//					dir_E ^= 1;
					tmp_man.id = -1;
					flag = 0;
				}
			}
			else
			{
				cur_floor --;
				if ( cur_floor == tmp_man.aim_floor )
				{
//					dir_E ^= 1;
					tmp_man.id = -1;
					flag = 0;
				}
			}
		}
		cur_time ++;	
	}
}

/*int btw( int cur_floor, Passenger a, Passenger b, int dir )
{
	if ( dir_E )
	{
		if ( b.ask_floor >= cur_floor && b.ask_floor <= a.ask_floor )
			return 1; 
	}
	else
	{
		if ( b.ask_floor <= cur_floor && b.ask_floor >= a.ask_floor )
			return 1; 
	}
	return 0;
}*/


