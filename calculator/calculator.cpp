// July, 3, 2021 calculator of target combinations of width and height

#include <stdio.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

const int best_wid = 1595;		// width of my doggo and oni
const int best_hei = 2062;		// height of my oni and doggo

const int stream_wid = 256;		// width of stream screen
const int stream_hei = 144;		// height of stream screen

const double eps = 0.005;	// acceptable precision

// this function will return the absolute value of the input x
double my_abs(double x);

// this function will draw a picture indicatig how final image will be divided
// and then save the picture
// - num_wid: the number of sub-picture on the width in the final collage
// - num_hei: the number of sub-picture on the height in the final collage
void draw(int num_wid, int num_hei);

int main(void)
{
	double ratio_tar;		// target ratio
	double ratio_cur;		// current ratio
	int num_wid = 1;		// number of grids at width of final picture
	int num_hei = 1;		// number of grids at height of final picture
	int i = 0;				// number of acceptable combination found
	int chosen_comb;		// combination chosen by user
	int comb[5][2] = {};	// combinations found
							// - [i][0]: num_wid of i_th combination
							// - [i][1]: num_hei of i_th combination

	ratio_tar = (double)best_wid / best_hei;		// find the target ratio
	printf("\n""ratio_tar: %f\n\n", ratio_tar);

	while (i < 5) {									// find 5 combinations
													// calculate current ratio
		ratio_cur = ((double)stream_wid * num_wid) / (stream_hei * num_hei);

		if ((num_wid >= 15 || num_hei >= 15) &&
		    my_abs(ratio_cur - ratio_tar) < eps) {	// acceptable combination
			comb[i][0] = num_wid;					// store the combination
			comb[i][1] = num_hei;
													// print found combination
			printf("%d: (num_wid, num_hei) = (%d, %d)\n", i, num_wid, num_hei);
			printf("   ratio_cur = %f\n", ratio_cur);

			i++;
		} 

		if (ratio_cur > ratio_tar)					// change the combination
			num_hei++;
		else
			num_wid++;
	}

	printf("\n""choose a combination (0 ~ 4): ");	// prompt user to choose
	scanf("%d", &chosen_comb);						// scan and draw the blue print
	draw(comb[chosen_comb][0], comb[chosen_comb][1]);

	return 0;
}

// this function will return the absolute value of the input x
double my_abs(double x)
{
	double result;

	result = x > 0 ? x : -x;		// test the sign of x

	return result;
}

// this function will draw a picture indicatig how final image will be divided
// and then save the picture
// - num_wid: the number of sub-picture on the width in the final collage
// - num_hei: the number of sub-picture on the height in the final collage
void draw(int num_wid, int num_hei)
{
	Mat img(best_hei, best_wid, CV_8UC3, Scalar(255, 255, 255));	// blueprint
	int cur_x;						// x-coordinate of current vertical line
	int cur_y;						// y-coordinate of current horizontal line
	int i;							// counter for the number of grids

	for (i = 1; i < num_wid; i++) {	// draw vertical lines
		cur_x = (double)best_wid / (num_wid) * i;
		line(img, Point(cur_x, 0), Point(cur_x, best_hei), Scalar(0, 0, 0), 3);
	}

	for (i = 1; i < num_hei; i++) {	// draw horizontal lines
		cur_y = (double)best_hei / num_hei * i;
		line(img, Point(0, cur_y), Point(best_wid, cur_y), Scalar(0, 0, 0), 3);
	}

	imwrite("..\\..\\..\\Resources\\blueprint.png", img);

	return;
}