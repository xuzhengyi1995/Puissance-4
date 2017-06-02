#include "StdAfx.h"
#include"AI.h"
#ifdef _DEBUG
ofstream fout("debug.txt");
#endif
char is_over(const _node &gp)
{
	int i, j, k;
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 7; j++)
		{
			if (gp.map[i][j] != 0)
			{
				//横向
				int s = 0;
				if (j <= 3)
				{
					//	向右
					for (k = j; k < 7; k++)
					{
						if (gp.map[i][k] == gp.map[i][j])
						{
							++s;
						}
						else
						{
							s = 0;
							break;
						}
						if (s == 4) return gp.map[i][j];
					}
				}

				//竖向
				if (i <= 2)
				{
					//	向下
					for (k = i; k < 6; k++)
					{
						if (gp.map[k][j] == gp.map[i][j])
						{
							++s;
						}
						else
						{
							s = 0;
							break;
						}
						if (s == 4) return gp.map[i][j];
					}
				}

				/*斜向『/』*/
				//
				if (((i >= 3) && (i <= 5)) && ((j >= 0) && (j <= 3)))
				{
					for (k = 0; k < 4; k++)
					{
						if (gp.map[i - k][j + k] == gp.map[i][j])
						{
							++s;
						}
						else
						{
							s = 0;
							break;
						}
						if (s == 4) return gp.map[i][j];
					}
				}

				//斜向『\』
				if (((i >= 0) && (i <= 2)) && ((j >= 0) && (j <= 3)))
				{
					for (k = 0; k < 4; k++)
					{
						if (gp.map[i + k][j + k] == gp.map[i][j])
						{
							++s;
						}
						else
						{
							s = 0;
							break;
						}
						if (s == 4) return gp.map[i][j];
					}
				}
			}
		}
	}
	return -1;
}
//返回获胜的颜色参数

bool is_over_draw(const _node &gp)
{
	int i;
	for (i = 0; i < 7; i++)
	{
		if (gp.map[0][i] == 0)
		{
			return false;
		}
	}
	return true;
}
//true则为平局，false为可继续

