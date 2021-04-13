// Computer Vision 2021 (P. Zanuttigh, code M. Carraro) - LAB 2

// copy and paste inside your code
#include <iostream>
#include <opencv2/opencv.hpp>
// hists = vector of 3 cv::mat of size nbins=256 with the 3 histograms

// e.g.: hists[0] = cv:mat of size 256 with the red histogram
//       hists[1] = cv:mat of size 256 with the green histogram
//       hists[2] = cv:mat of size 256 with the blue histogram

void showHistogram(std::vector<cv::Mat>& hists)
{
	// Min/Max computation
	double hmax[3] = { 0,0,0 };
	double min;
	cv::minMaxLoc(hists[0], &min, &hmax[0]);
	cv::minMaxLoc(hists[1], &min, &hmax[1]);
	cv::minMaxLoc(hists[2], &min, &hmax[2]);

	std::string wname[3] = { "blue", "green", "red" };
	cv::Scalar colors[3] = { cv::Scalar(255,0,0), cv::Scalar(0,255,0),
		cv::Scalar(0,0,255) };

	std::vector<cv::Mat> canvas(hists.size());

	// Display each histogram in a canvas
	for (int i = 0, end = hists.size(); i < end; i++)
	{
		canvas[i] = cv::Mat::ones(125, hists[0].rows, CV_8UC3);

		for (int j = 0, rows = canvas[i].rows; j < hists[0].rows - 1; j++)
		{
			cv::line(
				canvas[i],
				cv::Point(j, rows),
				cv::Point(j, rows - (hists[i].at<float>(j) * rows / hmax[i])),
				hists.size() == 1 ? cv::Scalar(200, 200, 200) : colors[i],
				1, 8, 0
			);
		}

		cv::imshow(hists.size() == 1 ? "value" : wname[i], canvas[i]);
	}
}

int main(int argc, char** argv)
{
	cv::Mat input_img = cv::imread("barbecue.png");

	/*cv::CommandLineParser parser(argc, argv, "{@input | barbecue.png | input image}");
	cv::Mat input_img = cv::imread(cv::samples::findFile(parser.get<cv::String>("@input")), cv::ImreadModes::IMREAD_COLOR);
	if (input_img.empty())
	{
	return EXIT_FAILURE;
	}*/

	std::vector<cv::Mat> bgr_planes;
	cv::split(input_img, bgr_planes);


	imshow("Source image", bgr_planes[0]);
	imshow("Source image1", bgr_planes[1]);
	imshow("Source image2", bgr_planes[2]);

	showHistogram(bgr_planes);




	int histSize = 256;
	float range[] = { 0,256 };
	const float* histRange = { range };
	bool uniform = true, accumulate = false;
	cv::Mat hists;
	cv::calcHist(&bgr_planes[0], 1, 0, cv::Mat(), b_hists[0], 1, &histSize, &histRange, uniform, accumulate);
	cv::calcHist(&bgr_planes[1], 1, 0, cv::Mat(), g_hists[1], 1, &histSize, &histRange, uniform, accumulate);
	cv::calcHist(&bgr_planes[2], 1, 0, cv::Mat(), r_hists[1], 1, &histSize, &histRange, uniform, accumulate);



	int hist_w = 512, hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);
	cv::Mat hists(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));
	cv::normalize(b_hist, b_hist, 0, hists.rows, cv::NORM_MINMAX, -1, cv::Mat());
	cv::normalize(g_hist, g_hist, 0, hists.rows, cv::NORM_MINMAX, -1, cv::Mat());
	cv::normalize(r_hist, r_hist, 0, hists.rows, cv::NORM_MINMAX, -1, cv::Mat());

	

	

	/*
	for (int i = 1; i < histSize; i++)
	{
	line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
	Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
	Scalar(255, 0, 0), 2, 8, 0);
	line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
	Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))),
	Scalar(0, 255, 0), 2, 8, 0);
	line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
	Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))),
	Scalar(0, 0, 255), 2, 8, 0);
	}
	imshow("Source image", src);
	imshow("calcHist Demo", histImage);
	waitKey();
	*/

	//cv::Mat input_img = cv::imread("barbecue.png");

	//cv::resize(input_img, input_img, cv::Size(input_img.cols / 2.0, input_img.rows / 2.0));
	//cv::imshow("img", input_img);
	//cv::setMouseCallback("img", onMouse, (void*)&input_img);

	cv::waitKey(0);
	cv::destroyAllWindows();
	return 0;
}