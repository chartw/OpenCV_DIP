#pragma once
#include "Gaussian.h"

Mat mySampling(Mat src)
{
	int width = src.cols / 2;
	int height = src.rows / 2;
	Mat dst(height, width, CV_8UC3);
	uchar* srcData = src.data;
	uchar* dstData = dst.data;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			for (int c = 0; c < 3; c++)
			{
				dstData[y * width * 3 + x * 3 + c] = srcData[(y * 2) * (width * 2) * 3 + (x * 2) * 3 + c];
			}
		}
	}
	return dst;

}

vector<Mat> myGaussianPyramid(Mat src)
{
	vector<Mat> Vec;

	Vec.push_back(src);
	for (int i = 0; i < 4; i++)
	{
		src = mySampling(src);
		src = myGaussianFilter(src, 1);
		Vec.push_back(src);
	}
	return Vec;
}

vector<Mat> myLaplacianPyramid(Mat src)
{
	vector<Mat> Vec;

	for (int i = 0; i < 4; i++)
	{
		if (i != 3)
		{
			Mat highImg = src;

			src = mySampling(src);
			src = myGaussianFilter(src, 1);

			Mat lowImg = src;
			resize(lowImg, lowImg, highImg.size());
			Vec.push_back(highImg - lowImg + 128);	// 오버플로우 방지를 위해 128을 더함
		}
		else
		{
			Vec.push_back(src);
		}
	}
	return Vec;
}