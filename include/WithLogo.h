#pragma once
#include "ocv.h"

void MakeMask(Mat img)
{
	for (int i = 0; i < img.cols; i++) {
		for (int j = 0; j < img.rows; j++) {
			if (img.channels() == 1) {
				if (img.at<uchar>(j, i) > 180)
					img.at<uchar>(j, i) = 0;
				else
					img.at<uchar>(j, i) = 255;

			}
		}
	}
}

void InsertLogo(Mat img, Mat logo)
{
	int rows = logo.rows;
	int cols = logo.cols;
	int chs = logo.channels();

	Mat roi = img(Rect(img.cols / 4, img.rows * 1 / 2, logo.cols, logo.rows));
	// logo 사이즈만큼 영상에 roi 생성

	//imshow("roi", roi);

	Mat mask = imread("img/logo.jpg", 0);	//mask로 만들 logo 영상 read (1 ch)
	MakeMask(mask);						//1ch mask의 흰색 영역의 값을 0으로 변경
	//imshow("mask", mask);

	logo.copyTo(roi, mask);				//roi 영역에 logo 영상(3ch)과 mask를 논리 곱 연산

	imshow("with logo", img);
}