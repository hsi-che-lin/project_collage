#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

// load an image
int main(void)
{
	string path;
	Mat img;
	path = "..\\..\\..\\Resources\\test.jpg";
	img = imread(path);
	if (!img.data) {
		cout << "Image not loaded";
		return -1;
	}
	imshow("Image", img);
	waitKey(0);
	return 0;
}

//	// load a video
//	int main(void)
//	{
//		string path = "..\\..\\..\\Resources\\test_video.mp4";
//		VideoCapture cap(path);
//		Mat img;
//		bool done = 0;
//	
//		do {
//			if (cap.read(img)) {
//				imshow("Image", img);
//				waitKey(1);
//			} else {
//				done = 1;
//				cout << "video finished\n";
//			}
//		} while (!done);
//	
//		return 0;
//	}
