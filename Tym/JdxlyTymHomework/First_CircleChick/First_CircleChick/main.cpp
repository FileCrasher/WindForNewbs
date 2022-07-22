#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main(int argc, char* argv) {
	Mat src = imread("chicken.jpg");
	Mat dst;
	if (src.empty()) {
		cout << "can not find" << endl;
		return -1;
	}
	Mat src1;
	GaussianBlur(src, src1, Size(15, 15), 0, 0);
	Mat n[3];
	split(src1, n);
	dst = n[2] - n[0];
	threshold(dst, dst, 50, 255, 0);
	vector<vector<Point>>contours;
	findContours(dst, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	Scalar color(255, 0, 0);
	drawContours(src, contours, -1, color, 1, LINE_4);
	namedWindow("output");
	imshow("output", src);
	//��Ӿ���
	vector<Rect> boundRect(contours.size()); //������Ӿ��μ���
	vector<RotatedRect> box(contours.size());//������С��Ӿ��μ���
	Point2f rect[4];
	Mat dstImg = src.clone();
	for (int i = 0; i < contours.size(); i++) {
		box[i] = minAreaRect(Mat(contours[i]));
		circle(dstImg, Point(box[i].center.x, box[i].center.y), 5, Scalar(0, 255, 0), -1, 8);
		cout << box[i].center.x << " " << box[i].center.y << endl;
		box[i].points(rect);
		for (int j = 0; j < 4; j++) {
			line(dstImg, rect[i], rect[(j + 1) % 4], Scalar(0, 0, 255), 2, 8);
		}
	}
	imshow("dst", dstImg);
	waitKey(0);
	destroyAllWindows();
	return 0;
}