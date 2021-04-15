#include "../include/ocv.h"
#include "../include/DFT.h"
#include "../include/PassFilter.h"
#include "../include/MagEdit.h"

int main() {
	//1
	Mat src = imread("img/einstein.jpg", 0); // 이미지 읽기

	Mat dst = doLPF(src);
	hconcat(src, dst, dst);

	imshow("LPF", dst); // 이미지 출력
	waitKey(0); // 키 입력 대기(0: 키가 입력될 때 까지 프로그램 멈춤)
	destroyAllWindows(); // 이미지 출력창 종료

	dst = doHPF(src);
	imshow("HPF", dst); // 이미지 출력
	waitKey(0); // 키 입력 대기(0: 키가 입력될 때 까지 프로그램 멈춤)
	destroyAllWindows(); // 이미지 출력창 종료

	dst = doBPF(src);
	imshow("BPF", dst); // 이미지 출력
	waitKey(0); // 키 입력 대기(0: 키가 입력될 때 까지 프로그램 멈춤)
	destroyAllWindows(); // 이미지 출력창 종료

	//2
	src = imread("img/stripe.jpg", 0); // 이미지 읽기

	dst = freqSobel(src);

	imshow("freq_sobel", dst);

	waitKey(0); // 키 입력 대기(0: 키가 입력될 때 까지 프로그램 멈춤)
	destroyAllWindows(); // 이미지 출력창 종료


	//3
	src = imread("img/flick.jpg", 0); // 이미지 읽기
	dst = rmFlick(src);
	imshow("PF", dst); // 이미지 출력

	waitKey(0); // 키 입력 대기(0: 키가 입력될 때 까지 프로그램 멈춤)
	destroyAllWindows(); // 이미지 출력창 종료

	return 0;
}
