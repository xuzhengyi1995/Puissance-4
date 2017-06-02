#include "StdAfx.h"
#include"Game_process.h"
#include"AI.h"

char game_process::is_over()
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

bool game_process::is_over_draw()
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

void game_process::process_can()
{
	int i;
	for (i = 0; i < 7; i++)
	{
		if (gp.map[0][i] != 0) gp.can[i] = -1;
	}
}
//更新能选择列表

char game_process::process_end(const char &column)
{
	int i;
	char s = 0;
	for (i = 0; i < 6; i++)
	{
		if (gp.map[i][column] == 0) ++s; else return 6-s;
	}
	return 6-s;
}
//计算结束位置

void game_process::game_start(game_ui &this_game)
{
	gp.choose = -1;
	char result = -1;
	srand((int)time(0));
	unsigned int s = 0;
	while ((result == -1) && (this->is_over_draw() == false))
	{
		this_game.clean_text();
		this_game.play_text(gp.side, gp.last, gp.can);
		bool is_choose_ok = false;
		++s;
		while (is_choose_ok == false)
		{
			if (gp.side == yellow)
			{
				if (this->mode == 2 || this->mode == 3)
				{
					bool c_g_p = true;
					if (this->mode == 2)
					{
						c_g_p = false;
					}
					AI p1(gp, 8, c_g_p);
					gp.choose = p1.search();
					if (gp.choose == -1)
					{
						this_game.clean_text();
						this_game.play_text(-2, gp.last, gp.can);
						this_game.draw_picture("red_win.bmp");
						this_game.give_up(yellow);
						return;

					}
				}
				else
				{
					gp.choose = _getch() - 49;
					if (gp.choose == 'a'-49 || gp.choose == 'A'-49)
					{
						this_game.sound_switch();
					}
				}
			}
			else
			{
				if (this->mode == 3)
				{
					if (s <= 4)
					{
						gp.choose = rand() % 6 + 1;
						//gp.choose = 2;
					}
					else
					{
						AI p2(gp, 5, true);
						gp.choose = p2.search();
						if (gp.choose == -1)
						{
							this_game.clean_text();
							this_game.play_text(-1, gp.last, gp.can);
							this_game.draw_picture("yellow_win.bmp");
							this_game.give_up(red);
							return;
						}
					}
				}
				else
				{
					gp.choose = _getch() - 49;
				}
			}
			if (gp.choose == 'a' - 49 || gp.choose == 'A' - 49)
			{
				this_game.sound_switch();
			}
			else
			{
				if (gp.choose < 1 && gp.choose>7)
				{
					this_game.error("Wrong data!");
				}
				else
				{
					if (gp.can[gp.choose] != 0)
					{
						this_game.error("Choose the wrong column!");
					}
					else
					{
						is_choose_ok = true;
					}
				}
			}
		}
		char _end = this->process_end(gp.choose);
		gp.map[5 - _end][gp.choose] = gp.side;
		this_game.place_it(gp.side, gp.choose, _end);
		result = this->is_over();
		if (result != -1) break;
		if (gp.side == yellow) gp.side = red; else gp.side = yellow;
		gp.last = gp.choose + 49;
		this->process_can();
		this_game.play_text(gp.side, gp.last, gp.can);
	}
	this_game.clean_text();
	if (result == -1)
	{
		this_game.play_text(-3, gp.last, gp.can);
		this_game.draw_picture("draw.bmp");
	}
	else
	{
		if (result == yellow)
		{
			this_game.play_text(-1, gp.last, gp.can);
			if (mode == 1 || mode == 3)
			{
				this_game.draw_picture("yellow_win.bmp");
			}
			else
			{
				this_game.draw_picture("you_lose.bmp");
			}
		}
		else
		{
			if (result == red)
			{
				this_game.play_text(-2, gp.last, gp.can);
				if (mode == 1 || mode == 3)
				{
					this_game.draw_picture("red_win.bmp");
				}
				else
				{
					this_game.draw_picture("you_win.bmp");
				}
			}
		}
	}
}
