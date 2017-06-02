#pragma once

#include"AI.h"
#include"Game_process.h"
#include"stdafx.h"
#include"bad_apple.h"

using namespace std;
class game
{
public:
	game(void)
	{
		game_start();
	}
	void game_start()
	{
		char tsuzuku = 'y';
		while (tsuzuku == 'y' || tsuzuku == 'Y')
		{
			system("mode con cols=22 lines=32");//22,30
			game_ui new_game(22, 32, 8, 8);
			char re = new_game.first();
			if (re == 4)
			{
				bad_apple s1;
				tsuzuku = 'y';
			}
			else
			{
				game_process new_process(re, new_game);
				tsuzuku = _getch();
				new_game.clean_picture();
			}
		}
	}
};