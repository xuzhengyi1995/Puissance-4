#pragma once
#include"Game_ui.h"
#include<iostream>
#include<string>


using namespace std;


struct node
{
	char map[6][7];//盘面0无
	char side;//哪一方
	char choose;//选择哪一列导致了这个盘面【0～6】
	char can[7];
	char last;
};

class game_process
{
private:
	node gp;
	char mode;
public:
	game_process(const char _mode, game_ui &_this_game) :
		mode(_mode)
	{
		int i, j;
		for (i = 0; i < 6; i++)
			for (j = 0; j < 7; j++)
				gp.map[i][j] = 0;
		/*{
			cin >> gp.map[i][j];
			gp.map[i][j] = gp.map[i][j] - '0';
		}*/
		for (i = 0; i < 7; i++)
			gp.can[i] = 0;
		gp.side = red;
		gp.choose = 0;
		gp.last = -1;
		game_start(_this_game);
	}
	char is_over();
	void game_start(game_ui &this_game);
	bool is_over_draw();
	void process_can();
	char process_end(const char &column);
};