long evaluate(const _node &gp, const unsigned int &_depth)//_depth=max_depth-depth
{
	int i, j, k;
	long sum = 0;
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 7; j++)
		{
			if (gp.map[i][j] == gp.max)
			{
				//横向
				int s = 0;
				if (j <= 3)
				{
					//	向右
					for (k = j; k < j + 4; k++)
					{
						if (gp.map[i][k] == gp.map[i][j])
						{
							++s;
						}
						else
						{
							if (gp.map[i][k] != 0)
							{
								s = 0;
								break;
							}
						}
						if (s == 4) return 200000 + _depth;
					}
					sum = sum + s * 60;
					s = 0;
				}
				else
				{
					//	向左
					for (k = j; k >= j - 3; k--)
					{
						if (gp.map[i][k] == gp.map[i][j])
						{
							++s;
						}
						else
						{
							if (gp.map[i][k] != 0)
							{
								s = 0;
								break;
							}
						}
						if (s == 4) return 200000 + _depth;
					}
					sum = sum + s * 60;
					s = 0;
				}

				//竖向
				if (i <= 2)
				{
					//	向下
					for (k = i; k < i + 4; k++)
					{
						if (gp.map[k][j] == gp.map[i][j])
						{
							++s;
						}
						else
						{
							if (gp.map[k][j] != 0)
							{
								s = 0;
								break;
							}
						}
						if (s == 4) return 200000 + _depth;
					}
					sum = sum + s * 60;
					s = 0;
				}
				else
				{
					//	向上
					for (k = i; k >= i - 3; k--)
					{
						if (gp.map[k][j] == gp.map[i][j])
						{
							++s;
						}
						else
						{
							if (gp.map[k][j] != 0)
							{
								s = 0;
								break;
							}
						}
						if (s == 4) return 200000 + _depth;
					}
					sum = sum + s * 60;
					s = 0;
				}

				/*斜向『/』*/
				//向上
				if (((i >= 3) && (i <= 5)) && ((j >= 0) && (j <= 3)))
				{
					for (k = 0; k < 4; k++)
					{
						if (gp.map[i - k][j + k] == gp.map[i][j])
						{
							++s;
						}
						else
						{
							if (gp.map[i - k][j + k] != 0)
							{
								s = 0;
								break;
							}
						}
						if (s == 4) return 200000 + _depth;
					}
					sum = sum + s * 60;
					if (gp.map[i - 2][j + 3] == 0) sum = sum - s * 20;
					s = 0;
				}
				//向下
				if (((i >= 0) && (i <= 2)) && ((j >= 3) && (j <= 6)))
				{
					for (k = 0; k < 4; k++)
					{
						if (gp.map[i + k][j - k] == gp.map[i][j])
						{
							++s;
						}
						else
						{
							if (gp.map[i + k][j - k] != 0)
							{
								s = 0;
								break;
							}
						}
						if (s == 4) return 200000 + _depth;
					}
					sum = sum + s * 60;
					if (i < 2)
						if (gp.map[i + 4][j - 3] == 0) sum = sum - s * 20;
					s = 0;
				}

				//斜向『\』
				//向下
				if (((i >= 0) && (i <= 2)) && ((j >= 0) && (j <= 3)))
				{
					for (k = 0; k < 4; k++)
					{
						if (gp.map[i + k][j + k] == gp.map[i][j])
						{
							++s;
						}
						else
						{
							if (gp.map[i + k][j + k] != 0)
							{
								s = 0;
								break;
							}
						}
						if (s == 4) return 200000 + _depth;
					}
					sum = sum + s * 60;
					if (i < 2)
						if (gp.map[i + 4][j + 3] == 0) sum = sum - s * 20;
					s = 0;
				}

				//向上
				if (((i >= 3) && (i <= 5)) && ((j >= 3) && (j <= 7)))
				{
					for (k = 0; k < 4; k++)
					{
						if (gp.map[i - k][j - k] == gp.map[i][j])
						{
							++s;
						}
						else
						{
							if (gp.map[i - k][j - k] != 0)
							{
								s = 0;
								break;
							}
						}
						if (s == 4) return 200000 + _depth;
					}
					sum = sum + s * 60;
					if (gp.map[i - 2][j - 3] == 0) sum = sum - s * 20;
					s = 0;
				}
			}
		}
	}
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 7; j++)
		{
			if (gp.map[i][j] == gp.min)
			{
				//横向
				int s = 0;
				//if (j <= 3)
				//{
					//	向右
				for (k = j; k < 7; k++)
				{
					if (gp.map[i][k] == gp.map[i][j])
					{
						++s;
					}
					else
					{
						//s = 0;
						if (gp.map[i][k] != 0)
						{
							s = 0;
							break;
						}
					}
					if (s == 4) return (-200000 - _depth);
				}
				//}
				if (s >= 2) sum = sum - s * 100;
				if (s == 3)sum = sum - 800;
				s = 0;

				//竖向
				//if (i <= 2)
				//{
					//	向下
				for (k = i; k < 6; k++)
				{
					if (gp.map[k][j] == gp.map[i][j])
					{
						++s;
					}
					else
					{
						//s = 0;
						if (gp.map[k][j] != 0)
						{
							s = 0;
							break;
						}
					}
					if (s == 4) return (-200000 - _depth);
				}

				if (s >= 2) sum = sum - s * 100;
				//if (s == 3)sum = sum - 100000;
				s = 0;
				//}

				/*斜向『/』*/
				//
				if (((i >= 3) && (i <= 5)) && ((j >= 0) && (j <= 3)))
				{
					for (k = 0; k < 4; k++)
					{
						if (gp.map[i - k][j + k] == gp.map[i][j])
						{
							++s;
						}
						else
						{
							if (gp.map[i - k][j + k] != 0)
							{
								s = 0;
								break;
							}
						}
						if (s == 4) return (-200000 - _depth);
					}
				}
				if (s >= 2) sum = sum - s * 100;
				//if (s == 3)sum = sum - 5000;
				s = 0;
				//向下!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				if (((i >= 0) && (i <= 2)) && ((j >= 3) && (j <= 6)))
				{
					for (k = 0; k < 4; k++)
					{
						if (gp.map[i + k][j - k] == gp.map[i][j])
						{
							++s;
						}
						else
						{
							if (gp.map[i + k][j - k] != 0)
							{
								s = 0;
								break;
							}
						}
						if (s == 4) return (-200000 - _depth);
					}
					if (s >= 2) sum = sum - s * 100;
					s = 0;
				}
				//斜向『\』
				if (((i >= 0) && (i <= 2)) && ((j >= 0) && (j <= 3)))
				{
					for (k = 0; k < 4; k++)
					{
						if (gp.map[i + k][j + k] == gp.map[i][j])
						{
							++s;
						}
						else
						{
							if (gp.map[i + k][j + k] != 0)
							{
								s = 0;
								break;
							}
						}
						if (s == 4) return (-200000 - _depth);
					}
				}
				if (s >= 2) sum = sum - s * 100;
				//if (s == 3)sum = sum - 5000;
				s = 0;
				//向上!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				if (((i >= 3) && (i <= 5)) && ((j >= 3) && (j <= 7)))
				{
					for (k = 0; k < 4; k++)
					{
						if (gp.map[i - k][j - k] == gp.map[i][j])
						{
							++s;
						}
						else
						{
							if (gp.map[i - k][j - k] != 0)
							{
								s = 0;
								break;
							}
						}
						if (s == 4) return (-200000 - _depth);
					}
					if (s >= 2) sum = sum - s * 100;
					s = 0;
				}
			}
		}
	}
	//特殊判断
	//**&&**
	//&&&&&&
	bool dang = false;
	for (i = 0; i < 6; i++)
	{
		for (j = 1; j < 5; j++)
		{
			if (gp.map[i][j] == gp.min && gp.map[i][j + 1] == gp.min)
			{
				if (i == 5)
				{
					if (gp.map[i][j - 1] == 0 && gp.map[i][j + 2] == 0)
					{
						dang = true;
						break;
					}
				}
				else
				{
					if ((gp.map[i][j - 1] == 0 && gp.map[i][j + 2] == 0) && (gp.map[i + 1][j - 1] != 0 && gp.map[i + 1][j + 2] != 0))
					{
						dang = true;
						break;
					}
				}
			}
		}
		if (dang) break;
	}
	if (dang == true) sum = sum - _depth * 150;

	bool dang1 = false;
	for (i = 0; i < 6; i++)
	{
		for (j = 1; j < 5; j++)
		{
			if (gp.map[i][j] == gp.max && gp.map[i][j + 1] == gp.max)
			{
				if (i == 5)
				{
					if (gp.map[i][j - 1] == 0 && gp.map[i][j + 2] == 0)
					{
						dang1 = true;
						break;
					}
				}
				else
				{
					if ((gp.map[i][j - 1] == 0 && gp.map[i][j + 2] == 0) && (gp.map[i + 1][j - 1] != 0 && gp.map[i + 1][j + 2] != 0))
					{
						dang1 = true;
						break;
					}
				}
			}
		}
		if (dang1) break;
	}
	if (dang1 == true) sum = sum + _depth * 150;
	for (i = 5; i >= 0; i--)
	{
		for (j = 0; j < 3; j++)
		{
			if (gp.map[i][j] == 0 && gp.map[i][j + 1] == gp.min && gp.map[i][j + 2] == gp.min && gp.map[i][j + 3] == gp.min && gp.map[i][j + 4] == 0)
			{
				if (i == 5)
				{
					sum = sum - _depth * 10000;
				}
				else
				{
					if (gp.map[i + 1][j] != 0 && gp.map[i + 1][j + 4] != 0) sum = sum - _depth * 10000;
				}
			}
			if (gp.map[i][j] == 0 && gp.map[i][j + 1] == gp.max && gp.map[i][j + 2] == gp.max && gp.map[i][j + 3] == gp.max && gp.map[i][j + 4] == 0)
			{
				if (i == 5)
				{
					sum = sum + _depth * 10000;
				}
				else
				{
					if (gp.map[i + 1][j] != 0 && gp.map[i + 1][j + 4] != 0) sum = sum + _depth * 10000;
				}
			}
		}
	}

	for (i = 5; i >= 0; i--)
	{
		for (j = 0; j < 3; j++)
		{
			if (gp.map[i][j] == 0 && gp.map[i][j + 1] == gp.min && gp.map[i][j + 2] == 0 && gp.map[i][j + 3] == gp.min && gp.map[i][j + 4] == 0)
			{
				if (i == 5)
				{
					sum = sum - _depth * 8000;
				}
				else
				{
					if (gp.map[i + 1][j] != 0 && gp.map[i][j + 2] != 0 && gp.map[i + 1][j + 4] != 0) sum = sum - _depth * 8000;
				}
			}
			if (gp.map[i][j] == 0 && gp.map[i][j + 1] == gp.max && gp.map[i][j + 2] == 0 && gp.map[i][j + 3] == gp.max && gp.map[i][j + 4] == 0)
			{
				if (i == 5)
				{
					sum = sum + _depth * 8000;
				}
				else
				{
					if (gp.map[i + 1][j] != 0 && gp.map[i][j + 2] != 0 && gp.map[i + 1][j + 4] != 0) sum = sum + _depth * 8000;
				}
			}
		}
	}
	return sum;
}
//评分

