#include "../include/ocv.h"
#include "../include/DFT.h"
#include "../include/PassFilter.h"
#include "../include/MagEdit.h"

int main() {
	//1
	Mat src = imread("img/einstein.jpg", 0); // �̹��� �б�

	Mat dst = doLPF(src);
	hconcat(src, dst, dst);

	imshow("LPF", dst); // �̹��� ���
	waitKey(0); // Ű �Է� ���(0: Ű�� �Էµ� �� ���� ���α׷� ����)
	destroyAllWindows(); // �̹��� ���â ����

	dst = doHPF(src);
	imshow("HPF", dst); // �̹��� ���
	waitKey(0); // Ű �Է� ���(0: Ű�� �Էµ� �� ���� ���α׷� ����)
	destroyAllWindows(); // �̹��� ���â ����

	dst = doBPF(src);
	imshow("BPF", dst); // �̹��� ���
	waitKey(0); // Ű �Է� ���(0: Ű�� �Էµ� �� ���� ���α׷� ����)
	destroyAllWindows(); // �̹��� ���â ����

	//2
	src = imread("img/stripe.jpg", 0); // �̹��� �б�

	dst = freqSobel(src);

	imshow("freq_sobel", dst);

	waitKey(0); // Ű �Է� ���(0: Ű�� �Էµ� �� ���� ���α׷� ����)
	destroyAllWindows(); // �̹��� ���â ����


	//3
	src = imread("img/flick.jpg", 0); // �̹��� �б�
	dst = rmFlick(src);
	imshow("PF", dst); // �̹��� ���

	waitKey(0); // Ű �Է� ���(0: Ű�� �Էµ� �� ���� ���α׷� ����)
	destroyAllWindows(); // �̹��� ���â ����

	return 0;
}
