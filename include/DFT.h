#pragma once
#include "ocv.h"

Mat doDft(Mat srcImg)
{
	Mat floatImg;
	srcImg.convertTo(floatImg, CV_32F);

	Mat complexImg;
	dft(floatImg, complexImg, DFT_COMPLEX_OUTPUT);

	return complexImg;
}

Mat myNormalize(Mat src)
{
	Mat dst;
	src.copyTo(dst);
	normalize(dst, dst, 0, 255, NORM_MINMAX); // ?ȼ??? 0~255?? ?????ǵ??? ?????? ?÷???
	dst.convertTo(dst, CV_8UC1);				//32F ?????? 8Bit 1channel ???????? ??ȯ

	return dst;
}

Mat getMagnitude(Mat complexImg)
{
	Mat planes[2];
	split(complexImg, planes);

	Mat magImg;
	magnitude(planes[0], planes[1], magImg);	//Magnitude ????
	magImg += Scalar::all(1);					//???? 1 ????
	log(magImg, magImg);

	return magImg;
}



Mat getPhase(Mat complexImg)
{
	Mat planes[2];
	split(complexImg, planes);

	Mat phaseImg;
	phase(planes[0], planes[1], phaseImg);	//Phase ????

	return phaseImg;
}

Mat centralize(Mat complex)
{
	Mat planes[2];
	split(complex, planes);
	int cx = planes[0].cols / 2;
	int cy = planes[1].rows / 2;

	Mat q0Re(planes[0], Rect(0, 0, cx, cy));
	Mat q1Re(planes[0], Rect(cx, 0, cx, cy));
	Mat q2Re(planes[0], Rect(0, cy, cx, cy));
	Mat q3Re(planes[0], Rect(cx, cy, cx, cy));

	Mat tmp;
	q0Re.copyTo(tmp);
	q3Re.copyTo(q0Re);
	tmp.copyTo(q3Re);
	q1Re.copyTo(tmp);
	q2Re.copyTo(q1Re);
	tmp.copyTo(q2Re);

	Mat q0Im(planes[1], Rect(0, 0, cx, cy));
	Mat q1Im(planes[1], Rect(cx, 0, cx, cy));
	Mat q2Im(planes[1], Rect(0, cy, cx, cy));
	Mat q3Im(planes[1], Rect(cx, cy, cx, cy));

	q0Im.copyTo(tmp);
	q3Im.copyTo(q0Im);
	tmp.copyTo(q3Im);
	q1Im.copyTo(tmp);
	q2Im.copyTo(q1Im);
	tmp.copyTo(q2Im);

	Mat centerComplex;
	merge(planes, 2, centerComplex);

	return centerComplex;
}

Mat setComplex(Mat mag, Mat phase)
{
	exp(mag, mag);
	mag -= Scalar::all(1);

	Mat planes[2];
	polarToCart(mag, phase, planes[0], planes[1]);

	Mat complexImg;
	merge(planes, 2, complexImg);

	return complexImg;
}

Mat doIdft(Mat complexImg)
{
	Mat idftcvt;
	idft(complexImg, idftcvt);

	Mat planes[2];
	split(idftcvt, planes);

	Mat dst;
	magnitude(planes[0], planes[1], dst);
	normalize(dst, dst, 255, 0, NORM_MINMAX);
	dst.convertTo(dst, CV_8UC1);

	return dst;
}

Mat padding(Mat img)
{
	int dftRows = getOptimalDFTSize(img.rows);
	int dftCols = getOptimalDFTSize(img.cols);

	Mat padded;
	copyMakeBorder(img, padded, 0, dftRows - img.rows, 0, dftCols - img.cols, BORDER_CONSTANT, Scalar::all(0));
	return padded;
}