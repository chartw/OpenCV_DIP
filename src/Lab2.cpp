#include "../include/ocv.h"
#include "../include/Gaussian.h"
#include "../include/GradHist.h"
#include "../include/SpreadCount.h"
#include "../include/Sobel.h"
#include "../include/MakePy.h"


int main() {

	//1
	Mat src = imread("img/gear.jpg", 0); // 이미지 읽기
	Mat dst = myGaussianFilter(src, 1);
	Mat dst1 = myGaussianFilter(src, 10);

	hconcat(src, dst, dst);
	hconcat(dst, dst1, dst1);
	imshow("Gaussian", dst1); // 이미지 출력
	waitKey(0); // 키 입력 대기(0: 키가 입력될 때 까지 프로그램 멈춤)
	destroyWindow("Gaussian"); // 이미지 출력창 종료

	//2
	src = imread("img/gear.jpg", 0); // 이미지 읽기
	dst = myGaussianFilter(src, 2);

	Mat hst1 = GetHistogram(src);
	Mat hst2 = GetHistogram(dst);
	resize(hst1, hst1, Size(src.cols, src.rows));
	resize(hst2, hst2, Size(src.cols, src.rows));

	hconcat(src, hst1, hst1);
	hconcat(dst, hst2, hst2);
	vconcat(hst1, hst2, hst2);
	imshow("Histogram", hst2);
	waitKey(0);
	destroyWindow("Histogram"); // 이미지 출력창 종료

	//3
	src = imread("img/gear.jpg", 0); // 이미지 읽기
	SpreadPoints(src, 500, 0);
	SpreadPoints(src, 500, 1);
	dst = myGaussianFilter(src, 2);
	
	hconcat(src, dst, dst);
	imshow("Noise Filtering", dst); // 이미지 출력
	waitKey(0); // 키 입력 대기(0: 키가 입력될 때 까지 프로그램 멈춤)
	destroyWindow("Noise Filtering"); // 이미지 출력창 종료

	//4
	src = imread("img/gear.jpg", 0); // 이미지 읽기
	dst = mySobelFilter(src, 0);
	dst1 = mySobelFilter(src, 1);
	Mat dst2 = mySobelFilter(src, 2);

	hconcat(dst, dst1, dst1);
	hconcat(dst1, dst2, dst2);

	imshow("Source", src); // 이미지 출력sss
	imshow("Sobel", dst2); // 이미지 출력
	waitKey(0); // 키 입력 대기(0: 키가 입력될 때 까지 프로그램 멈춤)
	destroyWindow("Source"); // 이미지 출력창 종료
	destroyWindow("Sobel"); // 이미지 출력창 종료

	//5
	src = imread("img/gear.jpg", 1); // 이미지 읽기
	vector<Mat> VecGauss = myGaussianPyramid(src);

	for (int i = 0; i < VecGauss.size(); i++)
	{
		string wname = "Gaussian Pyramid" + to_string(i);
		imshow(wname, VecGauss[i]); // 이미지 출력
	}
	waitKey(0); // 키 입력 대기(0: 키가 입력될 때 까지 프로그램 멈춤)

	for (int i = 0; i < VecGauss.size(); i++)
	{
		string wname = "Gaussian Pyramid" + to_string(i);
		destroyWindow(wname); // 이미지 출력창 종료
	}

	//6
	vector<Mat> VecLap = myLaplacianPyramid(src);
	reverse(VecLap.begin(), VecLap.end());

	for (int i = 0; i < VecLap.size(); i++)
	{
		string wname = "Lap Pyramid" + to_string(i);
		imshow(wname, VecLap[i]); // 이미지 출력
	}

	for (int i = 0; i < VecLap.size(); i++)
	{
		if (i == 0)
		{
			dst = VecLap[i];
		}
		else
		{
			resize(dst, dst, VecLap[i].size());
			dst = dst + VecLap[i] - 128;			// 오버플로우 방지를 위해 더했던 값을 빼줌
		}
		string wname = "Restore" + to_string(i);
		imshow(wname, dst);
	}
	waitKey(0);

	for (int i = 0; i < VecLap.size(); i++)
	{
		string wname = "Lap Pyramid" + to_string(i);
		destroyWindow(wname); // 이미지 출력창 종료

		wname = "Restore" + to_string(i);
		destroyWindow(wname); // 이미지 출력창 종료
	}

	return 0;
}