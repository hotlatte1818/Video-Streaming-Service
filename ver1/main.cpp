#include "game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using std::srand;
using std::time;

int main()
{
	Game game;
	Cell my_shoot, en_shoot;
	cell_val my_res, en_res;
	
	try
	{
		game.init_ships();
		
		while(1)
		{
			do // Наш выстрел
			{
				game.out_fields();		
				my_shoot = game.shoot();		
				game.out_coord(my_shoot);		
				my_res = game.in_val();
				game.update(my_shoot.x, my_shoot.y, my_res);
				if(game.get_status() == GAME_WIN)
					exit(0);
				
			}while (my_res == CELL_WOUND || my_res == CELL_KILL);

		
			do // Выстрел соперника
			{
				game.out_fields();
				en_shoot = game.in_coord();		
				en_res = game.check(en_shoot.x, en_shoot.y);
				game.out_val(en_res);		
				if(game.get_status() == GAME_LOOSE)
					exit(0);
				
			}while (en_res == CELL_WOUND || en_res == CELL_KILL);
		}
	}
	
	catch(Error err)
	{
		cout << "Сбой в программе: " << err.err_txt << endl;
	}
	
	return 0;
}