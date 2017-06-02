#include "StdAfx.h"
#include"bad_apple.h"

void bad_apple::start()
{
	FILE *open;
	fopen_s(&open, "AscPic.txt", "r");
	//获取文件 
	//int speed = 9;
	Sleep(50);
	PlaySound(L"BadApple.wav", NULL, SND_FILENAME | SND_ASYNC);//播放badapple
	screen->clear();
	int i;
	int j;
	char a[500];
	DWORD  dwGTCBegin, dwGTCEnd, dwStart, time;
	COORD pos;
	pos.X = 0;
	pos.Y = 61;
	int s = 0;
	int q;
	dwGTCBegin = clock();
	while (s < 190)
	{
		dwGTCEnd = clock();
		s = dwGTCEnd - dwGTCBegin;
	}
	dwGTCBegin = clock();
	dwStart = dwGTCBegin;
	double fps=30;
	for (i = 0; i < 6600; i++)
	{
		
		for (j = 0; j < 61; j++) //输出一个画面的每一行 
		{
			if (fgets(a, 162, open) == NULL) break; //获得一行的字符串存入a中，发现取完则退出这个循环 
			screen->print_string(a, 160, 0, j);//调用printchar函数，在指定位置上打印字符串使得没有刷新感觉 
		}
		s = 0;
		if (i == 0)
		{
			q = 35;
		}
		else
		{
			if (!(i > 3000 && i < 3600))
			{
				if (fps < 29.67) q = 33; else q = 35;
			}
			else
			{
				if (fps < 29.57) q = 33; else q = 39;
			}
		}
		while (s < q)
		{
			dwGTCEnd = clock();
			s = dwGTCEnd - dwGTCBegin;
		}
		dwGTCBegin = clock();
		screen->set_cursor_position(pos);
		time = dwGTCEnd - dwStart;
		fps = (i * 1000 / (double)time);
		cout << "Delay: " << s << "ms  Frame: " << i << "  Time: " << time << "ms  FPS: " << fps << "fps";
		//pos.Y = 0;
		//screen->set_cursor_position(pos);
		//Sleep(s);//控制停顿时间
	}
	system("pause");
}