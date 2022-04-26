#include<iostream>
#include<opencv2/opencv.hpp>
#include"windmillDemo.h"
#include<vector>
#include<string>

using namespace std;
using namespace cv;

int main()
{
	windmill wm;

	wm.input_video("D:/video/work.mp4");

	wm.demo();

	return 0;
}