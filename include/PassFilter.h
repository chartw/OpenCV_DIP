#pragma once
#include "DFT.h"

Mat doLPF(Mat srcImg)
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

	Mat maskImg = Mat::zeros(magImg.size(), CV_32F);
	circle(maskImg, Point(maskImg.cols / 2, maskImg.rows / 2), 50, Scalar::all(1), -1, -1, 0);

	Mat magImg2;
	multiply(magImg, maskImg, magImg2);

	imshow("magimg1", magImg);
	imshow("magimg2", magImg2);

	normalize(magImg2, magImg2, (float)minVal, (float)maxVal, NORM_MINMAX);
	Mat complexImg2 = setComplex(magImg2, phaImg);
	Mat dstImg = doIdft(complexImg2);

	return dstImg;
}

Mat doHPF(Mat srcImg)
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
	circle(maskImg, Point(maskImg.cols / 2, maskImg.rows / 2), 50, Scalar::all(0), -1, -1, 0);

	Mat magImg2;
	multiply(magImg, maskImg, magImg2);

	imshow("magimg1", magImg);
	imshow("magimg2", magImg2);

	normalize(magImg2, magImg2, (float)minVal, (float)maxVal, NORM_MINMAX);
	Mat complexImg2 = setComplex(magImg2, phaImg);
	Mat dstImg = doIdft(complexImg2);

	return dstImg;
}

Mat doBPF(Mat srcImg)
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

	Mat maskImg = Mat::zeros(magImg.size(), CV_32F);
	circle(maskImg, Point(maskImg.cols / 2, maskImg.rows / 2), 50, Scalar::all(1), -1, -1, 0);
	circle(maskImg, Point(maskImg.cols / 2, maskImg.rows / 2), 20, Scalar::all(0), -1, -1, 0);

	Mat magImg2;
	multiply(magImg, maskImg, magImg2);

	imshow("magimg1", magImg);
	imshow("magimg2", magImg2);

	normalize(magImg2, magImg2, (float)minVal, (float)maxVal, NORM_MINMAX);
	Mat complexImg2 = setComplex(magImg2, phaImg);
	Mat dstImg = doIdft(complexImg2);

	return dstImg;
}