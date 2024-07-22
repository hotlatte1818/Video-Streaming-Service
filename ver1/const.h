#ifndef CONST_H
#define CONST_H
#include <string>
#include <vector>

using std::string;
using std::vector;

enum direction			//Направление корабля (вертикальное или горизонтальное)
{
	DIR_HOR,
	DIR_VER
};	
 

struct Ship
{
	int x;			//x-координата левого верхнего угла корабля
	int y;			//y-координата левого верхнего угла корабля
	int len;		//длина
	direction dir;	//направление
};

struct Cell
{
	int x;
	int y;
};


#define DEBUG 1

// --------------- Константы и макросы ---------

#define FIELD_SIZE 10	//Размер поля

const extern vector<int> ship_types;




// -------------- Exception Class -------------
struct Error
{
	string err_txt;
};


enum cell_val			//Возможные значения клеток
{
	CELL_EMPTY,
	CELL_WOUND,
	CELL_KILL,
	CELL_SHIP,			//нетронутая клетка корабля
	CELL_UNKNOWN,
	CELL_MIN = CELL_EMPTY,
	CELL_MAX = CELL_UNKNOWN
};



enum game_st			//статус игры
{
	GAME_UNKNOWN,
	GAME_WIN,
	GAME_LOOSE
};

#endif		
