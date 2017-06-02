#include "StdAfx.h"

#include "console.h"

console::console(void)
{
	system("chcp 863");
	hScreenBuffer = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hScreenBuffer == INVALID_HANDLE_VALUE)
	{
		error_exit("Can't get screen handle");
	}
	GetConsoleScreenBufferInfo(hScreenBuffer, &screenInfo);
	clear();
}

console::~console(void)
{
	// �ָ�
	SetConsoleTextAttribute(hScreenBuffer, screenInfo.wAttributes);

}

void console::error_exit(const string& s) const
{
	cerr << s;
	system("pause");
	ExitProcess(0);
}

void console::set_title(const wstring& s)
{
	SetConsoleTitle(s.c_str());
}

void console::set_cursor_color(color c)
{
	switch (c)
	{
		case default_color:
			SetConsoleTextAttribute(hScreenBuffer, 0);
			break;
		case red:
			SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_RED | FOREGROUND_INTENSITY);
			break;
		case green:
			SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		case blue:
			SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			break;
		case yellow:
			SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		case white:
			SetConsoleTextAttribute(hScreenBuffer, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			break;
		default:
			error_exit("Unknown color in set_cursor_color");
	}
}

void console::set_cursor_position(const COORD& p)
{
	SetConsoleCursorPosition(hScreenBuffer, p);
}

void console::clear()
{
	system("CLS");
}

void console::set_dimensions(unsigned int w, unsigned int h)
{
	COORD cSize = { w,h };
	int result = SetConsoleScreenBufferSize(hScreenBuffer, cSize);
	if (result == 0)
	{
		error_exit("SetConsoleScreenBufferSize");
	}
}

void console::set_font(wchar_t *font, unsigned int width, unsigned int height)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof cfi;
	cfi.nFont = 0;
	cfi.dwFontSize.X = width;
	cfi.dwFontSize.Y = height;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, font);
	SetCurrentConsoleFontEx(hScreenBuffer, FALSE, &cfi);
}

void console::print_string(const char *ch, UINT count, UINT x, UINT y)  
{
	COORD pos;
	ULONG unuse;
	pos.X = x;
	pos.Y = y;
	WriteConsoleOutputCharacterA(hScreenBuffer, ch, count, pos, &unuse);
}

void console::print_char(const char ch, UINT count, UINT x, UINT y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	this->set_cursor_position(pos);
	unsigned int i;
	for (i = 0; i < count; i++)
		cout << ch;
}

bool console::draw_bmp(unsigned long w,unsigned long h,unsigned long **t)
{
	//CDC dc();
	HDC p1 = GetWindowDC(NULL);
	int i, j;
	unsigned int s_i = 50;
	unsigned int e_i = h + 50;
	unsigned int s_j = 50;
	unsigned int e_j = w + 50;
	for (i = s_i; i < e_i; i++)
		for (j = s_j; j < e_j; j++)
		{
			SetPixelV(p1,j, i,t[i-s_i][j-s_j]);
		}
	return true;
}

bool console::clean_bmp()
{
	HDC p1 = GetWindowDC(NULL);
	ReleaseDC(NULL, p1);
	InvalidateRect(NULL, NULL, true);
	UpdateWindow(NULL);
	return true;
}
