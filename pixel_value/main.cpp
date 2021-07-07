// July, 5th, 2021 
// invastigate how Mat stores the data and try to read the pixel value of image

// #include <stdio.h>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

// #define SIMPLE_MATRIX
#define IMAGE

using namespace std;
using namespace cv;

#ifdef SIMPLE_MATRIX

int main(void)
{
	Mat matrix(3, 3, CV_8UC3, Scalar(1, 2, 3));

	line(matrix, Point(1, 0), Point(1, 2), Scalar(4, 5, 6));

//	cout << "matrix.dims: " << matrix.dims << '\n';
//	cout << "matrix.size[0]: " << matrix.size[0] << '\n';
//	cout << "matrix.size[1]: " << matrix.size[1] << '\n';
//	cout << "matrix.step[0]: " << matrix.step[0] << '\n';
//	cout << "matrix.step[1]: " << matrix.step[1] << '\n';
//	cout << "matrix.elemSize: " << matrix.elemSize() << '\n';
	
	cout << (int)matrix.data[0] << '\n';
	cout << (int)matrix.data[1] << '\n';
	cout << (int)matrix.data[2] << '\n';
	cout << (int)matrix.data[3] << '\n';
	cout << (int)matrix.data[4] << '\n';
	cout << (int)matrix.data[5] << '\n';

	return 0;
}

#endif

#ifdef IMAGE

int main(void)
{
	string path = "..\\..\\..\\Resources\\test.jpg";
	Mat img;

	img = imread(path);

//	cout << "img.dims: " << img.dims << '\n';
//	cout << "img.size[0]: " << img.size[0] << '\n';			// row = height
//	cout << "img.size[1]: " << img.size[1] << '\n';			// colum = width
//	cout << "img.step[0]: " << img.step[0] << '\n';			// == im.size[1] * img.step[1]
//	cout << "img.step[1]: " << img.step[1] << '\n';			// color channel
//	cout << "img.elemSize: " << img.elemSize() << '\n';
	
	cout << (int)img.data[0] << '\n';						// B
	cout << (int)img.data[1] << '\n';						// G
	cout << (int)img.data[2] << '\n';						// R
	cout << (int)img.data[(img.size[0] - 1) * img.step[0] + (img.size[1] - 1) * img.step[1]] << '\n';
	cout << (int)img.data[(img.size[0] - 1) * img.step[0] + (img.size[1] - 1) * img.step[1] + 1] << '\n';
	cout << (int)img.data[(img.size[0] - 1) * img.step[0] + (img.size[1] - 1) * img.step[1] + 2] << '\n';

	return 0;
}

#endif
