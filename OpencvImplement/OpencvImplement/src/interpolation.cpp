#include "pch.h"

namespace luo
{
	//×î½üÁÚ²åÖµ
	void nearest_neighbor_interpolation(const cv::Mat& ori, cv::Mat& res, float multiple)
	{
		CV_Assert(ori.depth() == CV_8U);

		int ori_width = ori.size().width;
		int ori_height = ori.size().height;

		float res_width = ori_width * multiple;
		float res_height = ori_height * multiple;

		if (res_width <= 10.0 || res_height <= 10.0)
			return;

		res = cv::Mat::zeros(round(res_height), round(res_width), ori.type());

		int rows = res.rows;
		int cols = res.cols * res.channels();
		int channels = res.channels();

		uchar* res_p;
		int x = 0, y = 0;
		for (int i = 0; i < rows; i++)
		{
			x = round((i * ori_height) / res_height);
			x = x < ori_height ? x : ori_height - 1;
			res_p = res.ptr<uchar>(i);
			for (int j = 0; j < cols; j += channels)
			{
				y = round(((j / channels) * ori_width) / res_width);
				y = y < ori_width ? y : ori_width - 1;
				for (int c = 0; c < channels; c++)
				{
					res_p[j + c] = ori.ptr<uchar>(x)[y * channels + c];
				}
			}
		}
	}
}

void test_interpolation()
{
	cv::Mat mat = cv::imread("D:/testpic/cv2.PNG");
	if (mat.empty())
		return;

	cv::imshow("mat", mat);

	cv::Mat res;
	luo::nearest_neighbor_interpolation(mat, res, 0.6);
	cv::imshow("res", res);
}