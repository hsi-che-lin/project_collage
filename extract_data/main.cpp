// July, 5th, 2021
// this program combines stream_snap_shot, condence, and pixel_value
// read the video, save the screenshots, write the pixel_value represents it into a file

#include <stdio.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

// #define TEST

using namespace std;
using namespace cv;

// this function return a 1-pixel image which represent the input img
Mat condence(Mat img, int factor);

#ifndef TEST

int main(void)
{
	string stream_path = "..\\..\\..\\Resources\\1.mp4";		// path to video
	string save_path = "..\\..\\..\\Resources\\screenshots\\";	// partial path to save screenshots
	string cur_save_path;										// complete path to save screenshots
	VideoCapture cap(stream_path);
	FILE *file_w;								// point to .txt file to save data
	Mat img;									// a frame of the video
	Mat img_resize;								// img resied to 144 x 256
	Mat img_condence;							// condenced img
	int num = 0;								// number of frames to save
	int i = 0;									// frame counter

	file_w = fopen("..\\..\\..\\Resources\\data.txt", "w");

	while (cap.grab()) {						// grab a fram
		if (i++ == 750) {						// for evvery 750 frames
			cap.retrieve(img);					// retrieve adn resize
			resize(img, img_resize, Size(256, 144), INTER_AREA);
			cur_save_path = save_path + to_string(num) + ".png";
			imwrite(cur_save_path, img_resize);	// save the frame

			img_condence = condence(img, 2);	// condence frame and save data
			fprintf(file_w, "%d ", img_condence.data[0]);
			fprintf(file_w, "%d ", img_condence.data[1]);
			fprintf(file_w, "%d\n", img_condence.data[2]);

			i = 0;								// reset counter
			num++;
		}
	}

	fclose(file_w);

	return 0;
}

#endif

// this function return a 1-pixel image which represent the input img
//  - img: the image to condence
//  - factor: factor to shrink the image
Mat condence(Mat img, int factor)
{
	Mat img_con;				// the image keeping shrinking to be the result
	int width;					// current width of img_condence
	int height;					// current height of img_condence

	img_con = img;				// initialization
	width = img.size().width;	
	height = img.size().height;

	while (width != 1 || height != 1) {				// shrink until become 1x1
		if (width / factor != 0) width /= factor;	// compute next width
		else width = 1;
		if (height / factor != 0) height /= factor;	// compute next height
		else height = 1;
													// shrinking
		resize(img_con, img_con, Size(width, height), 0, 0, INTER_AREA);
	}

	return img_con;
}


#ifdef TEST			// test by using a single picture

int main(void)
{
	FILE *file_w;
	string path = "..\\Resources\\test\\test.jpg";
	Mat test_img;
	Mat test_condence_img;

	file_w = fopen("..\\Resources\\test\\test_data.txt", "w");

	test_img = imread(path);
	test_condence_img = condence(test_img, 2);

	imwrite("..\\Resources\\test\\test_condence.jpg", test_condence_img);

	fprintf(file_w, "%d ", test_condence_img.data[0]);
	fprintf(file_w, "%d ", test_condence_img.data[1]);
	fprintf(file_w, "%d\n", test_condence_img.data[2]);

	fclose(file_w);

	return 0;
}

#endif