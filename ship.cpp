#include <iostream>
#include <stdlib.h>
#include "ship.h"

using std::cout;
using std::to_string;

void Cell::set_x(int in_x)
{
	if(in_x < 0 || in_x >= FIELD_SIZE)
	{
		Error err;
		err.err_txt = "Ошибка в функции Cell::set_x. Недопустимое значение in_x = " + to_string(in_x);
		throw(err);		
	}
	x = in_x;
}

void Cell::set_y(int in_y)
{
	if(in_y < 0 || in_y >= FIELD_SIZE)
	{
		Error err;
		err.err_txt = "Ошибка в функции Cell::set_y. Недопустимое значение in_y = " + to_string(in_y);
		throw(err);		
	}
	y = in_y;
}

void Cell::set_val(cell_val in_val)
{
	if(in_val <= CELL_MIN || in_val >= CELL_MAX)
	{
		Error err;
		err.err_txt = "Ошибка в функции Cell::set_val. Недопустимое значение in_val = " + to_string(in_val);
		throw(err);
	}
	val = in_val;	
}

int Cell::get_x() const
{
	return x;
}

int Cell::get_y() const
{
	return y;
}

cell_val Cell::get_val() const
{
	return val;
}	


// --------------------- Ship ----------------------

void Ship::set_x(int in_x)
{
	if(in_x<0 || in_x>=FIELD_SIZE)
	{
		Error err;
		err.err_txt = "Ошибка в функции Ship::set_x. Недопустимое значение in_x = " + to_string(in_x);
		throw(err);		
	}
	
	x = in_x;
}

void Ship::set_y(int in_y)
{
	if(in_y<0 || in_y>=FIELD_SIZE)
	{
		Error err;
		err.err_txt = "Ошибка в функции Ship::set_y. Недопустимое значение in_y = " + to_string(in_y);
		throw(err);		
	}
	
	y = in_y;

}

void Ship::set_len(int in_len)
{
	if(in_len<1 || in_len>FIELD_SIZE)
	{
		Error err;
		err.err_txt = "Ошибка в функции Ship::set_len. Недопустимое значение in_len = " + to_string(in_len);
		throw(err);		
	}
	
	len = in_len;
}

void Ship::set_dir(direction in_dir)
{
	dir = in_dir;
}

int Ship::get_x() const
{
	return x;
}

int Ship::get_y() const
{
	return y;
}

int Ship::get_len() const
{
	return len;
}

direction Ship::get_dir() const
{
	return dir;
}	

