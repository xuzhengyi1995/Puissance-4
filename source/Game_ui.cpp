#include "StdAfx.h"
#include"Game_ui.h"
#include"picture.h"


using namespace std;

game_ui::game_ui(const unsigned int &_w_ui, const unsigned int &_h_ui, const unsigned int &_w_font, const unsigned int &_h_font) :
	w_ui(_w_ui), h_ui(_h_ui), w_font(_w_font), h_font(_h_font)
{
	sound = true;
	Game = new console;
	Game->set_title(L"New Game");
	Game->set_font(L"Arial",_w_font, _h_font);
	Game->set_dimensions(_w_ui, _h_ui);//50,30
	this->set_up();
}

game_ui::~game_ui()
{
	delete Game;
}

void game_ui::set_up()
{
	//22
	Game->set_cursor_color(blue);
	unsigned int i, j;
	for (i = 0; i < 19; i++)
	{
		if (i % 3 == 0)
		{
			Game->print_char(178, 22, 0, i);
		}
		else
		{
			for (j = 0; j < 22; j++)
				if (j % 3 == 0) 
					Game->print_char(178, 1, j, i);
				else
					Game->print_char(' ', 1, j, i);
		}
	}
	Game->set_cursor_color(green);
	Game->print_char(178, 22, 0, 19);
	Game->print_char(178, 22, 0, 28);
	Game->set_cursor_color(white);
	sound_display();
	/*Game->set_cursor_color(white);
	cout << "joueur ";
	Game->set_cursor_color(yellow);
	cout << "jaune"<<endl;
	Game->set_cursor_color(white);
	cout << "colonne :" << endl;
	cout << endl;
	cout << "votre choix (1 2 3 4 5 6 7)?" << endl;
	COORD pos;
	pos.X = 0;
	pos.Y = 25;
	Game->set_cursor_position(pos);*/

}
void game_ui::clean_text()
{
	unsigned int i;
	for (i = 20; i <= 27; i++)
		Game->print_string("                      ", 22, 0, i);
}
char game_ui::first()
{
	Game->set_cursor_color(white);
	Game->print_string("Welcome!", 8, 7, 20);
	Game->print_string("1.Two person", 12, 0, 21);
	Game->print_string("2.One person", 12, 0, 22);
	Game->print_string("3.DEMO", 6, 0, 23);
	Game->print_string("4.**Bad Apple!**", 17, 0, 24);
	Game->print_string("Choose 1, 2 or 3 to start the game", 34, 0, 25);
	char choose='0';
	COORD pos;
	pos.X = 0;
	pos.Y = 26;
	while (!(choose >= '1' && choose <= '4'))
	{
		Game->set_cursor_position(pos);
		choose=_getch();
		if (choose == 'a' || choose == 'A')
		{
			sound_switch();
		}
		else
		{
			if (!(choose >= '1' && choose <= '4'))
			{
				unsigned int i;
				for (i = 0; i < 5; i++)
				{
					Game->print_string("                                  ", 34, 0, 25);
					Sleep(200);
					Game->print_string("Choose 1, 2 or 3 to start the game", 34, 0, 25);
					Sleep(200);
				}
			}
		}
	}
	return choose-48;
}

