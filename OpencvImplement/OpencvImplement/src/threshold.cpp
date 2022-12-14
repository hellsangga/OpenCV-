#include "pch.h"

namespace luo
{
	void threshold_otsu(const cv::Mat& ori, cv::Mat& res, int maxval)
	{
		int rows = ori.rows;
		int cols = ori.cols;

		res = cv::Mat::zeros(ori.size(), CV_8UC1);

		double total = rows * cols;

		int count[256] = { 0 };

		for (int i = 0; i < rows; i++)
		{
			const uchar* p = ori.ptr<uchar>(i);
			for (int j = 0; j < cols; j++)
			{
				int intensity = p[j];
				count[intensity]++;
			}
		}

		double max = 0.0;
		int mark = 0;
		for (int t = 0; t < 256; t++)
		{
			int n1 = 0, n2 = 0;
			double p1, p2;

			for (int i = 0; i < t; i++)
			{
				n1 += count[i];
			}

			n2 = rows * cols - n1;

			p1 = n1 / total;
			p2 = n2 / total;

			double m1 = 0.0, m2 = 0.0;
			for (int v = 0; v < t; v++)
			{
				m1 += v * (count[v] / total);
			}
			m1 = m1 / p1;

			for (int v = t; v < 256; v++)
			{
				m2 += v * (count[v] / total);
			}
			m2 = m2 / p2;

			double temp = p1 * p2 * (m1 - m2) * (m1 - m2);

			if (max < temp)
			{
				max = temp;
				mark = t;
			}
		}

		uchar* res_p;
		for (int i = 0; i < rows; i++)
		{
			const uchar* ori_p = ori.ptr<uchar>(i);
			res_p = res.ptr<uchar>(i);
			for (int j = 0; j < cols; j++)
			{
				int intensity = ori_p[j];

				if (intensity <= mark)
					res_p[j] = 0;
				else
					res_p[j] = (uchar)maxval;
			}
		}
	}


	void threshold_binary(const cv::Mat& ori, cv::Mat& res, int thresh, int maxval)
	{
		int rows = ori.rows;
		int cols = ori.cols;

		res = cv::Mat::zeros(ori.size(), CV_8UC1);

		uchar* res_p;
		for (int i = 0; i < rows; i++)
		{
			const uchar* ori_p = ori.ptr<uchar>(i);
			res_p = res.ptr<uchar>(i);
			for (int j = 0; j < cols; j++)
			{
				int intensity = ori_p[j];

				if (intensity <= thresh)
					res_p[j] = 0;
				else
					res_p[j] = (uchar)maxval;
			}
		}
	}


	void threshold_binary_inv(const cv::Mat& ori, cv::Mat& res, int thresh, int maxval)
	{
		int rows = ori.rows;
		int cols = ori.cols;

		res = cv::Mat::zeros(ori.size(), CV_8UC1);

		uchar* res_p;
		for (int i = 0; i < rows; i++)
		{
			const uchar* ori_p = ori.ptr<uchar>(i);
			res_p = res.ptr<uchar>(i);
			for (int j = 0; j < cols; j++)
			{
				int intensity = ori_p[j];

				if (intensity > thresh)
					res_p[j] = 0;
				else
					res_p[j] = (uchar)maxval;
			}
		}
	}

	
	void threshold_trunc(const cv::Mat& ori, cv::Mat& res, int thresh)
	{
		int rows = ori.rows;
		int cols = ori.cols;

		res = cv::Mat::zeros(ori.size(), CV_8UC1);

		uchar* res_p;
		for (int i = 0; i < rows; i++)
		{
			const uchar* ori_p = ori.ptr<uchar>(i);
			res_p = res.ptr<uchar>(i);
			for (int j = 0; j < cols; j++)
			{
				int intensity = ori_p[j];

				if (intensity > thresh)
					res_p[j] = (uchar)thresh;
				else
					res_p[j] = (uchar)intensity;
			}
		}
	}

	
	void threshold_tozero(const cv::Mat& ori, cv::Mat& res, int thresh)
	{
		int rows = ori.rows;
		int cols = ori.cols;

		res = cv::Mat::zeros(ori.size(), CV_8UC1);

		uchar* res_p;
		for (int i = 0; i < rows; i++)
		{
			const uchar* ori_p = ori.ptr<uchar>(i);
			res_p = res.ptr<uchar>(i);
			for (int j = 0; j < cols; j++)
			{
				int intensity = ori_p[j];

				if (intensity < thresh)
					res_p[j] = 0;
				else
					res_p[j] = (uchar)intensity;
			}
		}
	}

	
	void threshold_tozero_inv(const cv::Mat& ori, cv::Mat& res, int thresh)
	{
		int rows = ori.rows;
		int cols = ori.cols;

		res = cv::Mat::zeros(ori.size(), CV_8UC1);

		uchar* res_p;
		for (int i = 0; i < rows; i++)
		{
			const uchar* ori_p = ori.ptr<uchar>(i);
			res_p = res.ptr<uchar>(i);
			for (int j = 0; j < cols; j++)
			{
				int intensity = ori_p[j];

				if (intensity > thresh)
					res_p[j] = 0;
				else
					res_p[j] = (uchar)intensity;
			}
		}
	}


