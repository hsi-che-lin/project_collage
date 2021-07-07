#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main(void)
{
	string path = "..\\..\\..\\Resources\\test.jpg";
	Mat img;			// original image
	Mat img_gray;		// gray scale image
	Mat img_blur;		// blurred image
	Mat img_canny;		// image after Canny edge detection
	Mat img_dil;		// dilation
	Mat img_ero;		// erosion
	Mat kernel;			// kernel for dilation and erosion

	img = imread(path);								// read image
	cvtColor(img, img_gray, COLOR_BGR2GRAY);		// convert from BGR to GRAY
	GaussianBlur(img, img_blur, Size(5, 5), 5, 0);	// blur the image
	Canny(img, img_canny, 200, 200);				// do Canny edge dectection

	kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(img_canny, img_dil, kernel);				// dilating
	erode(img_dil, img_ero, kernel);				// eroding

	imshow("Image", img);							// show the images
	imshow("ImageGray", img_gray);
	imshow("Image Blur", img_blur);
	imshow("Image Canny", img_canny);
	imshow("Image dilate", img_dil);
	imshow("Image erode", img_ero);

	waitKey(0);

	return 0;
}

