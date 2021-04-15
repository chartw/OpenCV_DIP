#include "../include/ocv.h"
#include "../include/SpreadCount.h"
#include "../include/GradHist.h"
#include "../include/WithLogo.h"

int main() {
	//1

	Mat src_img = imread("img/landing_gray.jpg", 1); // �̹��� �б�
	int num = 0;

	// �� ���� ���� point�� ���� �Է�
	for (int i = 2; i >= 0; i--) {
		if (i == 2) cout << "Select the number of red points\n";
		else if (i == 1) cout << "Select the number of green points\n";
		else if (i == 0) cout << "Select the number of blue points\n";

		cin >> num;
		SpreadPoints(src_img, num, i);
	}
	CountPoints(src_img);

	imshow("RGB Point", src_img); // �̹��� ���

	waitKey(0); // Ű �Է� ���(0: Ű�� �Էµ� �� ���� ���α׷� ����)
	destroyAllWindows(); // �̹��� ���â ����

	//2

	Mat src_img1 = imread("img/landing_gray.jpg", 0); // �̹��� �б�
	Mat src_img2 = imread("img/landing_gray.jpg", 0); // �̹��� �б�
	Mat src_img3 = imread("img/landing_gray.jpg", 0); // �̹��� �б�

	Gradation(src_img1, 1);
	Gradation(src_img2, 2);
	Mat his_img1 = GetHistogram(src_img1);
	Mat his_img2 = GetHistogram(src_img2);

	hconcat(src_img1, src_img2, src_img2);
	hconcat(src_img3, src_img2, src_img2);
	hconcat(his_img1, his_img2, his_img2);
	hconcat(GetHistogram(src_img3), his_img2, his_img2);

	imshow("����", src_img2); // �̹��� ���
	imshow("Histogram", his_img2); // �̹��� ���


	waitKey(0); // Ű �Է� ���(0: Ű�� �Էµ� �� ���� ���α׷� ����)
	destroyAllWindows(); // �̹��� ���â ����

	//3

	src_img1 = imread("img/mars.jpg", 1); // �̹��� �б�
	src_img2 = imread("img/vignetting.jpg", 1); // �̹��� �б�
	src_img3 = imread("img/logo.jpg", 1); // �̹��� �б�


	Mat dst1, dst2, dst3, dst4;
	resize(src_img2, src_img2, Size(src_img1.cols, src_img1.rows));
	subtract(src_img1, src_img2, dst1);

	InsertLogo(dst1, src_img3);


	waitKey(0); // Ű �Է� ���(0: Ű�� �Էµ� �� ���� ���α׷� ����)
	destroyAllWindows(); // �̹��� ���â ����


	return 0;
}