/*for (j = 0; j < 6; j++)
{
for (k = 0; k < 7; k++)
{
printf("%d ", node.map[j][k]);
}
std::cout << endl;
}
printf("%d %d %d %d %d", node.choose, node.side, ok_1, ok_2, depth);
std::cout << endl;
long x = evaluate(node, (this->max_depth - depth + 1));
cout << "evaluate: " << x << endl;
std::system("pause");
return x;*/

long AI::Mm_search(_node &node, unsigned int depth, long a, long b)
{
	char ok_1 = is_over(node);
	bool ok_2 = is_over_draw(node);
	int i, j;
	//int saigo=-500000;
	//设置终止条件
	if (depth >= this->max_depth || ok_1 != -1 || ok_2 == true)
	{
		//#ifdef _DEBUG;
		if (ok_1 != -1 && ok_1 == node.max)
		{
			node.evaluate = 200000 + (this->max_depth - depth + 1);
			return node.evaluate;
		}
		if (ok_1 != -1 && ok_1 == node.min)
		{
			node.evaluate = -200000 - (this->max_depth - depth + 1);
			return node.evaluate;
		}
#ifdef _DEBUG1
		long x = evaluate(node, (this->max_depth - depth + 1));
		if (x > 200000)
		{
			fout << "DEPTH: " << depth << endl;
			for (i = 0; i < 6; i++)
			{
				for (j = 0; j < 7; j++)
					fout << (int)node.map[i][j] << "  ";
				fout << endl;
			}
			fout << endl;
			//return 205000;
		}
		return x;
#endif
		return evaluate(node, (this->max_depth - depth + 1));
	}
	//搜索
	if (node.side == node.max)
	{
		char _i = -1, _j = -1;
		#ifdef _DEBUG
			bool debug_c = true;
		#endif
		for (i = 0; i < 7; i++)
		{
			_i = -1, _j = -1;
			while (node.map[0][i] != 0 && i < 7) i++;
			if (i == 7) break;
			//int l;
			bool flag = true;
			for (j = 5; j >= 0; j--)
			{
				if (node.map[j][i] == 0)
				{
					flag = false;
					node.map[j][i] = node.max;
					_i = j;
					_j = i;
				}
				if (!flag) break;
			}
			node.side = node.min;
			//std::cout << "diannao !!!" << endl;
			long temp = Mm_search(node, depth + 1, a, b);
			#ifdef _DEBUG
				if (depth == 0)
				{
					if (debug_c == true)
					{
						fout << "COLOR:";
						if (node.max == yellow) fout << "yellow" << endl << endl; else fout << "red" << endl << endl;
						debug_c = false;
					}
					fout << "I:" << i << ":";
					fout << temp << endl;
				}
			#endif
			if (_i != -1 && _j != -1)
			{
				node.map[_i][_j] = 0;
				if (node.side == yellow) node.side = red; else node.side = yellow;
			}
			//std::cout << "diannao " << temp << endl;
			//system("pause");
			if (temp > a)
			{
				a = temp;
			}
			if (depth == 0)
			{
				if (temp > -200000) node.give_up = false;
				node.can_choose[i] = temp;
			}
			//if (b < a) break;
		}
		//node.evaluate = a;
		return a;
	}
	else
	{
		char _i = -1, _j = -1;
		for (i = 0; i < 7; i++)
		{
			_i = -1, _j = -1;
			while (node.map[0][i] != 0 && i < 7) i++;
			if (i == 7) break;
			//int l;
			bool flag = true;
			for (j = 5; j >= 0; j--)
			{
				if (node.map[j][i] == 0)
				{
					flag = false;
					node.map[j][i] = node.min;
					_i = j;
					_j = i;
					break;
					//node.map[j][k] = yellow;*/
				}
				if (!flag) break;
			}
			node.side = node.max;
			//std::cout << "ren !!!"<< endl;
			long temp = Mm_search(node, depth + 1, a, b);
			if (_i != -1 && _j != -1)
			{
				node.map[_i][_j] = 0;
				if (node.side == yellow) node.side = red; else node.side = yellow;
			}
			//std::cout <<"ren "<< temp << endl;
			//system("pause");
			if (temp < b)
			{
				b = temp;
			}
			//if (b > a) break;
		}
		//node.evaluate = b;
		return b;
	}
}

