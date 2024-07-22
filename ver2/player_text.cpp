#include "player.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#define MAX_READ_BUF 100

using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::cin;

Cell Player_Text::ask_cell()
{
	char x,y;
	Cell cell;
	string str;
	
	print("Ваш ход: ");

	while(1)
	{
		str = scan();
		
		if(str.size()!=2)
		{
			print("Неверное значение\n");
			print("Ваш ход: ");
			continue;
		}

		x = str[0] - 'a';
		y = str[1] - '0';
		
		if(x < 0 || x > FIELD_SIZE || y < 0 || y > FIELD_SIZE)
		{
			print("Неверное значение\n");
			print("Ваш ход: ");
			continue;
		}
		else
		{
			cell.x = (int)x;
			cell.y = (int)y;
			return cell;
		}
		
	}
}

cell_val Player_Text::ask_val(Cell cell) 
{
	string str;
	int val;
	
	string xstr(1,'a' + cell.x);
	string instr = "Введите результат (Мимо: " + to_string(CELL_EMPTY) + 
		", Ранил: " + to_string(CELL_WOUND) + 
		", Убил: " + to_string(CELL_KILL) + "): ";
	
	print("Противник сходил: " + xstr + to_string(cell.y) + "\n");
	print(instr);
	
	while(1)
	{
		str = scan();

		if(str.size()!=1)
		{
			print("Неверное значение\n");
			print(instr);
			continue;
		}

		val = str[0] - '0';
		
		if(val != CELL_EMPTY && val != CELL_WOUND && val != CELL_KILL)
		{
			print("Неверное значение\n");
			print(instr);
		}
		else
		{
			en_shoots.set_cell(cell.x, cell.y, (cell_val)val);
			print_fields();
			return (cell_val)val;
		}

	};
}

void Player_Text::send_val(Cell cell, cell_val val)
{	
	
	if(val != CELL_EMPTY && val != CELL_WOUND && val != CELL_KILL)
	{
		Error err;
		err.err_txt = "Ошибка в функции Player_Text::send_val. Недопустимое значение val = " + to_string(val);
		throw(err);
	}
	
	my_shoots.set_cell(cell.x, cell.y, (cell_val)val);
	print_fields();
	
	switch(val)
	{
		case CELL_EMPTY: print("Мимо\n"); break;
		case CELL_WOUND: print("Ранил\n"); break;
		case CELL_KILL: print("Убил\n"); break;
		default: break;
	}
}

void Player_Text::bad_cell(Cell cell)
{

}
	
void Player_Text::bad_val(Cell cell, cell_val val)
{
	print("Неверное значение\n");
}
	
void Player_Text::win()
{
	print("Вы выиграли!\n");
}
	
void Player_Text::lose()
{
	print("Вы проиграли!\n");
}

void Player_Text::print_field_line(const Field &f,int n)
{
	int j;
	cell_val val;
	
	print(to_string(n) + " ");
	for(j=0;j<FIELD_SIZE;j++)
	{
		val = f.get_cell(j,n);
		switch(val)
		{
			case CELL_EMPTY: print("- "); break;
			case CELL_WOUND: print("+ "); break;
			case CELL_KILL: print("X "); break;
			case CELL_SHIP: print("S "); break;
			case CELL_UNKNOWN: print(". "); break;
			default: print("? ");
		}
	}
}

void Player_Text::print_fields()
{
	int i;

	print("     Ваши выстрелы          Выстрелы соперника \n");
	print("  a b c d e f g h i j       a b c d e f g h i j\n");
	
	for(i=0;i<FIELD_SIZE;i++)
	{
		print_field_line(my_shoots, i);
		print("    ");
		print_field_line(en_shoots, i);
		print("\n");
	}
	
	print("\n");
}


//----------------- Player_TCP ------------

Player_TCP::Player_TCP(int port_num)
{
	socklen_t addrlen;
	struct sockaddr_in server, client;
	int ret;
	
	port = port_num;
	
	srv_sock = socket(AF_INET, SOCK_STREAM, 0);	
	if (srv_sock == -1)
	{
		Error err;
		err.err_txt = "Ошибка в функции Player_TCP::Player_TCP. Невозможно открыть сокет";
		throw(err);
	}
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);
	
	ret = bind(srv_sock,(struct sockaddr*)&server,sizeof(server));
	if (ret == -1)
	{
		Error err;
		err.err_txt = "Ошибка в функции Player_TCP::Player_TCP. Ошибка bind";
		throw(err);
	}
	
	ret = listen(srv_sock, 1);
	if (ret == -1)
	{
		Error err;
		err.err_txt = "Ошибка в функции Player_TCP::Player_TCP. Ошибка listen";
		throw(err);
	}
	
	addrlen = sizeof(client);
	cl_sock = accept(srv_sock, (struct sockaddr*)&client, &addrlen);
	if (cl_sock == -1)
	{
		Error err;
		err.err_txt = "Ошибка в функции Player_TCP::Player_TCP. Ошибка accept";
		throw(err);
	}

	close(srv_sock);
}

Player_TCP::~Player_TCP()
{
	close(cl_sock);
}


void Player_TCP::print(string msg)
{
	write(cl_sock, msg.c_str(), msg.size());
}

string Player_TCP::scan()
{
	int len;
	char buf[MAX_READ_BUF];
	len = read(cl_sock, buf, sizeof(buf));

	string str(buf,len-2);
	return str;
}

// ----------------- Player_Console ---------------
void Player_Console::print(string msg)
{
	cout << msg;
}

string Player_Console::scan()
{
	string str;
	cin >> str;
	
	return str;
}