#include "pch.h"

class Timer
{
public:
	Timer(std::string name)
	{
		m_name = name;
		m_start = std::chrono::system_clock::now();
		std::cout << m_name << " timer satrt\n";
	}

	~Timer()
	{
		auto end = std::chrono::system_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - m_start);

		std::cout << m_name << " usage_time: " << duration.count() << " ms\n";
	}

private:
	std::chrono::time_point<std::chrono::system_clock> m_start;
	std::string m_name;
};

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

	enum BlurMethod
	{
		MEAN_BLUR,
		MEDIAN_BLUR,
		GAUSSIAN_BLUR
	};

	void blur(const cv::Mat& ori, cv::Mat& res, cv::Size block_size, int method, double sigma_x = 0.0, double sigma_y = 0.0);

	void bilateral_filter(const cv::Mat& ori, cv::Mat& res, int d, double sigma_space, double sigma_color);
}

int main()
{
	cv::Mat mat = cv::imread("D:/testpic/cv7.PNG");
	if (mat.empty())
		return -1;

	//cv::cvtColor(mat, mat, cv::COLOR_BGR2GRAY);

	cv::imshow("mat", mat);

	{
		Timer t("bilateral_filter");
		cv::Mat gb;
		luo::bilateral_filter(mat, gb, 19, 23.0, 200);
		cv::imshow("gb", gb);
	}

	cv::Mat cvb;
	cv::bilateralFilter(mat, cvb, 19.0, 23.0, 200);
	cv::imshow("cvb", cvb);

	cv::waitKey(0);
}