// July, 3, 2021

#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main(void)
{
	int width;
	int height;
	string path = "..\\..\\..\\Resources\\test.jpg";
	Mat img;
	int i = 0;

	img = imread(path);
	width = img.size().width;
	height = img.size().height;

	while (width != 1 || height != 1) {
		if (width / 2 == 0) width = 1;
		else width /= 2;
		if (height / 2 == 0) height = 1;
		else height /= 2;

		resize(img, img, Size(width, height), 0, 0, INTER_AREA);

		if (++i % 2)
			imshow("Image", img);
		waitKey(0);
	}

	cout << (int)img.data[0] << " " << (int)img.data[1] << " " << (int)img.data[2] << '\n';

	imwrite("..\\..\\..\\Resources\\condensed.png", img);

	return 0;
}

