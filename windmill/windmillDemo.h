#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>
#include<string>
#include<vector>

using namespace std;
using namespace cv;

class windmill {
public:

	VideoCapture video;
	Mat image;

	void demo();
	void input_video(string x);
	Mat	get_bule2(Mat& dst);
	Mat FindAndDraw_contours(Mat &img,Mat& dst);

//useless
	void show_video();
	void tryhsv();
	void input_image(string x);
	void	get_bule(Mat& dst);
	void drawapp(Mat result, Mat img);

};