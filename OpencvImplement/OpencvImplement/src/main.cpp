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


<<<<<<< HEAD
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
=======
	enum BlurMethod
	{
		MEAN_BLUR,
		MEDIAN_BLUR,
		GAUSSIAN_BLUR
	};

	void blur(const cv::Mat& ori, cv::Mat& res, cv::Size block_size, int method, double sigma_x = 0.0, double sigma_y = 0.0);
>>>>>>> c79f385659f53174865a35e864f34edb947752dc
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

	cv::Mat ad;
	luo::adaptive_threshold(mat, ad, 255, luo::AT_MEAN, luo::AT_THRESH_BINARAY, 3, 1);
	cv::imshow("ad", ad);

	cv::Mat ad2;
	luo::adaptive_threshold(mat, ad2, 255, luo::AT_GAUSSIAN, luo::AT_THRESH_BINARAY, 3, 1);
	cv::imshow("ad2", ad2);

	cv::waitKey(0);
}