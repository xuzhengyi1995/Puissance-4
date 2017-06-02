#include"stdafx.h"
#include"picture.h"

void picture::readbmpheader()
{
	fread(&pictureheader.bfType, 2, 1, open);
	fread(&pictureheader.bfSize, 4, 1, open);
	fread(&pictureheader.bfReserved1, 2, 1, open);
	fread(&pictureheader.bfReserved2, 2, 1, open);
	fread(&pictureheader.bfOffBits, 4, 1, open);
}
//读取文件头

void picture::readbmpinfo()
{
	fread(&pictureinfo.biSize, 4, 1, open);
	fread(&pictureinfo.biWidth, 4, 1, open);
	fread(&pictureinfo.biHeight, 4, 1, open);
	fread(&pictureinfo.biPlanes, 2, 1, open);
	fread(&pictureinfo.biBitCount, 2, 1, open);
	fread(&pictureinfo.biCompression, 4, 1, open);
	fread(&pictureinfo.biSizeImage, 4, 1, open);
	fread(&pictureinfo.biXPelsPerMeter, 4, 1, open);
	fread(&pictureinfo.biYPelsPerMeter, 4, 1, open);
	fread(&pictureinfo.biClrUsed, 4, 1, open);
	fread(&pictureinfo.biClrImportant, 4, 1, open);
}
//读取文件信息     

void picture::read_data()
{
	unsigned char b, g, r = 0;
	unsigned int i = 0;
	unsigned int j = 0;
	fseek(open, pictureheader.bfOffBits, SEEK_SET);
	//定位文件到数据开始的偏移量处

	unsigned int q;
	if ((pictureinfo.biWidth * 3) % 4 != 0)
	{
		q = 4 - ((pictureinfo.biWidth * 3) % 4);
	}
	else
	{
		q = 0;
	}
	//检查该文件的数据是否满足一行数据是4的整倍数，如果不是计算q为需要补足多少个字节的0

	unsigned char test;
	//空读取0
	DWORD x=0x0;

	for (j = pictureinfo.biHeight; j >= 1; j--)
	{
		for (i = 1; i <= pictureinfo.biWidth; i++)
		{

			fread(&b, 1, 1, open);
			fread(&g, 1, 1, open);
			fread(&r, 1, 1, open);
			x = (DWORD)((b << 16) + (g << 8) + r);
			//读取信息并存入数组 
			t[j][i] = x;
		}
		for (i = 1; i <= q; i++) { fread(&test, 1, 1, open); }
		//读取为了凑4的倍数而存在的00 
	}
	fclose(open);
	open = NULL;
}