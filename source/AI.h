#pragma once
#include<iostream>
#include<string>
#include"Game_process.h"

using namespace std;

struct _node
{
	char map[6][7];//盘面0无
	char side;//哪一方
	char choose;
	//_node *child[7];
	long evaluate;
	char max;
	char min;
	bool give_up;
	long can_choose[7];
};

class AI
{
private:
	_node root_of_tree;
	unsigned int max_depth;
	bool can_give_up;
public:
	AI(const node &root, unsigned int _max_depth,bool c_gp)
	{
		can_give_up = c_gp;
		max_depth = _max_depth;
		unsigned int i, j;
		for (i = 0; i < 6; i++)
			for (j = 0; j < 7; j++)
				root_of_tree.map[i][j] = root.map[i][j];
		root_of_tree.choose = -1;
		root_of_tree.give_up = true;
		clear_can();
		//for (i = 0; i < 7; i++)
			//root_of_tree.child[i] = NULL;
		if (root.side == yellow)
		{
			root_of_tree.side = yellow;
			root_of_tree.max = yellow;
			root_of_tree.min = red;
		}
		else
		{
			root_of_tree.side = red;
			root_of_tree.max = red;
			root_of_tree.min = yellow;
		}
	}
	~AI()
	{
		//int i;
		//for (i = 0; i < 7; i++)
			//delete root_of_tree.child[i];
		//delete[] root_of_tree.child;
	}
	
	long AI::Mm_search(_node &node, unsigned int depth, long a, long b);
	char search();
	void clear_can()
	{
		int i;
		for (i = 0; i < 7; i++)
		{
			this->root_of_tree.can_choose[i] = -500000;
		}
	}
	void AI::choose_can();
	/*friend void de(_node *dee)
	{
		int i;
		for (i = 0; i < 7; i++)
		{
			if (dee->child[i] == NULL)
			{
				return;
			}
			else
			{
				de(dee->child[i]);
			}
			delete[] dee->child[i];
		}
	}*/
};
char is_over(const _node &gp);
bool is_over_draw(const _node &gp);
long evaluate(const _node &gp, const unsigned int &_depth);
