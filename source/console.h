#pragma once
#include "Windows.h"
#include <string>
#include <iostream>

using namespace std;

enum color { default_color, blue, red, green, white, yellow };

class console
{
private:
	HANDLE hScreenBuffer;
	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	void error_exit(const string& s) const;
public:
	console(void);
	~console(void);
	void set_title(const wstring& s); //���ñ���
	void set_dimensions(unsigned int width, unsigned int height); //�任���ڴ�С
	void set_cursor_position(const COORD& p);
	void set_cursor_color(color c); //������ɫ
	void clear(); //CLS
	void set_font(wchar_t *font, unsigned int width, unsigned int height);//�任�����С
	void print_string(const char *ch, UINT count, UINT x, UINT y);//������(x,y)������ַ���ch,ch����count���ַ�
	void print_char(const char ch, UINT count, UINT x, UINT y);//������(x,y)�����count���ַ�
	bool console::draw_bmp(unsigned long w, unsigned long h, unsigned long **t);//���ߣ���ɫ����
	bool console::clean_bmp();//���ͼƬ
};
