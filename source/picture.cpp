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
//��ȡ�ļ�ͷ

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
//��ȡ�ļ���Ϣ     

void picture::read_data()
{
	unsigned char b, g, r = 0;
	unsigned int i = 0;
	unsigned int j = 0;
	fseek(open, pictureheader.bfOffBits, SEEK_SET);
	//��λ�ļ������ݿ�ʼ��ƫ������

	unsigned int q;
	if ((pictureinfo.biWidth * 3) % 4 != 0)
	{
		q = 4 - ((pictureinfo.biWidth * 3) % 4);
	}
	else
	{
		q = 0;
	}
	//�����ļ��������Ƿ�����һ��������4����������������Ǽ���qΪ��Ҫ������ٸ��ֽڵ�0

	unsigned char test;
	//�ն�ȡ0
	DWORD x=0x0;

	for (j = pictureinfo.biHeight; j >= 1; j--)
	{
		for (i = 1; i <= pictureinfo.biWidth; i++)
		{

			fread(&b, 1, 1, open);
			fread(&g, 1, 1, open);
			fread(&r, 1, 1, open);
			x = (DWORD)((b << 16) + (g << 8) + r);
			//��ȡ��Ϣ���������� 
			t[j][i] = x;
		}
		for (i = 1; i <= q; i++) { fread(&test, 1, 1, open); }
		//��ȡΪ�˴�4�ı��������ڵ�00 
	}
	fclose(open);
	open = NULL;
}