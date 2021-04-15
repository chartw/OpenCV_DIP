#pragma once
#include "Conv.h"

double GaussianKernel(int x, int y, int sig) {
	/*2���� ����þ� ���� ����*/
	//sig = ǥ������, PI = ������
	double f1, f2, res;
	f1 = 1 / (2 * PI * pow(sig, 2));
	f2 = -(pow(x, 2) + pow(y, 2)) / (2 * pow(sig, 2));
	res = f1 * exp(f2);
	return round(res * 1000);
}


Mat myGaussianFilter(Mat srcImg, int sig) {
	int width = srcImg.cols;
	int height = srcImg.rows;
	int kernel[9][9] = { 0 };	//9*9 ����þȺ��� ����ũ 
	for (int i = 4; i >= -4; i--) {
		for (int j = -4; j <= 4; j++) {
			kernel[i + 4][j + 4] = int(GaussianKernel(i, j, sig));
			//ǥ������ sig�� ����þ� ���� ����ũ
		}
	}
	int ch = srcImg.channels();
	if (ch == 1)
	{
		Mat dstImg(srcImg.size(), CV_8UC1);

		uchar* srcData = srcImg.data;
		uchar* dstData = dstImg.data;
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				dstData[y * width + x] = myKernelConv9x9(srcData, kernel, x, y, width, height, ch);
				//srcImg�� ����þ� ���͸�
			}
		}

		return dstImg;
	}
	else if (ch == 3)
	{
		Mat dstImg(srcImg.size(), CV_8UC3);

		uchar* srcData = srcImg.data;
		uchar* dstData = dstImg.data;
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				for (int c = 0; c < 3; c++)
				{
					dstData[y * width * 3 + x * 3 + c] = myKernelConv9x9(srcData, kernel, x, y, width, height, ch, c);
					//srcImg�� ����þ� ���͸�
				}
			}
		}

		return dstImg;
	}
}