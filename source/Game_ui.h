#pragma once
#include"console.h"
#include<iostream>
#include<string>

//����ʹ������
//system("mode con cols=22 lines=30"); ��ʹ��֮ǰһ����д����
//game_ui new_game(22, 30, 8, 8);//��Ŀ��׼

class game_ui
{
private:
	console *Game;
	unsigned int w_ui;
	unsigned int h_ui;
	unsigned int w_font;
	unsigned int h_font;
	bool sound;
public:
	game_ui(const unsigned int &_w_ui, const unsigned int &_h_ui, const unsigned int &_w_font, const unsigned int &_h_font);//������ߣ��������
	~game_ui();
	void set_up();//����Ϸ����
	char first();//��ʾ��ӭ���棬�������û�ѡ���ֵ��1��2��3.
	void clean_text();//�����Ϸ������ʾ����
	void play_text(const char &stat, const char &last, const char(&which_can)[7]);//��ʾ��ʾ���֣�1:�ƣ�2���죬-1����win��-2����win,���飬��һ�пɷţ�-1���ɣ�0��
	void place_it(const char &stat, const char &column, const char &end);//stat��1 �ƣ�2�죬column����һ��(0~6),end���䵽����(0,1,2,3,4,5)
	void error(const string &err);//������������ʾ���󣬴����ַ�����
	void give_up(color what);//���䣬what����Ϊ��һ����yellow����red
	bool draw_picture(const char *name);//��ͼƬ
	bool clean_picture();//���ͼƬ
	void sound_display();//��ʾ�������
	void sound_switch();//�л���������
};

