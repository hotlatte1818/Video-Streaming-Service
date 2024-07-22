#include "arbitr.h"
#include <iostream>
using std::cout;
using std::endl;

Arbitr::Arbitr()
{
	unsigned int i,j;
	ship_cells = 0;
	
	for(i=0;i<FIELD_SIZE;i++)
		for(j=0;j<FIELD_SIZE;j++)
		{
			field1[i][j] = CELL_UNKNOWN;
			field2[i][j] = CELL_UNKNOWN;
		}
		
	for(i=0;i<ship_types.size();i++)
	{
		ship_cells += ship_types[i];
	}
	
	killed1 = killed2 = 0;
}

status Arbitr::check_p1_cell(Cell cell)
{
	if(cell.x < 0 || cell.x > FIELD_SIZE || cell.y < 0 || cell.y > FIELD_SIZE)
		return ST_FAIL;
	else
		return ST_OK;
}

status Arbitr::check_p1_val(Cell cell, cell_val val)
{
	return check_val(cell, val, field1, killed1);
}

status Arbitr::check_p1_lose()
{
	if(killed1 >= ship_cells)
		return ST_END;
	else
		return ST_OK;
}

status Arbitr::check_p2_cell(Cell cell)
{
	if(cell.x < 0 || cell.x > FIELD_SIZE || cell.y < 0 || cell.y > FIELD_SIZE)
		return ST_FAIL;
	else
		return ST_OK;	
}

status Arbitr::check_p2_val(Cell cell, cell_val val)
{
	return check_val(cell, val, field2, killed2);
}

status Arbitr::check_p2_lose()
{
	if(killed2 >= ship_cells)
		return ST_END;
	else
		return ST_OK;
}

status Arbitr::check_val(Cell cell, cell_val val, cell_val (&field)[FIELD_SIZE][FIELD_SIZE], int &killed)
{
	if(cell.x < 0 || cell.x > FIELD_SIZE || cell.y < 0 || cell.y > FIELD_SIZE)
		return ST_FAIL;

	if(val != CELL_EMPTY && val != CELL_WOUND && val != CELL_KILL)
		return ST_FAIL;
	
	
	if(field[cell.x][cell.y] == CELL_UNKNOWN)
	{
		field[cell.x][cell.y] = val;
	}
	
	if(field[cell.x][cell.y] != val)
		return ST_FAIL;
	else
	{
		if(val == CELL_WOUND || val == CELL_KILL)
			killed ++;
		
		return ST_OK;
	}
}
  