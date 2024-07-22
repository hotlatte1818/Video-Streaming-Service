#include "field.h"
#include <stdlib.h>
#include <string>

using std::string;
using std::to_string;

Field::Field()
{
	fill(CELL_UNKNOWN);
}

void Field::fill(cell_val val)
{
	int i,j;
	for(i=0;i<FIELD_SIZE;i++)
		for(j=0;j<FIELD_SIZE;j++)
			buf[i][j] = val;
}

void Field::check_coord(int x) const
{
	if(x < 0 || x >= FIELD_SIZE)
	{
		Error err;
		err.err_txt = "Ошибка в функции Field::check_coord. Недопустимое значение x = " + to_string(x);
		throw(err);		
	}
}

void Field::set_cell(int x, int y, cell_val val)
{
	check_coord(x);
	check_coord(y);
	buf[x][y] = val;
}

cell_val Field::get_cell(int x, int y) const
{
	check_coord(x);
	check_coord(y);

	return buf[x][y];
}

cell_val Field::get_right(int x, int y) const
{
	check_coord(x);
	check_coord(y);

	if(x == FIELD_SIZE-1)
		return CELL_EMPTY;
	else
		return buf[x+1][y];
}

cell_val Field::get_left(int x, int y) const
{
	check_coord(x);
	check_coord(y);
	
	if(x == 0)
		return CELL_EMPTY;
	else
		return buf[x-1][y];
}

cell_val Field::get_up(int x, int y) const
{
	check_coord(x);
	check_coord(y);

	if(y == 0)
		return CELL_EMPTY;
	else
		return buf[x][y-1];
}

cell_val Field::get_down(int x, int y) const
{
	check_coord(x);
	check_coord(y);

	if(y == FIELD_SIZE-1)
		return CELL_EMPTY;
	else
		return buf[x][y+1];
}



void print(const vector<Field> fields)
{
	int i,j,k;
	cell_val val;
	char c;
	Field current;

	if(fields.size()==0)
		return;

	for(k=0;k<fields.size();k++)
		cout << "  a b c d e f g h i j     ";
	cout << endl;
	
	for(i=0;i<FIELD_SIZE;i++)
	{
		for(k=0;k<fields.size();k++)
		{
			cout << i << " ";
			current = fields[k];
			for(j=0;j<FIELD_SIZE;j++)
			{
				val = current.get_cell(j,i);
				switch(val)
				{
					case CELL_EMPTY: c = '-'; break;
					case CELL_WOUND: c = '+'; break;
					case CELL_KILL: c = 'X'; break;
					case CELL_SHIP: c = 'S'; break;
					case CELL_UNKNOWN: c = '.'; break;
					default: c = '?';
				}
				cout << c << " ";
			}
			cout << "    ";
		}
		cout << endl;
	}
		
}

bool Field::check_ship(const Ship& ship) const
{
	int i,j,x,y,len;
	direction dir;
	
	x = ship.x;
	y = ship.y;
	len = ship.len;
	dir = ship.dir;
	
	if(x<0 || y<0 || x>=FIELD_SIZE || y>=FIELD_SIZE)
		return false;
	
	if(dir == DIR_HOR)
 	{
		if(x+len > FIELD_SIZE)
			return false;
		
 		for(i=x;i<x+len;i++)
 			if(buf[i][y] != CELL_UNKNOWN) 
				return false;
 	}
 	else
 	{
		if(y+len > FIELD_SIZE)
			return false;

 		for(j=y;j<y+len;j++)
 			if(buf[x][j] != CELL_UNKNOWN) 
				return false;
 	}
	return true;
}

vector<Ship> Field::get_all_psbl(int len) const
{
	vector<Ship> psbl;
	Ship ship;
	int i,j;
	
	ship.len = len;
	
	for(i=0;i<FIELD_SIZE;i++)
		for(j=0;j<FIELD_SIZE;j++)
		{	
			ship.x = i;
			ship.y = j;

			ship.dir = DIR_HOR;
			if(check_ship(ship))
				psbl.push_back(ship);

			ship.dir = DIR_VER;
			if(check_ship(ship))
				psbl.push_back(ship);					
		}
		
	return psbl;
}

