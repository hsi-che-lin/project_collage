// July, 5th, 2021
// this program combines stream_snap_shot, condense, and pixel_value
// read the video, save the screenshots, write the pixel_value represents it into a file

#include <stdio.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

// #define TEST			// trigger the test mode

using namespace std;
using namespace cv;

const double FRAME_DELTA = 0.5 * 60 * 30;						// interval of time to screenshot

// this function return a 1-pixel image which represent the input img
//  - img: the image to condense
//  - factor: factor to shrink the image
Mat condense(Mat img, int factor);

#ifndef TEST			// if not in the test mode

int main(void)
{
	string read_path = "..\\..\\..\\Resources\\streams\\";		// partial path to read video
	string save_path = "..\\..\\..\\Resources\\screenshots\\";	// partial path to save screenshots
	string cur_read_path;				// complete path to read video
	string cur_save_path;				// complete path to save screenshots
	VideoCapture cap;
	FILE *file_w;						// point to .txt file to save data
	Mat img;							// a frame of the video
	Mat img_resize;						// img resied to 144 x 256
	Mat img_condense;					// condensed img
	int vid_num = 0;					// number of video to read
	int saved_num = 0;					// number of frames saved
	double cur_frame = 7200;			// current position in video (in frames) 
	double total_frame;					// total number of frames in this video
	double cur_pro;						// current progress (in percentages)

	file_w = fopen("..\\..\\..\\Resources\\data.txt", "w");

	cur_read_path = read_path + to_string(vid_num++) + ".mp4";	// read first video
	while (cap.open(cur_read_path)) {							// successfully readd an video
		total_frame = cap.get(CAP_PROP_FRAME_COUNT);			// reset parameters
		cur_frame = 7200;
		cur_pro = 0;

		while (cap.set(CAP_PROP_POS_FRAMES, cur_frame) && cap.read(img) &&
			   cur_pro <= 0.80) {		// successfully read an image
			resize(img, img_resize, Size(160, 90), INTER_AREA);
			cur_save_path = save_path + to_string(saved_num) + ".png";
			imwrite(cur_save_path, img_resize);					// save the frame

			img_condense = condense(img, 2);					// condense frame and save data
			fprintf(file_w, "%d ", img_condense.data[0]);
			fprintf(file_w, "%d ", img_condense.data[1]);
			fprintf(file_w, "%d\n", img_condense.data[2]);

			cur_frame += FRAME_DELTA;							// update parameters
			saved_num++;
			cur_pro = cur_frame / total_frame;
		}
																// read next video
		cur_read_path = read_path + to_string(vid_num++) + ".mp4";
	}

	fclose(file_w);

	return 0;
}

#endif

// this function return a 1-pixel image which represent the input img
//  - img: the image to condense
//  - factor: factor to shrink the image
Mat condense(Mat img, int factor)
{
	Mat img_con;				// the image keeping shrinking to be the result
	int width;					// current width of img_condense
	int height;					// current height of img_condense

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
	Mat test_condense_img;

	file_w = fopen("..\\Resources\\test\\test_data.txt", "w");

	test_img = imread(path);
	test_condense_img = condense(test_img, 2);

	imwrite("..\\Resources\\test\\test_condense.jpg", test_condense_img);

	fprintf(file_w, "%d ", test_condense_img.data[0]);
	fprintf(file_w, "%d ", test_condense_img.data[1]);
	fprintf(file_w, "%d\n", test_condense_img.data[2]);

	fclose(file_w);

	return 0;
}

#endif