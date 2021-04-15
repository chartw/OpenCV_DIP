#pragma once
#include "Conv.h"

Mat mySobelFilter(Mat src, int flag)
{
	//45µµ
	int kernelRT[3][3] = { -2, -1, 0,
							-1,  0, 1,
							 0,  1, 2 };
	//135µµ
	int kernelRB[3][3] = { 0, -1, -2,
							1,  0, -1,
							2,  1,  0 };

	Mat dst(src.size(), CV_8UC1);
	uchar* srcData = src.data;
	uchar* dstData = dst.data;
	int width = src.cols;
	int height = src.rows;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int RT = abs(myKernelConv3x3(srcData, kernelRT, x, y, width, height));
			int RB = abs(myKernelConv3x3(srcData, kernelRB, x, y, width, height));
			if (flag == 0) dstData[y * width + x] = RT;
			else if (flag == 1) dstData[y * width + x] = RB;
			else dstData[y * width + x] = (RT + RB) / 2;
		}
	}
	return dst;
}