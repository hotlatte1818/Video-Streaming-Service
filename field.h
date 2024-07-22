#ifndef FIELD_H
#define FIELD_H 

#include <iostream>
#include <functional>
#include "const.h"

using std::ostream;
using std::cout;
using std::endl;
using std::vector;
using std::reference_wrapper;



class Field
{
public:
	Field();
	~Field(){};

	//Заполняет поле значением val
	void fill(cell_val val);						
	
	//    Функции для работы с клетками
	void set_cell(int x, int y, cell_val val);
	cell_val get_cell(int x, int y) const;
	cell_val get_right(int x, int y) const;
	cell_val get_left(int x, int y) const;
	cell_val get_up(int x, int y) const;
	cell_val get_down(int x, int y) const;
	
	//    Функции для работы с кораблями
	bool check_ship(const Ship& ship) const;				//true если корабль может быть размещен	
	vector<Ship> get_all_psbl(int len) const;				//возвращает все валидные варианты размещения корабля длины len
	void add_ship(const Ship &ship, cell_val val);			//добавляет корабль на поле со значениями val	
	bool check_killed(int x, int y, Ship &ship) const;		//Проверяет, убит ли корабль. Если убит, до возвращает его параметры в ship
	int kill(int x, int y);									//Оформляет убитый корабль, возвращает его длину
	
	// вывод на экран
	friend void print(const vector<Field> fields);	//Выводит на экран поля
	
	// вспомогательные функции
	bool get_wound(Cell &cell);						//Находит клетку CELL_WOUND, если такая есть

private:
	void check_coord(int x) const;

	cell_val buf[FIELD_SIZE][FIELD_SIZE];
};




#endif