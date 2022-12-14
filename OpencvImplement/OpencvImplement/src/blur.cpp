#include "pch.h"

namespace luo
{
	void mean_blur(const cv::Mat& ori, cv::Mat& res, cv::Size block_size)
	{
		int rows = ori.rows;
		int cols = ori.cols * ori.channels();
		int channels = ori.channels();

		res = cv::Mat::zeros(ori.size(), ori.type());

		int rad_w = block_size.width / 2;
		int rad_h = block_size.height / 2;
		int block_total = block_size.width * block_size.height;

		cv::Mat copy;
		cv::copyMakeBorder(ori, copy, rad_h, rad_h, rad_w, rad_w, cv::BORDER_REPLICATE);

		int offet_h = rad_h;
		int offet_w = rad_w * channels;

		uchar* res_p;
		for (int y = offet_h; y < rows + offet_h; y++)
		{
			res_p = res.ptr<uchar>(y - offet_h);
			for (int x = offet_w; x < cols + offet_w; x += channels)
			{
				for (int c = 0; c < channels; c++)
				{
					float sum = 0.0;
					for (int b_y = y - offet_h; b_y <= y + offet_h; b_y++)
					{
						for (int b_x = x - offet_w; b_x <= x + offet_w; b_x += channels)
						{
							sum += static_cast<float>(copy.ptr<uchar>(b_y)[b_x + c]);
						}
					}

					res_p[x - offet_w + c] = round(sum / block_total);
				}
			}
		}
	}


	void median_blur(const cv::Mat& ori, cv::Mat& res, cv::Size block_size)
	{
		int rows = ori.rows;
		int cols = ori.cols * ori.channels();
		int channels = ori.channels();

		res = cv::Mat::zeros(ori.size(), ori.type());

		int rad_w = block_size.width / 2;
		int rad_h = block_size.height / 2;
		int block_total = block_size.width * block_size.height;

		cv::Mat copy;
		cv::copyMakeBorder(ori, copy, rad_h, rad_h, rad_w, rad_w, cv::BORDER_REPLICATE);

		int offet_h = rad_h;
		int offet_w = rad_w * channels;

		std::vector<int> block_val;
		block_val.resize(block_total);

		uchar* res_p;
		for (int y = offet_h; y < rows + offet_h; y++)
		{
			res_p = res.ptr<uchar>(y - offet_h);
			for (int x = offet_w; x < cols + offet_w; x += channels)
			{
				for (int c = 0; c < channels; c++)
				{
					int count = 0;
					for (int b_y = y - offet_h; b_y <= y + offet_h; b_y++)
					{
						for (int b_x = x - offet_w; b_x <= x + offet_w; b_x += channels)
						{
							int intensity = static_cast<int>(copy.ptr<uchar>(b_y)[b_x + c]);

							if (count == 0)
								block_val[0] = intensity;
							else
							{
								for (int i = count - 1; i >= 0; i--)
								{
									if (intensity >= block_val[i])
									{
										block_val[i + 1] = intensity;
										break;
									}

									int temp = block_val[i];
									block_val[i] = intensity;
									block_val[i + 1] = temp;
								}
							}

							count++;
 						}
					}

					res_p[x - offet_w + c] = block_val[block_total / 2];
				}
			}
		}
	}


	void gaussian_blur(const cv::Mat& ori, cv::Mat& res, cv::Size block_size, double sigma_x, double sigma_y = 0.0)
	{
		int rows = ori.rows;
		int cols = ori.cols * ori.channels();
		int channels = ori.channels();

		res = cv::Mat::zeros(ori.size(), ori.type());

		int rad_w = block_size.width / 2;
		int rad_h = block_size.height / 2;

		cv::Mat copy;
		cv::copyMakeBorder(ori, copy, rad_h, rad_h, rad_w, rad_w, cv::BORDER_REPLICATE);

		int offet_h = rad_h;
		int offet_w = rad_w * channels;
	}


	enum BlurMethod
	{
		MEAN_BLUR,
		MEDIAN_BLUR,
		GAUSSIAN_BLUR
	};

	void blur(const cv::Mat& ori, cv::Mat& res, cv::Size block_size, int method, double sigma_x = 0.0, double sigma_y = 0.0)
	{
		CV_Assert(ori.depth() == CV_8U);

		if (block_size.width < 3)
			block_size.width = 3;
		if (block_size.height < 3)
			block_size.height = 3;

		if (block_size.width % 2 == 0)
			block_size.width--;
		if (block_size.height % 2 == 0)
			block_size.height--;

		switch (method)
		{
		case MEAN_BLUR:
			mean_blur(ori, res, block_size);
			break;

		case MEDIAN_BLUR:
			median_blur(ori, res, block_size);
			break;

		case GAUSSIAN_BLUR:
			gaussian_blur(ori, res, block_size, sigma_x, sigma_y);
			break;

		default:
			break;
		}
	}
}