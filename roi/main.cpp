// To Do: (1) you need to know difference between setTo(), copyTo() or other similar function
//			  if possible explore how exactly they work
//		  (2) what type after imread (can it be change when call imread)
//		  (3) use other way to implement and examine the efficiency (try to explore and use at())

#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <chrono>

using namespace std;
using namespace cv;

// #define COPYTO
#define CONCATE
// #define SETTO
// #define SIMPLE

#if defined(COPYTO)

int main(void)
{
	Mat img(Size(14 * 256, 32 * 144), CV_8UC3, Scalar(255, 0, 255));
	Mat unit;
	Mat unit_cvt;
	string path = "..\\..\\..\\Resources\\screenshots\\";
	string read_path;
	int i, j;

	auto start = chrono::steady_clock::now();

	for (i = 0; i < 14; i++) {
		for (j = 0; j < 32; j++) {
			read_path = path + to_string(i * 32 + j) + ".png";
			unit = imread(read_path);
			unit.convertTo(unit_cvt, CV_8UC3);				// this line is indispensable
			unit_cvt.copyTo(Mat(img, Rect(i * 256, j * 144, 256, 144)));
		}
	}

	imwrite("..\\..\\..\\Resources\\roi.png", img);

	auto end = chrono::steady_clock::now();
	auto diff = end - start;
	cout << "use the method of copyTo.()\n";
	cout << chrono::duration <double, milli> (diff).count() <<endl;

	return 0;
}

#elif defined(CONCATE)

int main(void)
{
	Mat v_unit[32];
	Mat h_unit[14];
	Mat unit;
	Mat unit_cvt;
	Mat column;
	Mat img;
	string path = "..\\..\\..\\Resources\\screenshots\\";
	string read_path;
	int i, j;

	auto start = chrono::steady_clock::now();

	for (i = 0; i < 14; i++) {
		for (j = 0; j < 32; j++) {
			read_path = path + to_string(i * 32 + j) + ".png";
			v_unit[j] = imread(read_path);
		}
		vconcat(v_unit, 32, h_unit[i]);
	}

	hconcat(h_unit, 14, img);
	imwrite("..\\..\\..\\Resources\\roi.png", img);

	auto end = chrono::steady_clock::now();
	auto diff = end - start;
	cout << "use the method of concat.()\n";
	cout << chrono::duration <double, milli> (diff).count() << endl;

	return 0;
}

#elif defined(SETTO)
// Note: the function setTo() can only assign the scalar value to matrix but
//       set value of a matrix to that of another matrix. As a result, this 
//       function cannot be used in my project

int main(void)
{
	Mat img(Size(14 * 256, 32 * 144), CV_8UC3, Scalar(255, 0, 255));
	Mat unit;
	Mat unit_cvt;
	string path = "..\\..\\..\\Resources\\screenshots\\";
	string read_path;
	int i, j;

	auto start = chrono::steady_clock::now();

	for (i = 0; i < 14; i++) {
		for (j = 0; j < 32; j++) {
			read_path = path + to_string(i * 32 + j) + ".png";
			unit = imread(read_path);
			unit.convertTo(unit_cvt, CV_8UC3);				// this line is indispensable
			Mat(img, Rect(i * 256, j * 144, 256, 144)).setTo(Scalar(255, 255, 0));
		}
	}

	imwrite("..\\..\\..\\Resources\\roi.png", img);

	auto end = chrono::steady_clock::now();
	auto diff = end - start;
	cout << "use the method of setTo.()\n";
	cout << chrono::duration <double, milli> (diff).count() << endl;

	return 0;
}

#elif defined(SIMPLE)

int main(void)
{
	Mat img(500, 500, CV_8UC3, Scalar(255, 255, 255));
	int i, j;

	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			switch ((i + j) % 3) {
				case 0:
					Mat(img, Rect(i * 50, j * 50, 50, 50)) = Scalar(0, 255, 255);
					break;
				case 1:
					Mat(img, Rect(i * 50, j * 50, 50, 50)) = Scalar(255, 0, 255);
					break;
				case 2:
					Mat(img, Rect(i * 50, j * 50, 50, 50)) = Scalar(255, 255, 0);
					break;
			}
		}
	}

	imshow("Image", img);
	waitKey(0);

	return 0;
}

#endif
