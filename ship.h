#ifndef SHIP_H
#define SHIP_H
#include "const.h"

class Cell
{
public:
	void set_x(int in_x);
	void set_y(int in_y);
	void set_val(cell_val in_val);
	int get_x() const;
	int get_y() const;
	cell_val get_val() const;	

private:
	int x;
	int y;
	cell_val val;
};


class Ship
{
public:
	void set_x(int in_x);
	void set_y(int in_y);
	void set_len(int in_len);
	void set_dir(direction in_dir);
	int get_x() const;
	int get_y() const;
	int get_len() const;
	direction get_dir() const;	
private:
	int x;			//x coordiname
	int y;			//y coordinate
	int len;		//length
	direction dir;	//direction
};

#endif