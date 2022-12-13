#include "pch.h"

namespace luo
{
	enum interpolation_method
	{
		NEAREST_NEIGHBOR_INTERPOLATION,
		BILINEAR_INTERPOLATION
	};

	void interpolation(const cv::Mat& ori, cv::Mat& res, float multiple, int method);
}

int main()
{
	cv::Mat mat = cv::imread("D:/testpic/cv2.PNG");
	if (mat.empty())
		return -1;

	cv::imshow("mat", mat);

	cv::Mat res;
	luo::interpolation(mat, res, 1.5, luo::NEAREST_NEIGHBOR_INTERPOLATION);
	cv::imshow("res", res);

	cv::Mat res2;
	luo::interpolation(mat, res2, 1.5, luo::BILINEAR_INTERPOLATION);
	cv::imshow("res2", res2);

	cv::waitKey(0);
}