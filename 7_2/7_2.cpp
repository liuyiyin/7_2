// 7_2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat src = cv::imread("D:\\metal-part-distorted-03.png", 1); 
	cv::Mat canny;
	Canny(src, canny, 20, 170);
	std::vector<cv::Vec2f> lines;
	cv::HoughLines(canny, lines, 1, CV_PI / 180, 90);
	std::vector<cv::Vec2f>::iterator it = lines.begin();
	for(; it != lines.end(); ++it) {
		float rho = (*it)[0], theta = (*it)[1];
		cv::Point pt1, pt2;
		double a = cos(theta);
		double b = sin(theta);
		double x0 = a*rho;
		double y0 = b*rho;
		pt1.x = cv::saturate_cast<int>(x0 + 1000 * (-b));
		pt1.y = cv::saturate_cast<int>(y0 + 1000 * (a));
		pt2.x = cv::saturate_cast<int>(x0 - 1000 * (-b));
		pt2.y = cv::saturate_cast<int>(y0 - 1000 * (a));
		cv::line(src, pt1, pt2, cv::Scalar(0, 0, 255), 1, CV_AA);
	}

	cv::imshow("canny", canny);
	cv::imshow("src", src);
	waitKey(0);
    return 0;
}