void game_ui::play_text(const char &stat, const char &last, const char(&which_can)[7])//1:黄，2：红，-1：黄win，-2：红win,数组，哪一个可放，-1不可，0可
{
	COORD pos;
	unsigned int i;
	switch(stat)
	{
	case yellow:
		pos.X = 0;
		pos.Y = 20;
		Game->set_cursor_position(pos);
		Game->set_cursor_color(white);
		cout << "Player ";
		Game->set_cursor_color(yellow);
		cout << "Yellow" << endl;
		Game->set_cursor_color(white);
		cout << "Last Column : ";
		if (last == -1)
			cout << "No" << endl;
		else
			cout << last << endl;
		cout << "You choose ( ";
		for (i = 0; i < 7; i++)
			if (which_can[i] == 0) cout << i + 1 << ' ';
		cout << " )?";
		pos.X = 0;
		pos.Y = 26;
		Game->set_cursor_position(pos);
		break;
	case red:
		pos.X = 0;
		pos.Y = 20;
		Game->set_cursor_position(pos);
		Game->set_cursor_color(white);
		cout << "Player ";
		Game->set_cursor_color(red);
		cout << "Red" << endl;
		Game->set_cursor_color(white);
		cout << "Last Column : ";
		if (last == -1)
			cout << "No" << endl;
		else
			cout << last << endl;
		cout << "You choose ( ";
		for (i = 0; i < 7; i++)
			if (which_can[i] == 0) cout << i + 1 << ' ';
		cout << " )?";
		pos.X = 0;
		pos.Y = 26;
		Game->set_cursor_position(pos);
		break;
	case -1:
		pos.X = 0;
		pos.Y = 20;
		if (sound) PlaySound(L"Bakuhatu.wav", NULL, SND_FILENAME | SND_ASYNC);
		Game->set_cursor_position(pos);
		Game->set_cursor_color(yellow);
		cout << "Yellow Win! " << endl;
		Game->set_cursor_color(white);
		cout << "Again?(Y or N)" << endl;
		pos.X = 0;
		pos.Y = 26;
		Game->set_cursor_position(pos);
		break;
	case -2:
		pos.X = 0;
		pos.Y = 20;
		if (sound) PlaySound(L"Bakuhatu.wav", NULL, SND_FILENAME | SND_ASYNC);
		Game->set_cursor_position(pos);
		Game->set_cursor_color(red);
		cout << "Red Win! " << endl;
		Game->set_cursor_color(white);
		cout << "Again?(Y or N)" << endl;
		pos.X = 0;
		pos.Y = 26;
		Game->set_cursor_position(pos);
		break;
	case -3:
		pos.X = 0;
		pos.Y = 20;
		if (sound) PlaySound(L"Bakuhatu.wav", NULL, SND_FILENAME | SND_ASYNC);
		Game->set_cursor_position(pos);
		Game->set_cursor_color(red);
		cout << "Draw! " << endl;
		Game->set_cursor_color(white);
		cout << "Again?(Y or N)" << endl;
		pos.X = 0;
		pos.Y = 26;
		Game->set_cursor_position(pos);
		break;
	}
}

void game_ui::place_it(const char &stat, const char &column, const char &end)//stat：1 黄，2红，column：哪一列(0~6),end：落到哪里(0,1,2,3,4,5)
{
	COORD pos;
	pos.X = 0;
	pos.Y = 26;
	color temp;
	if (stat == 5) temp = yellow; else temp = red;
	unsigned int i;
	for (i = 0; i < (6 - end); i++)
	{
		Game->set_cursor_color(temp);
		Game->print_char(254, 2, 3 * column + 1, 3 * i + 1);
		Game->print_char(254, 2, 3 * column + 1, 3 * i + 2);
		Game->set_cursor_position(pos);
		if (i != 5 - end)
		{
			Sleep(110);
			Game->print_char(' ', 2, 3 * column + 1, 3 * i + 1);
			Game->print_char(' ', 2, 3 * column + 1, 3 * i + 2);
			Game->set_cursor_position(pos);
			Sleep(110);
		}
	}
	if (sound) PlaySound(L"Up.wav", NULL, SND_FILENAME | SND_ASYNC);
}

void game_ui::error(const string &err)
{
	COORD pos;
	pos.X = 0;
	pos.Y = 26;
	Game->set_cursor_position(pos);
	cout << "ERROR:" << err << endl;
	Sleep(500);
	Game->print_string("                                  ", 34, 0, 26);
	Game->set_cursor_position(pos);
}

void game_ui::give_up(color what)
{
	COORD pos;
	pos.X = 0;
	pos.Y = 26;
	PlaySound(L"Bakuhatu.wav", NULL, SND_FILENAME | SND_ASYNC);
	Game->set_cursor_position(pos);
	if (what == yellow) cout << "Yellow "; else cout << "Red ";
	cout << "Give Up!" << endl;
	Game->set_cursor_position(pos);
}

bool game_ui::draw_picture(const char *name)
{
	picture p1(name);
	Game->draw_bmp(p1.get_width(), p1.get_height(), p1.get_data());
	return true;
}

bool game_ui::clean_picture()
{
	Game->clean_bmp();
	return true;
}

void game_ui::sound_display()
{
	COORD pos;
	pos.X = 0;
	pos.Y = 29;
	Game->set_cursor_position(pos);
	cout << "Sound:";
	if (sound == true) cout << "On "; else cout << "Off";
	pos.Y = 30;
	Game->set_cursor_position(pos);
	cout << "Press A to Switch";
}
	
void game_ui::sound_switch()
{
	sound=!sound;
	sound_display();
}