#include "game.h"
#include <iostream>
#include <string>
#include <functional>
#include <vector>


using std::cin;
using std::cout;
using std::string;
using std::stoi;
using std::to_string;
using std::vector;
using std::reference_wrapper;

Game::Game()
{
	my_ships.fill(CELL_UNKNOWN);
	my_shoots.fill(CELL_UNKNOWN);
	en_shoots.fill(CELL_UNKNOWN);
	
	live_ships = ship_types;
	my_ship_cells = 0;
	
	int i;
	for(i=0;i<ship_types.size();i++)
	{
		my_ship_cells += ship_types[i];
	}
	en_ship_cells = my_ship_cells;
}

Game::~Game()
{
	
}

void Game::out_fields() const
{

	vector<Field> fields;

	fields.push_back(en_shoots);
	fields.push_back(my_shoots);
//	fields.push_back(my_ships);
	
	cout << endl;
	cout << "     Ваши выстрелы             Мои выстрелы               Мои корабли " << endl;
	print(fields);
	cout << endl;
}				

void Game::out_my_ships() const
{
	vector<Field> fields;
	
	fields.push_back(my_ships);
	
	cout << endl;
	cout << "     Мои корабли " << endl;
	print(fields);
	cout << endl;	
}

void Game::out_coord(const Cell& cell) const
{
	char c1,c2;
	
	c1 = 'a' + cell.x;
	c2 = '0' + cell.y;
	
	cout << "Мой ход: " << c1 << c2 << endl;	
}

Cell Game::in_coord()
{
	string str;
	char x,y;
	Cell cell;
	
	
	cout << "Ваш ход: ";
	
	
	while(1)
	{
		cin >> str;
		if(str.size()!=2)
		{
			cout << "Неверное значение" << endl;
		}
		else
		{
			x = str[0] - 'a';
			y = str[1] - '0';
			
			if(x < 0 || x > FIELD_SIZE || y < 0 || y > FIELD_SIZE)
			{
				cout << "Неверное значение" << endl;
				continue;
			}
			else
			{
				cell.x = (int)x;
				cell.y = (int)y;
				return cell;
			}
		}
	}
}	

void Game::out_val(cell_val val) const
{
	switch(val)
	{
		case CELL_EMPTY: cout << "Мимо" << endl; break;
		case CELL_WOUND: cout << "Ранил" << endl; break;
		case CELL_KILL: cout << "Убил" << endl; break;
		default:
		{
			Error err;
			err.err_txt = "Ошибка в функции Game::out_val. Недопустимое значение cell.getval() = " + to_string(val);
			throw(err);
		}
	}
}

cell_val Game::in_val()
{
	string str;
	int val = -1;
	
	cout << "Введите результат: (";
	cout << "Мимо: " << CELL_EMPTY << ", ";
	cout << "Ранил: " << CELL_WOUND << ", ";
	cout << "Убил: " << CELL_KILL << "): ";
	
	
	while(1)
	{
		cin >> str;
		try
		{
			val = stoi(str);
		}
		catch(...)
		{
			cout << "Неверное значение" << endl;
			continue;
		}
		if(val != CELL_EMPTY && val != CELL_WOUND && val != CELL_KILL)
		{
			cout << "Неверное значение" << endl;
		}
		else
			return (cell_val)val;
	};
	
}


void Game::init_ships()
{
	int i, j, val, len, psbl_count, select;
	vector<Ship> psbl;	//возможные расстановки кораблей
	Cell cell;
	Ship ship;
	
	srand(time(0));
	for(i=0;i<ship_types.size();i++)
	{
		len = ship_types[i];
		psbl = my_ships.get_all_psbl(len);
		psbl_count = psbl.size();		
		select = rand() % psbl_count;
		ship = psbl[select];
		my_ships.add_ship(ship, CELL_SHIP);
	}
	
	// Заполняет CELL_EMPTY вместо CELL_UNKNOWN
	for(i=0;i<FIELD_SIZE;i++)
		for(j=0;j<FIELD_SIZE;j++)
		{
			if(my_ships.get_cell(i,j) == CELL_UNKNOWN)
			{
				my_ships.set_cell(i,j,CELL_EMPTY);
			}
		}
}


Cell Game::shoot()
{
	Cell new_shoot;
	Cell wounded;
	
	if(my_shoots.get_wound(wounded))
		new_shoot = shoot_wounded(wounded.x, wounded.y);
	else
		new_shoot = shoot_new();
	
	return new_shoot;
}

Cell Game::shoot_new()
{
	int len; 			//длина самого большого корабля
	int i,j,k, psbl_count;
	vector<Ship> psbl;	//возможные расстановки кораблей
	Field F;
	Ship ship;
	cell_val val;
	Cell cell;
	int count[FIELD_SIZE][FIELD_SIZE];
	
	len = get_max_ship();
	for(j=0;j<FIELD_SIZE;j++)
		for(k=0;k<FIELD_SIZE;k++)
			count[j][k] = 0;

	psbl = my_shoots.get_all_psbl(len);
	psbl_count = psbl.size();		
	for(i=0;i<psbl_count;i++)
	{
		F.fill(CELL_EMPTY);
		ship = psbl[i];
		F.add_ship(ship, CELL_SHIP);
		for(j=0;j<FIELD_SIZE;j++)
			for(k=0;k<FIELD_SIZE;k++)
			{
				val = F.get_cell(j,k);
				if(val == CELL_SHIP)
					count[j][k]++;
			}
	}
	
	int max_val = 0;
	for(j=0;j<FIELD_SIZE;j++)
		for(k=0;k<FIELD_SIZE;k++)
		{
			if(count[j][k]>max_val)
			{
				max_val = count[j][k];
				cell.x = j;
				cell.y = k;
			}
		}
	
	return cell;
}	


