#ifndef ENUMERATOR_H
#define ENUMERATOR_H

#include <vector>
#include <iostream>

using std::vector;
using std::ostream;

/*
	Class for enumeration of array of states
*/

class Enumerator
{ 
public:
	Enumerator(int states_num, int max_val);	//number of states (0 - states_num-1), each of which has max values (0 - max-1) or -1 if state missing
	~Enumerator(){};

/*
	is_good - is current configuration good
	return 0 if change not last state (partial configuration)
	return 1 if change last state (full configuration)
	return 2 if complited whole cicle.
*/
	int next(bool is_good);			
	vector<int> get();
	void set(int index, int val);
	
	friend ostream& operator<<(ostream& out, const Enumerator& en);

private:
	int move(int n);	//move n-th state, return most left moved state number

	vector<int> states;
	int num;
	int max;
	int cur_index;
};


#endif