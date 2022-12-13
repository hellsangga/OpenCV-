#include "pch.h"

namespace luo
{
	enum interpolation_method
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


	enum AdaptiveThreshMethod
	{
		AT_MEAN,
		AT_GAUSSIAN
	};

	enum AdaptiveThreshType
	{
		AT_THRESH_BINARAY,
		AT_THRESH_BINARAY_INV
	};

	void adaptive_threshold(const cv::Mat& ori,
		cv::Mat& res,
		double maxval,
		int method,
		int type,
		int block_size,
		double k);
}

int main()
{
	cv::Mat mat = cv::imread("D:/testpic/cv2.PNG");
	if (mat.empty())
		return -1;

	cv::cvtColor(mat, mat, cv::COLOR_BGR2GRAY);

	cv::imshow("mat", mat);

	cv::Mat thresh1;
	luo::threshold(mat, thresh1, 100, 255, luo::THRESH_OTSU);
	cv::imshow("thresh1", thresh1);

	cv::Mat thresh2;
	luo::threshold(mat, thresh2, 100, 255, luo::THRESH_TRUNC);
	cv::imshow("thresh2", thresh2);

	cv::Mat ad;
	luo::adaptive_threshold(mat, ad, 255, luo::AT_MEAN, luo::AT_THRESH_BINARAY, 3, 1);
	cv::imshow("ad", ad);

	cv::Mat ad2;
	luo::adaptive_threshold(mat, ad2, 255, luo::AT_GAUSSIAN, luo::AT_THRESH_BINARAY, 3, 1);
	cv::imshow("ad2", ad2);

	cv::waitKey(0);
}