Cell Game::shoot_wounded(int x, int y)
{
	bool is_hor = false, is_ver = false;
	
	Cell cell, tmp_cell;
	cell_val val;
	direction dir;
	
	// ---- проверяем есть ли еще ранения------
	if(my_shoots.get_left(x,y) == CELL_WOUND || my_shoots.get_right(x,y) == CELL_WOUND)
		is_hor = 1;
	
	if(my_shoots.get_up(x,y) == CELL_WOUND || my_shoots.get_down(x,y) == CELL_WOUND)
		is_ver = 1;
	


	//проверяем корректность
	if(is_hor && is_ver)
	{
		Error err;
		err.err_txt = "Ошибка в функции Game::shoot_old. Крестообразный корабль";
		throw(err);		
	}
	
	// ---------------- выбираем клетку ----------
	if(is_hor)
	{	
		while(my_shoots.get_left(x,y) == CELL_WOUND) // двигаемся влево
			x--;
		if(my_shoots.get_left(x,y) == CELL_UNKNOWN)
		{
			x--;
			cell.x = x;
			cell.y = y;
			return cell;
		}
		
		while(my_shoots.get_right(x,y) == CELL_WOUND) // двигаемся вправо
			x++;
		if(my_shoots.get_right(x,y) == CELL_UNKNOWN)
		{
			x++;
			cell.x = x;
			cell.y = y;
			return cell;
		}

		Error err;
		err.err_txt = "Ошибка в функции Game::shoot_old. Невозможно убить горизонтальный корабль";
		throw(err);		
	}
	else if(is_ver)						//вертикальный корабль
	{
		while(my_shoots.get_up(x,y) == CELL_WOUND) // двигаемся влево
			y--;
		if(my_shoots.get_up(x,y) == CELL_UNKNOWN)
		{
			y--;
			cell.x = x;
			cell.y = y;
			return cell;
		}
		
		while(my_shoots.get_down(x,y) == CELL_WOUND) // двигаемся вправо
			y++;
		if(my_shoots.get_down(x,y) == CELL_UNKNOWN)
		{
			y++;
			cell.x = x;
			cell.y = y;
			return cell;
		}

		Error err;
		err.err_txt = "Ошибка в функции Game::shoot_old. Невозможно убить вертикальный корабль";
		throw(err);		
	}
	else		// неизвестно направление корабля
	{
		if(my_shoots.get_left(x,y) == CELL_UNKNOWN)
		{
			cell.x = x-1;
			cell.y = y;
			return cell;
		}
		else if(my_shoots.get_right(x,y) == CELL_UNKNOWN)
		{
			cell.x = x+1;
			cell.y = y;
			return cell;
		}
		else if(my_shoots.get_up(x,y) == CELL_UNKNOWN)
		{
			cell.x = x;
			cell.y = y-1;
			return cell;
		}
		else if(my_shoots.get_down(x,y) == CELL_UNKNOWN)
		{
			cell.x = x;
			cell.y = y+1;
			return cell;
		}

		else
		{
			Error err;
			err.err_txt = "Ошибка в функции Game::shoot_old. Ранен одноклеточный корабль";
			throw(err);		

		}
	}

	
}


void Game::update(int x, int y, cell_val val)
{
	int len;
	
	if(val == CELL_EMPTY)
		my_shoots.set_cell(x,y,val);
	else if(val == CELL_WOUND)
	{
		my_shoots.set_cell(x,y,val);
		en_ship_cells --;
	}
	else if(val == CELL_KILL)
	{
		len = my_shoots.kill(x,y);
		del_ship(len);
		en_ship_cells --;
	}
	else
	{
		Error err;
		err.err_txt = "Ошибка в функции Game::update. Недопустимое значение val = " + to_string(val);
		throw(err);
	
	}
}
	
cell_val Game::check(int x, int y)
{
	int res;
	cell_val val;
	Ship ship;
	
	val = my_ships.get_cell(x,y);
	
	if(val == CELL_EMPTY)
	{
		en_shoots.set_cell(x,y,val);
		return CELL_EMPTY;
	}
	else if(val == CELL_SHIP || val == CELL_WOUND)
	{
		my_ship_cells --;
		my_ships.set_cell(x,y,CELL_WOUND);
		res = my_ships.check_killed(x,y,ship);
		
		if(res == true)
		{
			en_shoots.add_ship(ship,CELL_KILL);
			return CELL_KILL;
		}
		else
		{
			en_shoots.set_cell(x,y,CELL_WOUND);
			return CELL_WOUND;
		}
		
	}
	else
	{
		Error err;
		err.err_txt = "Ошибка в функции Game::update. Недопустимое значение val = " + to_string(val);
		throw(err);
	
	}
}	

int Game::get_max_ship() const
{
	int i,num,len=0;
	
	num = live_ships.size();
	for(i=0;i<num;i++)
	{
		if(live_ships[i]>len)
			len = live_ships[i];
	}
	return len;
}

void Game::del_ship(int len)
{
	int i,num;
	
	num = live_ships.size();
	for(i=0;i<num;i++)
	{
		if(live_ships[i] == len)
		{
			live_ships[i] = 0;
			return;
		}
	}
	
	Error err;
	err.err_txt = "Ошибка в функции Game::del_ship. Недопустимое невозможно удалить корабль с длиной " + to_string(len);
	throw(err);

}

game_st Game::get_status()
{
	 if(my_ship_cells <=0)
	 {
		 cout << "Вы выиграли!" << endl;
		 return GAME_LOOSE;
	 }
	 else if(en_ship_cells <=0)
	 {
		 cout << "Вы проиграли!" << endl;
		 return GAME_WIN;
	 }
	 
	 return GAME_UNKNOWN;

}