void Field::add_ship(const Ship& ship, cell_val val)
{
	int x,y,len,i,j;
 	direction dir;	
 	int xmin, ymin, xmax, ymax;

	x = ship.x;
	y = ship.y;
	len = ship.len;
	dir = ship.dir;
	
 	if(x==0) 
 		xmin = 0;
 	else
 		xmin = x-1;
 	
 	if(y==0) 
 		ymin = 0;
 	else
 		ymin = y-1;
 	
 	if(dir == DIR_HOR)
 	{
 		if(x+len == FIELD_SIZE)
 			xmax = x+len-1;
 		else
 			xmax = x+len;
 		
 		if(y == FIELD_SIZE-1)
 			ymax = y;
 		else
 			ymax = y+1;
 	}
 	else
 	{
 		if(x == FIELD_SIZE-1)
 			xmax = x;
 		else
 			xmax = x+1;
 		
 		if(y+len == FIELD_SIZE)
 			ymax = y+len-1;
 		else
 			ymax = y+len;
 	}
	
 	//    set empty sells
 	for(i=xmin;i<=xmax;i++)
 		for(j=ymin;j<=ymax;j++)
 				buf[i][j] = CELL_EMPTY;
 		
 			
 	//  set ship 
 	if(dir == DIR_HOR)
 	{
 		for(i=x;i<x+len;i++)
 			buf[i][y] = val;
 	}
 	else
 	{
 		for(j=y;j<y+len;j++)
 			buf[x][j] = val;
 	}

}


bool Field::check_killed(int x, int y, Ship &ship) const
{
	int tmp_x, tmp_y;
	int ship_x, ship_y, len;
	bool is_hor = false, is_ver = false;
	direction dir;
	
	
	if(buf[x][y] != CELL_SHIP && buf[x][y] != CELL_WOUND)
		return false;
	
	ship_x = x; ship_y = y, len = 1; dir = DIR_HOR;
	
	// проверяем слева
	tmp_x = x; tmp_y = y;
	while(get_left(tmp_x, tmp_y) != CELL_EMPTY  && get_left(tmp_x, tmp_y) != CELL_UNKNOWN)
	{
		tmp_x--;
		if(buf[tmp_x][tmp_y] == CELL_SHIP)
			return false;
		ship_x--;
		len ++;
		is_hor = true;
	}
	
	// проверяем справа
	tmp_x = x; tmp_y = y;
	while(get_right(tmp_x, tmp_y) != CELL_EMPTY  && get_right(tmp_x, tmp_y) != CELL_UNKNOWN)
	{
		tmp_x++;
		if(buf[tmp_x][tmp_y] == CELL_SHIP)
			return false;
		len ++;
		is_hor = true;
	}
	
	
	// проверяем сверху
	tmp_x = x; tmp_y = y;
	while(get_up(tmp_x, tmp_y) != CELL_EMPTY && get_up(tmp_x, tmp_y) != CELL_UNKNOWN)
	{
		tmp_y--;
		if(buf[tmp_x][tmp_y] == CELL_SHIP)
			return false;
		ship_y--;
		len ++;
		dir = DIR_VER;
		is_ver = true;
	}
	
	
	// проверяем снизу
	tmp_x = x; tmp_y = y;
	while(get_down(tmp_x, tmp_y) != CELL_EMPTY && get_down(tmp_x, tmp_y) != CELL_UNKNOWN)
	{
		tmp_y++;
		if(buf[tmp_x][tmp_y] == CELL_SHIP)
			return false;
		len ++;
		dir = DIR_VER;
		is_ver = true;
	}

	if(is_hor && is_ver)
	{
		Error err;
		err.err_txt = "Ошибка в функции Field::check_killed. Крестообразный корабль";
		throw(err);
	}
	
	
	ship.x = ship_x;
	ship.y = ship_y;
	ship.len = len;
	ship.dir = dir;
	return true;	
}


int Field::kill(int x, int y)
{	
	Ship ship;
	buf[x][y] = CELL_WOUND;
	if(check_killed(x,y,ship) == false)
	{
		Error err;
		err.err_txt = "Ошибка в функции Field::kill. Невозможно убить корабль";
		throw(err);
	}
	
	add_ship(ship,CELL_KILL);
	return ship.len;
}


bool Field::get_wound(Cell &cell)
{
	int i,j;
	
	for(i=0;i<FIELD_SIZE;i++)
		for(j=0;j<FIELD_SIZE;j++)
		{
			if(buf[i][j] == CELL_WOUND)
			{
				cell.x = i;
				cell.y = j;
				return true;
			}
		}
		
	return false;
}
