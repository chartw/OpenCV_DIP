#pragma once
#include "DFT.h"


Mat rmFlick(Mat srcImg)
{
	Mat padImg = padding(srcImg);
	Mat complexImg = doDft(padImg);
	Mat centerComplexImg = centralize(complexImg);
	Mat magImg = getMagnitude(centerComplexImg);
	Mat phaImg = getPhase(centerComplexImg);

	double minVal, maxVal;
	Point minLoc, maxLoc;
	minMaxLoc(magImg, &minVal, &maxVal, &minLoc, &maxLoc);
	normalize(magImg, magImg, 0, 1, NORM_MINMAX);

	Mat maskImg = Mat::ones(magImg.size(), CV_32F);
	line(maskImg, Point(maskImg.cols / 2, maskImg.rows / 2 - 7), Point(maskImg.cols / 2, maskImg.rows / 2 - 50), Scalar::all(0), 12, FILLED);
	line(maskImg, Point(maskImg.cols / 2, maskImg.rows / 2 + 7), Point(maskImg.cols / 2, maskImg.rows / 2 + 50), Scalar::all(0), 12, FILLED);

	Mat magImg2;
	multiply(magImg, maskImg, magImg2);

	imshow("magimg1", magImg);
	imshow("magimg2", magImg2);

	normalize(magImg2, magImg2, (float)minVal, (float)maxVal, NORM_MINMAX);
	Mat complexImg2 = setComplex(magImg2, phaImg);
	Mat dstImg = doIdft(complexImg2);

	return dstImg;
}

Mat freqSobel(Mat srcImg)
{
	Mat padImg = padding(srcImg);
	Mat complexImg = doDft(padImg);
	Mat centerComplexImg = centralize(complexImg);
	Mat magImg = getMagnitude(centerComplexImg);
	Mat phaImg = getPhase(centerComplexImg);

	double minVal, maxVal;
	Point minLoc, maxLoc;
	minMaxLoc(magImg, &minVal, &maxVal, &minLoc, &maxLoc);
	normalize(magImg, magImg, 0, 1, NORM_MINMAX);

	Mat maskX = Mat::zeros(magImg.size(), CV_32F);
	line(maskX, Point(maskX.cols / 2, 50), Point(maskX.cols / 2, maskX.rows / 2 - 75), Scalar::all(1), 75, FILLED);
	line(maskX, Point(maskX.cols / 2, maskX.rows - 50), Point(maskX.cols / 2, maskX.rows / 2 + 75), Scalar::all(1), 75, FILLED);

	Mat maskY = Mat::zeros(magImg.size(), CV_32F);
	line(maskY, Point(50, maskY.rows / 2), Point(maskY.cols / 2 - 75, maskY.rows / 2), Scalar::all(1), 75, FILLED);
	line(maskY, Point(maskY.cols - 50, maskY.rows / 2), Point(maskY.cols / 2 + 75, maskY.rows / 2), Scalar::all(1), 75, FILLED);

	Mat magX, magY;
	multiply(magImg, maskX, magX);
	multiply(magImg, maskY, magY);

	//divide(2, magX, magX);

	Mat rst;
	add(magX, magY, rst);
	hconcat(maskX, maskY, maskY);

	//imshow("magimg1", maskX);
	imshow("magimg2", maskY);
	imshow("magimg3", rst);


	normalize(rst, rst, (float)minVal, (float)maxVal, NORM_MINMAX);
	Mat complexImg2 = setComplex(rst, phaImg);
	Mat dstImg = doIdft(complexImg2);

	return dstImg;
}

Mat getmag(Mat srcImg)
{
	Mat padImg = padding(srcImg);
	Mat complexImg = doDft(padImg);
	Mat centerComplexImg = centralize(complexImg);
	Mat magImg = getMagnitude(centerComplexImg);
	Mat phaImg = getPhase(centerComplexImg);

	double minVal, maxVal;
	Point minLoc, maxLoc;
	minMaxLoc(magImg, &minVal, &maxVal, &minLoc, &maxLoc);
	normalize(magImg, magImg, 0, 1, NORM_MINMAX);

	return magImg;
}