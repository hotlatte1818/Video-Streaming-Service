#ifndef ARBITR_H
#define ARBITR_H
#include "common.h"

class Arbitr
{
public:
	Arbitr();
	status check_p1_cell(Cell cell);
	status check_p1_val(Cell cell, cell_val val);
	status check_p1_lose();

	status check_p2_cell(Cell cell);
	status check_p2_val(Cell cell, cell_val val);
	status check_p2_lose();	

private:
	status check_val(Cell cell, cell_val val, cell_val (&field)[FIELD_SIZE][FIELD_SIZE], int &killed);

	cell_val field1[FIELD_SIZE][FIELD_SIZE];
	cell_val field2[FIELD_SIZE][FIELD_SIZE];
	int ship_cells;									//Количество клеток, занятых кораблями
	int killed1;									//Количество убитых/раненых клеток у игрока 1
	int killed2;									//Количество убитых/раненых клеток у игрока 1
};

#endif