#include "pch.h"

namespace luo
{
	void nearest_neighbor_interpolation(const cv::Mat& ori, cv::Mat& res, float multiple)
	{
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


	void bilinear_interpolation(const cv::Mat& ori, cv::Mat& res, float multiple)
	{
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
		float x = 0.0, y = 0.0, val = 0.0;
		int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
		int v11 = 0, v12 = 0, v21 = 0, v22 = 0;

		for (int i = 0; i < rows; i++)
		{
			y = (i * ori_height) / res_height;
			y1 = floor(y);
			y2 = ceil(y);
			y1 = y1 < ori_height ? y1 : ori_height - 1;
			y2 = y2 < ori_height ? y2 : ori_height - 1;

			res_p = res.ptr<uchar>(i);
			for (int j = 0; j < cols; j += channels)
			{
				x = ((j / channels) * ori_width) / res_width;
				x1 = floor(x);
				x2 = ceil(x);
				x1 = x1 < ori_width ? x1 : ori_width - 1;
				x2 = x2 < ori_width ? x2 : ori_width - 1;

				for (int c = 0; c < channels; c++)
				{
					if (y1 == y2 && x1 != x2)
					{
						v11 = ori.ptr<uchar>(y1)[x1 * channels + c];
						v12 = ori.ptr<uchar>(y1)[x2 * channels + c];
						val = v11 + ((v12 - v11) / (x2 - x1)) * (x - x1);
					}
					else if (x1 == x2 && y1 != y2)
					{
						v11 = ori.ptr<uchar>(y1)[x1 * channels + c];
						v21 = ori.ptr<uchar>(y2)[x1 * channels + c];
						val = v11 + ((v21 - v11) / (y2 - y1)) * (y - y1);
					}
					else if (x1 == x2 && y1 == y2)
					{
						val = ori.ptr<uchar>(y1)[x1 * channels + c];
					}
					else
					{
						v11 = ori.ptr<uchar>(y1)[x1 * channels + c];
						v12 = ori.ptr<uchar>(y1)[x2 * channels + c];
						v21 = ori.ptr<uchar>(y2)[x1 * channels + c];
						v22 = ori.ptr<uchar>(y2)[x2 * channels + c];

						float q1 = v11 + ((v12 - v11) / (x2 - x1)) * (x - x1);
						float q2 = v21 + ((v22 - v21) / (x2 - x1)) * (x - x1);

						val = q1 + ((q2 - q1) / (y2 - y1)) * (y - y1);
					}

					res_p[j + c] = round(val);
				}
			}
		}
	}

	enum interpolation_method
	{
		NEAREST_NEIGHBOR_INTERPOLATION,
		BILINEAR_INTERPOLATION
	};

	void interpolation(const cv::Mat& ori, cv::Mat& res, float multiple, int method)
	{
		CV_Assert(ori.depth() == CV_8U);

		switch (method)
		{
		case NEAREST_NEIGHBOR_INTERPOLATION:
			nearest_neighbor_interpolation(ori, res, multiple);
			break;
			
		case BILINEAR_INTERPOLATION:
			bilinear_interpolation(ori, res, multiple);
			break;

		default:
			break;
		}
	}
}