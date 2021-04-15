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
	// logo �����ŭ ���� roi ����

	//imshow("roi", roi);

	Mat mask = imread("img/logo.jpg", 0);	//mask�� ���� logo ���� read (1 ch)
	MakeMask(mask);						//1ch mask�� ��� ������ ���� 0���� ����
	//imshow("mask", mask);

	logo.copyTo(roi, mask);				//roi ������ logo ����(3ch)�� mask�� �� �� ����

	imshow("with logo", img);
}