char AI::search()
{
	//int i, j, k, l;
	/*for (i = 0; i < 7; i++)
	{
		this->root_of_tree.child[i] = new _node;
		for (l = 0; l < 7; l++)
		{
			this->root_of_tree.child[i]->child[l] = NULL;
		}
		this->root_of_tree.child[i]->max = this->root_of_tree.max;
		this->root_of_tree.child[i]->min = this->root_of_tree.min;
	}
	for (i = 0; i < 7; i++)
	{
		while (this->root_of_tree.map[0][i] != 0 && i < 7)
		{
			i++;
		}
		if (i == 7) break;
		bool flag = true;
		for (j = 5; j >= 0; j--)
		{
			for (k = 0; k < 7; k++)
			{
				if (k == i && flag == true)
				{
					if (this->root_of_tree.map[j][k] == 0)
					{
						this->root_of_tree.child[i]->evaluate = -500000;
						flag = false;
						this->root_of_tree.child[i]->map[j][k] = this->root_of_tree.side;
					}
					else
					{
						this->root_of_tree.child[i]->map[j][k] = this->root_of_tree.map[j][k];
					}
				}
				else
				{
					this->root_of_tree.child[i]->map[j][k] = this->root_of_tree.map[j][k];
				}
			}
		}
		this->root_of_tree.child[i]->evaluate=this->Mm_search(*this->root_of_tree.child[i], 0, -200000, 200000);
	}
	*/
	/*for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 6; j++)
		{
			for (k = 0; k < 7; k++)
			{
				printf("%d ", this->root_of_tree.child[i]->map[j][k]);
			}
			std::cout << endl;
		}
		printf("%d %d", root_of_tree.child[i]->choose, root_of_tree.child[i]->side);
		std::cout << endl;
		cout << "evaluate: " << root_of_tree.child[i]->evaluate << endl;
		std::system("pause");
	}
	int choose=0;
	long max = -50000000;
	bool give_up = true;
	for (i = 0; i < 7; i++)
	{
		if (root_of_tree.child[i]->evaluate>max)
		{
			choose = i;
			max = root_of_tree.child[i]->evaluate;
		}

	}
	for (i = 0; i < 7; i++)
	{
		if (root_of_tree.child[i]->evaluate != -200000 && root_of_tree.child[i]->evaluate != -500000)
			give_up = false;
	}*/
	//if (give_up == true) choose = -1;
	int i, j;
	int s = 0;
	int c = 0;
	for (i = 0; i < 6; i++)
		for (j = 0; j < 7; j++)
			if (root_of_tree.map[i][j] == root_of_tree.min)
			{
				++s;
				c = j;
			}
	if (s <= 2)
	{
		if (s == 1)
		{
			if (c == 6)
				return 5;
			else
				return c + 1;
		}
		else
		{
			s = 0;
			for (j = 0; j < 6; j++)
			{
				if (root_of_tree.map[5][j] == root_of_tree.min)
				{
					++s;
					if (root_of_tree.map[5][j + 1] == 0)
						c = j + 1;
					else
						if (root_of_tree.map[5][j - 1] == 0 && j != 0)
							c = j - 1;

				}
			}
			if (root_of_tree.map[5][6] == root_of_tree.min&&root_of_tree.map[5][5] == 0)
			{
				++s;
				c = 5;
			}
			if (s == 2) return c;
		}
	}

	this->Mm_search(this->root_of_tree, 0, -500000, 500000);
	if (root_of_tree.give_up == true && this->can_give_up == true)
	{
		return -1;
	}
	else
	{
		choose_can();
		return root_of_tree.choose;
	}

}

