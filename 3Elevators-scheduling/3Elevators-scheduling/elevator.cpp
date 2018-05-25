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
	//�ж����ĸ��ļ���� 
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

//����Ϊ����ĳָ��¥����ץȡĳһ�˿ͣ�����ʹ�� 
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

//�ó˿��Ƿ���Ͻ���������� 
int Elevator_3::pick( int cur_time, int cur_floor, Passenger now )
{
	if ( cur_time >= now.ask_time
		&& cur_floor == now.ask_floor
		&& !now.in ) return 1;
	return 0;
}

//�ó˿��Ƿ��Ѿ��ɵ����ʹ�Ŀ�ĵ� 
int Elevator_3::send( int cur_floor, Passenger now )
{
	if ( cur_floor == now.aim_floor
		&& now.in && !now.out ) return 1;
	return 0;
}

//ɨ�����󣬲������е��� 
void Elevator_3::Scan( int cur_time, int cur_floor, int dir_E, int name, char* argv[] )
{
	int cnt_out = 0;
	
	
	print_1 = print_2 = print_3 = 0;

	int flag = 0;
	//�жϵ��ݵ�ǰ�Ƿ���Ҫ�ƶ���1==�ƶ��� 0==��ֹ �ȴ��¸����������� 
	
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
			//�����ǰʱ�������ʱ��󣬵����漴��ʼ׼���ƶ� 
			if ( !All[i].in && All[i].ask_time <= cur_time )
			{
//				cout << "now is : " << cur_time << endl;
				flag = 1;
			}
			
//			�����ǰ�˿Ϳ���ץȡ��������ݣ� ����ץȡ��������Ӧ��������ǡ��������ʱ�䡢�ӵ������������� 
			if ( pick(cur_time, cur_floor, All[i]) )
			{
				if ( tmp_man.id == -1 ) tmp_man = All[i];
//				tmp_manΪ���������Ƚ���ĳ˿ͣ������id==-1˵�����ѳ����ݣ���������һ���˵������ƶ� 
				All[i].in = 1;
				Print( cur_time, cur_floor, name, All[i], argv );
				cur_time ++;
				sum_men ++;
			}
//			�����ǰ�˿����ɵ����ʹ�Ŀ�ĵأ�������Ӧ��������ǡ��������ʱ�䡢������������� 
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
//		����Ѿ������ݵ��˵�������������ô�������� 
		
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
//			�õ���ǰ�˿͵��˶����� 
			
			if ( dir_E )
			{
				cur_floor ++;
//				����ﵽ��Ŀ�ĵأ�����tmp_nan��flag����ͬ 
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


