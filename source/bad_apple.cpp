#include "StdAfx.h"
#include"bad_apple.h"

void bad_apple::start()
{
	FILE *open;
	fopen_s(&open, "AscPic.txt", "r");
	//��ȡ�ļ� 
	//int speed = 9;
	Sleep(50);
	PlaySound(L"BadApple.wav", NULL, SND_FILENAME | SND_ASYNC);//����badapple
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
		
		for (j = 0; j < 61; j++) //���һ�������ÿһ�� 
		{
			if (fgets(a, 162, open) == NULL) break; //���һ�е��ַ�������a�У�����ȡ�����˳����ѭ�� 
			screen->print_string(a, 160, 0, j);//����printchar��������ָ��λ���ϴ�ӡ�ַ���ʹ��û��ˢ�¸о� 
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
		//Sleep(s);//����ͣ��ʱ��
	}
	system("pause");
}