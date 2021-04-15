#include "../include/ocv.h"
#include "../include/Gaussian.h"
#include "../include/GradHist.h"
#include "../include/SpreadCount.h"
#include "../include/Sobel.h"
#include "../include/MakePy.h"


int main() {

	//1
	Mat src = imread("img/gear.jpg", 0); // �̹��� �б�
	Mat dst = myGaussianFilter(src, 1);
	Mat dst1 = myGaussianFilter(src, 10);

	hconcat(src, dst, dst);
	hconcat(dst, dst1, dst1);
	imshow("Gaussian", dst1); // �̹��� ���
	waitKey(0); // Ű �Է� ���(0: Ű�� �Էµ� �� ���� ���α׷� ����)
	destroyWindow("Gaussian"); // �̹��� ���â ����

	//2
	src = imread("img/gear.jpg", 0); // �̹��� �б�
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
	destroyWindow("Histogram"); // �̹��� ���â ����

	//3
	src = imread("img/gear.jpg", 0); // �̹��� �б�
	SpreadPoints(src, 500, 0);
	SpreadPoints(src, 500, 1);
	dst = myGaussianFilter(src, 2);
	
	hconcat(src, dst, dst);
	imshow("Noise Filtering", dst); // �̹��� ���
	waitKey(0); // Ű �Է� ���(0: Ű�� �Էµ� �� ���� ���α׷� ����)
	destroyWindow("Noise Filtering"); // �̹��� ���â ����

	//4
	src = imread("img/gear.jpg", 0); // �̹��� �б�
	dst = mySobelFilter(src, 0);
	dst1 = mySobelFilter(src, 1);
	Mat dst2 = mySobelFilter(src, 2);

	hconcat(dst, dst1, dst1);
	hconcat(dst1, dst2, dst2);

	imshow("Source", src); // �̹��� ���sss
	imshow("Sobel", dst2); // �̹��� ���
	waitKey(0); // Ű �Է� ���(0: Ű�� �Էµ� �� ���� ���α׷� ����)
	destroyWindow("Source"); // �̹��� ���â ����
	destroyWindow("Sobel"); // �̹��� ���â ����

	//5
	src = imread("img/gear.jpg", 1); // �̹��� �б�
	vector<Mat> VecGauss = myGaussianPyramid(src);

	for (int i = 0; i < VecGauss.size(); i++)
	{
		string wname = "Gaussian Pyramid" + to_string(i);
		imshow(wname, VecGauss[i]); // �̹��� ���
	}
	waitKey(0); // Ű �Է� ���(0: Ű�� �Էµ� �� ���� ���α׷� ����)

	for (int i = 0; i < VecGauss.size(); i++)
	{
		string wname = "Gaussian Pyramid" + to_string(i);
		destroyWindow(wname); // �̹��� ���â ����
	}

	//6
	vector<Mat> VecLap = myLaplacianPyramid(src);
	reverse(VecLap.begin(), VecLap.end());

	for (int i = 0; i < VecLap.size(); i++)
	{
		string wname = "Lap Pyramid" + to_string(i);
		imshow(wname, VecLap[i]); // �̹��� ���
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
			dst = dst + VecLap[i] - 128;			// �����÷ο� ������ ���� ���ߴ� ���� ����
		}
		string wname = "Restore" + to_string(i);
		imshow(wname, dst);
	}
	waitKey(0);

	for (int i = 0; i < VecLap.size(); i++)
	{
		string wname = "Lap Pyramid" + to_string(i);
		destroyWindow(wname); // �̹��� ���â ����

		wname = "Restore" + to_string(i);
		destroyWindow(wname); // �̹��� ���â ����
	}

	return 0;
}