#pragma once
#include"stdafx.h"


typedef unsigned int _WORD;
typedef unsigned long DWORD;
//定义字和双字

struct bmpheader {
	_WORD bfType;
	DWORD bfSize;
	_WORD bfReserved1;
	_WORD bfReserved2;
	DWORD bfOffBits;
};
//bmp头文件的结构

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
//bmp图片信息获取的结构

class picture
{
private:
	FILE *open;
	bmpheader pictureheader;
	bmpinfo pictureinfo;
	unsigned long **t;
	void readbmpheader(); //读取头 
	void readbmpinfo();  //读取信息 
	void read_data();  //读数据
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
		//采用堆方式直接申请数组 
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