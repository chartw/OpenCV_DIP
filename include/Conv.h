#pragma once
#include "ocv.h"

int myKernelConv3x3(uchar* arr, int kernel[][3], int x, int y, int width, int height)
{
	int sum = 0;
	int sumKernel = 0;

	for (int j = -1; j <= 1; j++) {
		for (int i = -1; i <= 1; i++) {
			if ((y + j) >= 0 && (y + j) < height && (x + i) >= 0 && (x + i) < width)
				// 가장자리 연산 금지 조건문
			{
				sum += arr[(y + j) * width + (x + i)] * kernel[i + 1][j + 1];
				sumKernel += kernel[i + 1][j + 1];
			}
		}
	}
	if (sumKernel != 0) { return sum / sumKernel; }	// 정규화된 값
	else { return sum; }
}

int myKernelConv9x9(uchar* arr, int kernel[][9], int x, int y, int width, int height, int ch, int c = 0)
{
	int sum = 0;
	int sumKernel = 0;

	for (int j = -4; j <= 4; j++) {
		for (int i = -4; i <= 4; i++) {
			if ((y + j) >= 0 && (y + j) < height && (x + i) >= 0 && (x + i) < width)
				// 가장자리 연산 금지 조건문
			{
				if (ch == 1)
					sum += arr[(y + j) * width + (x + i)] * kernel[i + 4][j + 4];
				else if (ch == 3)
					sum += arr[(y + j) * width * 3 + (x + i) * 3 + c] * kernel[i + 4][j + 4];
				sumKernel += kernel[i + 4][j + 4];
			}
		}
	}
	if (sumKernel != 0) { return sum / sumKernel; }	// 정규화된 값
	else { return sum; }
}