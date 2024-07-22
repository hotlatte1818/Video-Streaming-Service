#include "player.h"
#include "arbitr.h"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
	
	Cell cell;
	cell_val val;
	status res;
	int winner;
		
	try
	{
		Player_Console Player1;
//		Player_TCP Player1(2001);
		cout << "Подключился первый игрок" << endl;
		Player_TCP Player2(2002);
		cout << "Подключился второй игрок" << endl;
		Arbitr arb;

		
		while(1)
		{
			//  стреляет первый игрок
			do
			{
				do
				{
					cell = Player1.ask_cell();
					res = arb.check_p1_cell(cell);
					if(res == ST_FAIL)
						Player1.bad_cell(cell);
				}while(res == ST_FAIL);
				
				do
				{
					val = Player2.ask_val(cell);
					res = arb.check_p2_val(cell,val);
					if(res == ST_FAIL)
						Player2.bad_val(cell,val);
				}while(res == ST_FAIL);
	
				Player1.send_val(cell, val);
				res = arb.check_p2_lose();
			}while(val != CELL_EMPTY && res !=ST_END);
			if(res == ST_END)
			{
				Player1.win();
				Player2.lose();
				winner = 1;
				break;
			}
	
		
			//  стреляет второй игрок
			do
			{
				do
				{
					cell = Player2.ask_cell();
					res = arb.check_p2_cell(cell);
					if(res == ST_FAIL)
						Player2.bad_cell(cell);
				}while(res == ST_FAIL);
				
				do
				{
					val = Player1.ask_val(cell);
					res = arb.check_p1_val(cell,val);
					if(res == ST_FAIL)
						Player1.bad_val(cell,val);
				}while(res == ST_FAIL);
	
				Player2.send_val(cell, val);
				res = arb.check_p1_lose();
			}while(val != CELL_EMPTY && res !=ST_END);
			if(res == ST_END)
			{
				Player2.win();
				Player1.lose();
				winner = 2;
				break;
			}
		}
		
		cout << "Победил игрок " << winner << endl;
	}

	
	catch(Error err)
	{
		cout << "Сбой в программе: " << err.err_txt << endl;
	}
} 