	void threshold_triangle(const cv::Mat& ori, cv::Mat& res, int maxval)
	{
		int rows = ori.rows;
		int cols = ori.cols;

		res = cv::Mat::zeros(ori.size(), CV_8UC1);

		int count[256] = { 0 };

		for (int i = 0; i < rows; i++)
		{
			const uchar* p = ori.ptr<uchar>(i);
			for (int j = 0; j < cols; j++)
			{
				int intensity = p[j];
				count[intensity]++;
			}
		}

		int max_val = 0;
		int max_i = 0, left_i = -1, right_i = 256;
		bool li_find = false, ri_find = false;
		for (int i = 0; i < 256; i++)
		{
			if (max_val < count[i])
			{
				max_val = count[i];
				max_i = i;
			}

			if (count[i] == 0 && !li_find)
				left_i = i;
			else
				li_find = true;

			if (count[255 - i] == 0 && !ri_find)
				right_i = 255 - i;
			else
				ri_find = true;
		}

		int k, b, start, end;
		if (max_i - left_i >= right_i - max_i)
		{
			k = (count[max_i] - 0) / (max_i - left_i);
			b = -k * left_i;
			start = left_i + 1;
			end = max_i;
		}
		else
		{
			k = (count[max_i] - 0) / (max_i - right_i);
			b = -k * right_i;
			start = max_i + 1;
			end = right_i;
		}

		double max_distance = 0.0;
		int mark = 0;
		for (int i = start; i < end; i++)
		{
			double dis = abs(k * i - count[i] + b) / sqrt(k * k + 1);
			if (max_distance < dis)
			{
				max_distance = dis;
				mark = i;
			}
		}

		uchar* res_p;
		for (int i = 0; i < rows; i++)
		{
			const uchar* ori_p = ori.ptr<uchar>(i);
			res_p = res.ptr<uchar>(i);
			for (int j = 0; j < cols; j++)
			{
				int intensity = ori_p[j];

				if (intensity <= mark)
					res_p[j] = 0;
				else
					res_p[j] = (uchar)maxval;
			}
		}
	}


	enum ThresholdMethod
	{
		THRESH_OTSU,
		THRESH_BINARY,
		THRESH_BINARY_INV,
		THRESH_TRUNC,
		THRESH_TOZERO,
		THRESH_TOZERO_INV,
		THRESH_TRIANGLE
	};

	void threshold(const cv::Mat& ori, cv::Mat& res, int thresh, int maxval, int type)
	{
		CV_Assert(ori.type() == CV_8UC1);

		maxval = maxval <= 255 ? maxval : 255;
		maxval = maxval >= 0 ? maxval : 0;

		thresh = thresh <= 255 ? thresh : 255;
		thresh = thresh >= 0 ? thresh : 0;

		switch (type)
		{
		case THRESH_OTSU:
			threshold_otsu(ori, res, maxval);
			break;

		case THRESH_TRIANGLE:
			threshold_triangle(ori, res, maxval);
			break;

		case THRESH_BINARY:
			threshold_binary(ori, res, thresh, maxval);
			break;

		case THRESH_BINARY_INV:
			threshold_binary_inv(ori, res, thresh, maxval);
			break;

		case THRESH_TRUNC:
			threshold_trunc(ori, res, thresh);
			break;

		case THRESH_TOZERO:
			threshold_tozero(ori, res, thresh);
			break;

		case THRESH_TOZERO_INV:
			threshold_tozero_inv(ori, res, thresh);
			break;

		default:
			break;
		}
	}
}