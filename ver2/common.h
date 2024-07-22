#ifndef COMMON_H
#define COMMON_H
#include <string>
#include <vector>

using std::vector;
using std::string;

#define FIELD_SIZE 10
const extern vector<int> ship_types;

struct Cell
{
	int x;
	int y;
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

enum status
{
	ST_FAIL = -1,
	ST_OK = 0,
	ST_END
};

// -------------- Exception Class -------------
struct Error
{
	string err_txt;
};


#endif