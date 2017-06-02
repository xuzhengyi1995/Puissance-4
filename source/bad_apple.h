#pragma once
#include"console.h"
#include<iostream>
#include<string>

class bad_apple
{
private:
	console *screen;
	void start();
public:
	bad_apple(void)
	{
		screen = new console;
		screen->set_title(L"Bad Apple!");
		system("mode con cols=161 lines=62");
		screen->set_dimensions(161, 62);
		screen->set_font(L"Consolas", 0, 12);
		this->start();
	}
	~bad_apple()
	{
		delete screen;
	}
};