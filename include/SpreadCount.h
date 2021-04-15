#pragma once
#include "ocv.h"

void SpreadPoints(Mat img, int num, int color = 0) {
	int count = 0;
	srand(time(NULL) * color);							//time(NULL)를 srand함수의 시드로 이용 
	for (int i = 0; i < num; i++) {
		int x = rand() % img.cols;				//픽셀의 위치를 영상의 크기 내에서 무작위로 선택
		int y = rand() % img.rows;

		if (img.channels() == 1) {
			if (color == 0)
				img.at<uchar>(y, x) = 255;			// 1 ch 영상일 경우, 선택된 픽셀값을 흰색(255)로 설정
			else
				img.at<uchar>(y, x) = 0;			// 선택된 픽셀값을 검은색(0)으로 설정
		}
		else {									// 3 ch 영상일 경우
			if (color == 0) {					//color==0 (Blue)일 경우, Blue 값을 255, 나머지는 0으로 설정
				img.at<Vec3b>(y, x)[0] = 255;
				img.at<Vec3b>(y, x)[1] = 0;
				img.at<Vec3b>(y, x)[2] = 0;
			}
			else if (color == 1) {				//color==1 (Green)일 경우, Green값을 255, 나머지는 0으로 설정
				img.at<Vec3b>(y, x)[1] = 255;
				img.at<Vec3b>(y, x)[0] = 0;
				img.at<Vec3b>(y, x)[2] = 0;
			}
			else if (color == 2) {				//color==2 (Red)일 경우, Red값을 255, 나머지는 0으로 설정
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
	for (int i = 0; i < img.cols; i++) {				//영상의 너비값 만큼 반복
		for (int j = 0; j < img.rows; j++) {			//영상의 높이값 만큼 반복
			for (int k = 0; k < 3; k++) {
				pointcolor[k] = img.at<Vec3b>(j, i)[k];	//픽셀의 RGB 값을 저장
			}
			if (pointcolor[2] == 255 && pointcolor[1] == 0 && pointcolor[0] == 0)		//만약 R의 값만 255 이면
				count[2]++;																//R count++
			else if (pointcolor[2] == 0 && pointcolor[1] == 255 && pointcolor[0] == 0)	//만약 G의 값만 255 이면
				count[1]++;																//G count++
			else if (pointcolor[2] == 0 && pointcolor[1] == 0 && pointcolor[0] == 255)	//만약 B의 값만 255 이면
				count[0]++;																//B count++
		}
	}
	// 개수 출력
	cout << "red point number : " << count[2] << "\n";
	cout << "green point number : " << count[1] << "\n";
	cout << "blue point number : " << count[0] << "\n";
}