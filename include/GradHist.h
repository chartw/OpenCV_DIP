#pragma once
#include "ocv.h"

Mat GetHistogram(Mat& src) {
	Mat histogram;
	const int* ch_num = { 0 };
	float ch_range[] = { 0.0,255.0 };
	const float* ch_ranges = ch_range;
	int number_bins = 255;

	calcHist(&src, 1, ch_num, Mat(), histogram, 1, &number_bins, &ch_ranges);

	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / number_bins);

	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));
	normalize(histogram, histogram, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < number_bins; i++) {
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(histogram.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(histogram.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
	}
	return histImage;
}

void Gradation(Mat img, int dir) {
	int count[3] = { 0 };
	int pointcolor[3] = { 0 };
	for (int i = 0; i < img.rows; i++) {		//������ ���̸�ŭ �ݺ�
		for (int j = 0; j < img.cols; j++) {	//������ �ʺ�ŭ �ݺ�

			//������ �Ʒ��� ������ ��ο�����
			if (dir == 1)
			{
				if (img.at<uchar>(i, j) - i * 256 / img.rows < 0)
					img.at<uchar>(i, j) = 0;	//���� ������ ���� 0���� ������, 0���� ����
				else
					img.at<uchar>(i, j) -= i * 256 / img.rows;				//�ȼ������� i�� ����ϴ� ���� ����
			}

			//������ ���� ������ ��ο�����
			else
			{
				if (img.at<uchar>(i, j) - (img.rows - i) * 256 / img.rows < 0)
					img.at<uchar>(i, j) = 0;	//���� ������ ���� 0���� ������, 0���� ����
				else
					img.at<uchar>(i, j) -= (img.rows - i) * 256 / img.rows;	//�ȼ������� i�� ����ϴ� ���� ����
			}
		}
	}
}