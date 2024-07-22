#include "field.h"

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

status Field::check_coord(int x) const
{
	if(x < 0 || x >= FIELD_SIZE)
		return ST_FAIL;
	else
		return ST_OK;
}

status Field::set_cell(int x, int y, cell_val val)
{
	if(check_coord(x) == ST_FAIL || check_coord(y) == ST_FAIL)
		return ST_FAIL;
	else
	{
		buf[x][y] = val;
		return ST_OK;
	}
}

cell_val Field::get_cell(int x, int y) const
{
	if(check_coord(x) == ST_FAIL || check_coord(y) == ST_FAIL)
		return CELL_EMPTY;
	else
		return buf[x][y];
}

