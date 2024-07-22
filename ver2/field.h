#ifndef FIELD_H
#define FIELD_H 

#include "common.h"

class Field
{
public:
	Field();
	~Field(){};

	//��������� ���� ��������� val
	void fill(cell_val val);						
	
	//    ������� ��� ������ � ��������
	status set_cell(int x, int y, cell_val val);
	cell_val get_cell(int x, int y) const;

private:
	status check_coord(int x) const;

	cell_val buf[FIELD_SIZE][FIELD_SIZE];
};

#endif