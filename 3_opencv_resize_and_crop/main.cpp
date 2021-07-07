#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main(void)
{
	string path = "..\\..\\..\\Resources\\test.jpg";
	Mat img;						// original image
	Mat img_resize;					// resized image
	Rect roi(600, 0, 300, 300);		// region of intrest
	Mat img_crop;					// cropped image
//	int re_hei = 200;
//	int re_wid;

	img = imread(path);

//	re_wid = (float)re_hei / img.size().height * img.size().width;

//	resize(img, img_resize, Size(re_wid, re_hei));	// resize with specified size
	resize(img, img_resize, Size(), 0.25, 0.25);	// resize with scaling
	img_crop = img(roi);							// cropping

//	cout << img.size << endl;						// print out the original size

	imshow("Image", img);							// show images
	imshow("Image Resize", img_resize);
	imshow("Image crop", img_crop);

	imwrite("..\\Resources\\smol.png", img_resize);

	waitKey(0);

	return 0;
}
