#include "pch.h"

namespace luo
{
	enum InterpolationMethod
	{
		NEAREST_NEIGHBOR_INTERPOLATION,
		BILINEAR_INTERPOLATION
	};

	void interpolation(const cv::Mat& ori, cv::Mat& res, float multiple, int method);


	enum ThresholdType
	{
		THRESH_OTSU,
		THRESH_BINARY,
		THRESH_BINARY_INV,
		THRESH_TRUNC,
		THRESH_TOZERO,
		THRESH_TOZERO_INV,
		THRESH_TRIANGLE
	};

	void threshold(const cv::Mat& ori, cv::Mat& res, int thresh, int maxval, int type);


	enum BlurMethod
	{
		MEAN_BLUR,
		MEDIAN_BLUR,
		GAUSSIAN_BLUR
	};

	void blur(const cv::Mat& ori, cv::Mat& res, cv::Size block_size, int method, double sigma_x = 0.0, double sigma_y = 0.0);
}

int main()
{
	cv::Mat mat = cv::imread("D:/testpic/cv2.PNG");
	if (mat.empty())
		return -1;

	//cv::cvtColor(mat, mat, cv::COLOR_BGR2GRAY);

	cv::imshow("mat", mat);

	cv::Mat cvbl;
	cv::blur(mat, cvbl, cv::Size(5, 5));
	cv::imshow("ms", cvbl);

	cv::Mat cvm;
	cv::medianBlur(mat, cvm, 5);
	cv::imshow("cms", cvm);

	cv::Mat blurs;
	luo::blur(mat, blurs, cv::Size(5, 5), luo::MEDIAN_BLUR);
	cv::imshow("mb", blurs);

	cv::waitKey(0);
}