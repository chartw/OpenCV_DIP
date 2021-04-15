#pragma once
#include "ocv.h"

void SpreadPoints(Mat img, int num, int color = 0) {
	int count = 0;
	srand(time(NULL) * color);							//time(NULL)�� srand�Լ��� �õ�� �̿� 
	for (int i = 0; i < num; i++) {
		int x = rand() % img.cols;				//�ȼ��� ��ġ�� ������ ũ�� ������ �������� ����
		int y = rand() % img.rows;

		if (img.channels() == 1) {
			if (color == 0)
				img.at<uchar>(y, x) = 255;			// 1 ch ������ ���, ���õ� �ȼ����� ���(255)�� ����
			else
				img.at<uchar>(y, x) = 0;			// ���õ� �ȼ����� ������(0)���� ����
		}
		else {									// 3 ch ������ ���
			if (color == 0) {					//color==0 (Blue)�� ���, Blue ���� 255, �������� 0���� ����
				img.at<Vec3b>(y, x)[0] = 255;
				img.at<Vec3b>(y, x)[1] = 0;
				img.at<Vec3b>(y, x)[2] = 0;
			}
			else if (color == 1) {				//color==1 (Green)�� ���, Green���� 255, �������� 0���� ����
				img.at<Vec3b>(y, x)[1] = 255;
				img.at<Vec3b>(y, x)[0] = 0;
				img.at<Vec3b>(y, x)[2] = 0;
			}
			else if (color == 2) {				//color==2 (Red)�� ���, Red���� 255, �������� 0���� ����
				img.at<Vec3b>(y, x)[2] = 255;
				img.at<Vec3b>(y, x)[0] = 0;
				img.at<Vec3b>(y, x)[1] = 0;
			}
		}
	}
}

void CountPoints(Mat img) {
	int count[3] = { 0 };
	int pointcolor[3] = { 0 };
	for (int i = 0; i < img.cols; i++) {				//������ �ʺ� ��ŭ �ݺ�
		for (int j = 0; j < img.rows; j++) {			//������ ���̰� ��ŭ �ݺ�
			for (int k = 0; k < 3; k++) {
				pointcolor[k] = img.at<Vec3b>(j, i)[k];	//�ȼ��� RGB ���� ����
			}
			if (pointcolor[2] == 255 && pointcolor[1] == 0 && pointcolor[0] == 0)		//���� R�� ���� 255 �̸�
				count[2]++;																//R count++
			else if (pointcolor[2] == 0 && pointcolor[1] == 255 && pointcolor[0] == 0)	//���� G�� ���� 255 �̸�
				count[1]++;																//G count++
			else if (pointcolor[2] == 0 && pointcolor[1] == 0 && pointcolor[0] == 255)	//���� B�� ���� 255 �̸�
				count[0]++;																//B count++
		}
	}
	// ���� ���
	cout << "red point number : " << count[2] << "\n";
	cout << "green point number : " << count[1] << "\n";
	cout << "blue point number : " << count[0] << "\n";
}