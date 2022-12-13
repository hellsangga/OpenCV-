#include "pch.h"

int main()
{
	cv::Mat mat = cv::imread("testpic/cv2.PNG");
	if (mat.empty())
		std::cout << "empty\n";
	else
		cv::imshow("mat", mat);
	cv::waitKey(0);
}