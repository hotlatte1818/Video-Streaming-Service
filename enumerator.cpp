#include "enumerator.h"
#include <vector>
#include <stdlib.h>

using std::vector;
using std::ostream;
using std::cout;
using std::endl;

Enumerator::Enumerator(int states_num, int max_val)
{
	int i;
	
	for(i=0;i<states_num;i++)
		states.push_back(-1);
	
	max = max_val-1;
	num = states_num-1;
	cur_index = 0;
	
	states[0] = 0;
	
}

int Enumerator::move(int n)
{
	int i;
	
	if(states[n]<max)
	{
		states[n]++;
		return n;
	}
	
	n--;
	while(n>=0 && states[n]==max)
		n--;
	
	
	if(n==-1)	//whole cicle
	{
		states[0] = 0;
		for(i=1;i<=num;i++)
			states[i] = -1;
		return -1;
	}
	
	states[n]++;
	for(i=n+1;i<=num;i++)
		states[i] = -1;
	return n;	
}

int Enumerator::next(bool is_good)
{
	cout << "good=" << is_good << ", cur=" << cur_index << "  ";
	int res;
	
	if(is_good == true)
	{
		if(cur_index < num)
		{
			cur_index++;
			states[cur_index] = 0;
		}
		else
		{
			res = move(cur_index);
			if(res == -1)
			{
				cur_index = 0;
				return 2;
			}
			else
				cur_index = res;
		}
	}
	else
	{
		res = move(cur_index);
		if(res == -1)
		{
			cur_index = 0;
			return 2;
		}
		else
			cur_index = res;
	}
	
	
	if(cur_index == num)
		return 1;
	else
		return 0;
}

vector<int> Enumerator::get()
{
	return states;
}

void Enumerator::set(int index, int val)
{
	if(index < 0 || index >= num || val <0 || val >= max)
	{
		cout << "Error Enumerator::set, index = " << index << " ,val =" << val << endl;
		exit(0);
	}
	
	states[index] = val;
}

ostream& operator<<(ostream& out, const Enumerator& en)
{
	int i;
	
	for(i=0;i<=en.num;i++)
		out << en.states[i] << " ";

	return out;
}