#include"windmillDemo.h"
using namespace cv;

void windmill::input_video(string x)
{
	video.open(x);
	if (video.isOpened())
		{
			cout << "width=" << video.get(CAP_PROP_FRAME_WIDTH) << endl;
			cout << "height=" << video.get(CAP_PROP_FRAME_HEIGHT) << endl;
			cout << "fps=" << video.get(CAP_PROP_FPS) << endl;
			cout << "FPSS=" << video.get(CAP_PROP_FRAME_COUNT) << endl;
		}
		else
		{
			cout << x << endl;
			cout << "false" << endl;
		}

}

void windmill::demo()
{
	while (1)
	{
		video >> image;
		if (image.empty())
		{
			break;
		}
		namedWindow("show", WINDOW_AUTOSIZE);
		Mat result,img_blue;
		img_blue=get_bule2(image);
		result = FindAndDraw_contours(image,img_blue);
		imshow("show", result);
		//imshow("image", image);
		waitKey(1);
	}
}

Mat windmill::get_bule2(Mat& dst)
{
	Mat img;
	dst.copyTo(img);
	//imshow("img", img);
	
	vector<Mat> imgchannel;
	split(img, imgchannel);

	img = imgchannel.at(0)- imgchannel.at(2);

	inRange(img, Scalar(150), Scalar(255), img);

	return img;
}

Mat windmill::FindAndDraw_contours(Mat & img,Mat &dst)
{
	Mat result,img_blue;
	img.copyTo(result);
	dst.copyTo(img_blue);
	//imshow("img", img);

	//轮廓发现
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(img_blue,contours,hierarchy, RETR_EXTERNAL,CHAIN_APPROX_SIMPLE,Point());

	//int n = contours.size();
	//cout << n << endl;

	int area[20];
	//轮廓绘制
	for (int i = 0; i < contours.size(); i++)
	{
		//cout << hierarchy[i] << endl;
		area[i] = contourArea(contours[i]);
		//cout << area[i] << endl;
		if (area[i]<3000 && area[i]>500)
		{
			drawContours(result, contours, i, Scalar(0, 0, 255),3);

			Rect rect = boundingRect(contours[i]);
			//rectangle(result, rect, Scalar(0, 0, 255), 2, 8, 0);
			//获取中心点
			vector<Point2d> points;
			int x, y;
			x = rect.x + rect.width / 2;
			y = rect.y + rect.height / 2;
			Point2d a(x, y);
			//画园
			circle(result, a, 5, Scalar(0, 0, 255), -1);
			break;
		}
	}
	return result;
}


//useless
void windmill::input_image(string x)
{
	image = imread(x);
	cout << x << endl;
	if (image.empty())
	{
		cout << "false" << endl;
		exit(1);
	}
	namedWindow("image", WINDOW_NORMAL);
	cv::imshow("image", image);
}

void windmill::get_bule(Mat& dst)
{
	Mat image2;
	dst.copyTo(image2);
	Mat img_hsv,mask1,result;
	cvtColor(image2, img_hsv, COLOR_BGR2HSV);	//תhsv

	inRange(img_hsv, Scalar(110, 43, 30), Scalar(180, 255, 255), mask1);
	Mat kernel=getStructuringElement(MORPH_RECT, Size(7, 7), Point(-1,-1));
	Mat kernel2 = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	//imshow("mask", mask1);
	morphologyEx(mask1,mask1,MORPH_CLOSE, kernel,Point(),1);
	morphologyEx(mask1, mask1, MORPH_OPEN, kernel2, Point(), 1);

	//imshow("mask1", mask1);
	Canny(mask1, result, 20, 40);
	result.copyTo(image_blue);
	//imshow("result", result);
}

void windmill::show_video()
{
	Mat img;
	while (1)
	{
		video >> img;
		if (img.empty())
		{
			break;
		}
		namedWindow("show", WINDOW_AUTOSIZE);
		imshow("show", img);
		waitKey(1000 / video.get(CAP_PROP_FPS));
	}
}

void windmill::tryhsv()
{
	Mat img_hsv;
	cvtColor(image, img_hsv, COLOR_BGR2HSV);	//תhsv
	for (int i=10; i < 255; i += 10)
	{
		Mat mask1;
		inRange(img_hsv, Scalar(115, i, 35), Scalar(200, 255, 255), mask1);
		imshow("0", mask1);
		cout << i << endl;
		waitKey(2000);
	}
}

void windmill::drawapp(Mat result, Mat img)
{
	for (int i = 0; i < result.rows; i++)
	{
		if (i == result.rows - 1)
		{
			Vec2i point1 = result.at<Vec2i>(i);
			Vec2i point2 = result.at<Vec2i>(0);
			line(img, point1, point2, Scalar(0, 0, 255), 2, 8, 0);
		}
		Vec2i point1 = result.at<Vec2i>(i);
		Vec2i point2 = result.at<Vec2i>(i+1);
		line(img, point1, point2, Scalar(0, 0, 255), 2, 8, 0);
	}
}

