#include <iostream>
#include <vector>
#include "field.h"
#include "game.h"

using std::cout;
using std::vector;
using std::reference_wrapper;

void test_field_set_get();
void test_print();
void test_game_init_ships();
void test_field_kill();

int main() 
{

	
	try
	{
	//	test_print();
	//	test_field_set_get();
	//test_game_init_ships();
	test_field_kill();
	
	}
	
	catch(Error err)
	{
		cout << "Сбой в программе: " << err.err_txt << endl;
	}

}
/*
void test_game_out_my_ships()
{
	Game game;
	game.out_my_ships();
}
*/

void test_field_set_get()
{
	Field f;
	f.fill(CELL_UNKNOWN);

	//проверяем левый верхний угол
	f.set_cell(0,0,CELL_SHIP);
	f.set_cell(0,1,CELL_KILL);
	f.set_cell(1,0,CELL_WOUND);
	if(f.get_cell(0,0) != CELL_SHIP || 
		f.get_left(0,0) != CELL_EMPTY ||
		f.get_right(0,0) != CELL_WOUND ||
		f.get_up(0,0) != CELL_EMPTY ||
		f.get_down(0,0) != CELL_KILL)
	{
		cout << "test_field_set_get, левый верхний угол: FAIL" << endl;
		return;
	}
	
	//проверяем правый верхний угол
	f.set_cell(FIELD_SIZE-1,0,CELL_SHIP);
	f.set_cell(FIELD_SIZE-1,1,CELL_KILL);
	f.set_cell(FIELD_SIZE-2,0,CELL_WOUND);
	if(f.get_cell(FIELD_SIZE-1,0) != CELL_SHIP || 
		f.get_left(FIELD_SIZE-1,0) != CELL_WOUND ||
		f.get_right(FIELD_SIZE-1,0) != CELL_EMPTY ||
		f.get_up(FIELD_SIZE-1,0) != CELL_EMPTY ||
		f.get_down(FIELD_SIZE-1,0) != CELL_KILL)
	{
		cout << "test_field_set_get, правый верхний угол: FAIL" << endl;
		return;
	}

	//проверяем левый нижний угол
	f.set_cell(0,FIELD_SIZE-1,CELL_SHIP);
	f.set_cell(0,FIELD_SIZE-2,CELL_KILL);
	f.set_cell(1,FIELD_SIZE-1,CELL_WOUND);
	if(f.get_cell(0,FIELD_SIZE-1) != CELL_SHIP || 
		f.get_left(0,FIELD_SIZE-1) != CELL_EMPTY ||
		f.get_right(0,FIELD_SIZE-1) != CELL_WOUND ||
		f.get_up(0,FIELD_SIZE-1) != CELL_KILL ||
		f.get_down(0,FIELD_SIZE-1) != CELL_EMPTY)
	{
		cout << "test_field_set_get, левый нижний угол: FAIL" << endl;
		return;
	}

	//проверяем правый нижний угол
	f.set_cell(FIELD_SIZE-1,FIELD_SIZE-1,CELL_SHIP);
	f.set_cell(FIELD_SIZE-1,FIELD_SIZE-2,CELL_KILL);
	f.set_cell(FIELD_SIZE-2,FIELD_SIZE-1,CELL_WOUND);
	if(f.get_cell(FIELD_SIZE-1,FIELD_SIZE-1) != CELL_SHIP || 
		f.get_left(FIELD_SIZE-1,FIELD_SIZE-1) != CELL_WOUND ||
		f.get_right(FIELD_SIZE-1,FIELD_SIZE-1) != CELL_EMPTY ||
		f.get_up(FIELD_SIZE-1,FIELD_SIZE-1) != CELL_KILL ||
		f.get_down(FIELD_SIZE-1,FIELD_SIZE-1) != CELL_EMPTY)
	{
		cout << "test_field_set_get, правый нижний угол: FAIL" << endl;
		return;
	}

	cout << "test_field_set_get: OK" << endl;
}


void test_print()
{
	Field f1;
	int i;
	vector<Field> fields;
		
	for(i = CELL_MIN ; i<=CELL_MAX; i++)
	{
		f1.set_cell(i,0,(cell_val)i);
	}
	
	fields.push_back(f1);
	fields.push_back(f1);
	fields.push_back(f1);
		
	print(fields);
}

void test_game_init_ships()
{
	Game g;
	g.init_ships();
	g.out_my_ships();
}

void test_field_kill()
{
	Field f;
	f.fill(CELL_EMPTY);
	vector<Field> fields;
	Ship ship;
	
	f.set_cell(0,0,CELL_WOUND);
	f.set_cell(0,1,CELL_WOUND);
	f.set_cell(0,2,CELL_SHIP);
	fields.push_back(f);
	
	f.kill(0,2);
	fields.push_back(f);
		
	print(fields);
	
	f.set_cell(0,3,CELL_SHIP);
	if(f.check_killed(0,2,ship) == true)
	{
		cout << "test_field_check_killed: FAIL" << endl;
		return;
	}

	cout << "test_field_check_killed: OK" << endl;	
}
