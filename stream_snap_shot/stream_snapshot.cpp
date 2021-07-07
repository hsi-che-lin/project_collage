// July, 4, 2021 save a screenshot every 10 seconds for a given video

// Note:
//   using .grab then .retrieve when necessary is much faster (more than x4) 
//   then using .read everytime

#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main(void)
{
	string path = "..\\..\\..\\Resources\\0.mp4";				// path of video
	string save_path = "..\\..\\..\\Resources\\screenshots\\";	// partial path to save
	string cur_save_path;										// complete path to save
	VideoCapture cap(path);										// handle the video
	Mat img;													// current screenshot
	Mat img_resize;												// resized screenshot
	int num = 0;												// number of screenshots
	int i = 0;													// counter of input frames

	while (cap.grab()) {										// grabe every frame
		if (i++ == 900) {										// for every 900 frames
			cap.retrieve(img);									// retrieve the image
			resize(img, img_resize, Size(256, 144));			// resize the screenshot
																// generate save path
			cur_save_path = save_path + to_string(num) + ".png";
			imwrite(cur_save_path, img_resize);

			i = 0;												// reset counter
			num++;
		}
	}

	return 0;
}