void AI::choose_can()
{
#ifdef _DEBUG
	FILE *debug;
	fopen_s(&debug, "debug_c_c.txt", "a");
	fprintf(debug, "color:%d\n", this->root_of_tree.side);
#endif
	char c_s[7];
	char s = 0;
	int i;
	long max = -500000;
	for (i = 0; i < 7; i++)
	{
#ifdef _DEBUG
		fprintf(debug, "I%d : %ld\n", i, root_of_tree.can_choose[i]);
#endif
		if (this->root_of_tree.can_choose[i] != -500000)
		{
			if (this->root_of_tree.can_choose[i]>max)
			{
				max = this->root_of_tree.can_choose[i];
			}
		}
	}
	for (i = 0; i < 7; i++)
	{
		if (root_of_tree.can_choose[i] == max)
		{
			c_s[s] = i;
			++s;
		}
	}
#ifdef _DEBUG
	fprintf(debug, "We can choose:\n");
	for (i = 0; i < s; i++)
	{
		fprintf(debug, "  C%d: %ld\n", c_s[i], root_of_tree.can_choose[c_s[i]]);
	}
#endif
	if (root_of_tree.can_choose[c_s[0]] > 200000)
	{
		this->root_of_tree.choose = c_s[0];
	}
	else
	{
		srand((int)time(0) + rand() % 10);
		this->root_of_tree.choose = c_s[rand() % s];
	}
#ifdef _DEBUG
	fprintf(debug, "We choose:%d\n", this->root_of_tree.choose);
	fprintf(debug, "****************************\n");
	fclose(debug);
#endif
}