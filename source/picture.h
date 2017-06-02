#pragma once
#include"stdafx.h"


typedef unsigned int _WORD;
typedef unsigned long DWORD;
//�����ֺ�˫��

struct bmpheader {
	_WORD bfType;
	DWORD bfSize;
	_WORD bfReserved1;
	_WORD bfReserved2;
	DWORD bfOffBits;
};
//bmpͷ�ļ��Ľṹ

struct bmpinfo {
	DWORD  biSize;
	DWORD   biWidth;
	DWORD   biHeight;
	_WORD   biPlanes;
	_WORD   biBitCount;
	DWORD  biCompression;
	DWORD  biSizeImage;
	DWORD   biXPelsPerMeter;
	DWORD   biYPelsPerMeter;
	DWORD  biClrUsed;
	DWORD  biClrImportant;
};
//bmpͼƬ��Ϣ��ȡ�Ľṹ

class picture
{
private:
	FILE *open;
	bmpheader pictureheader;
	bmpinfo pictureinfo;
	unsigned long **t;
	void readbmpheader(); //��ȡͷ 
	void readbmpinfo();  //��ȡ��Ϣ 
	void read_data();  //������
public:
	picture(const char *_name)
	{
		fopen_s(&(this->open),_name, "rb");
		this->readbmpheader();
		this->readbmpinfo();
		unsigned int i;
		t = (unsigned long**)malloc(sizeof(unsigned long*)*(pictureinfo.biHeight + 10));
		for (i = 0; i < pictureinfo.biHeight + 10; i++)
		{
			t[i] = (unsigned long*)malloc(sizeof(unsigned long)*(pictureinfo.biWidth + 10));
		}
		//���öѷ�ʽֱ���������� 
		this->read_data();
	}
	~picture()
	{
		unsigned int i;
		for (i = 0; i < pictureinfo.biHeight + 10; i++)
		{
			free(t[i]);
		}
		free(t);
	}
	DWORD get_height()
	{
		return pictureinfo.biHeight;
	}
	DWORD get_width()
	{
		return pictureinfo.biWidth;
	}
	unsigned long ** get_data()
	{
		return t;
	}
};