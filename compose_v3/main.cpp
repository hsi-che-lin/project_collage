#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <chrono>

using namespace std;
using namespace cv;

typedef unsigned char uchar;
typedef struct PIX_VAL {
	uchar G;
	uchar B;
	uchar R;
} pix_val;

// this function will load the data from the given text file
//  - path: the path to the text file containing data
//  - data: datastructure to store whole the data
//  - returned value: the total number of data
int load_pix_data(string path, vector<pix_val>& data);

// this function will load the imgages fromm the given folder
//  - path: the path to the folder containing images
//  - data: datastructure to store all the image
//  - returned value: the total number of data
int load_img_data(string path, vector<Mat>& data);

// this function return a 1-pixel image which represent the input img
//  - img: the image to condense
//  - factor: factor to shrink the image
Mat condense(Mat img, int factor);

// this function will compute the distance between two pixel color value
//  - a, b: two pixel color value to compute the distance
//  - returned value:
double pix_dis(pix_val a, pix_val b);

// this function will find k nearest neighbor of the given pixel color value
//  - target: the target pixel color value to find its nearest neighbor
//  - pix_val_data: the dataset where to search nearest neighbor
//  - index: array of the indices of the nearest neighbor in pix_val_data
//  - k: the number of the nearest neighbor (should be the length of index)
void k_nn(pix_val target, vector<pix_val>& pix_val_data, int *index, int k);

int main(void)
{
	string target_path = "..\\..\\..\\Resources\\target.jpg";		// path to the target image
	string pix_data_path = "..\\..\\..\\Resources\\data.txt";		// path to the pixel data
	string img_data_path = "..\\..\\..\\Resources\\screenshots\\";	// path to the image data
	vector<pix_val> pix_data;	// datastructure to store all the pixel data
	vector<Mat> img_data;		// datastructure to store all the image data
	int npix_data;				// the total number of pixel data
	int nimg_data;				// the total number of image data
	int x;						// x-coordinate of grids to fill in units
	int y;						// y-coordinate of grids to fill in units
	int pos;					// memory location of tar_smol corresponding to x, y
	int k = 20;					// the number of nearest neighbor to find
	int *index;					// indices of nearest neighbors
	int best_index;				// img_data index of best nearest neighbor to put in collage
	int i;						// loop counter
	double best_score;			// best score of templatematching
	Mat target;					// the target image
	Mat tar_cond;				// condensed target
	Mat tar_big;				// enlarged target to produce roi to do template match
	Mat roi;					// to match the templates
	Mat cur_score;				// current score of templatematching
	Mat collage;				// result image
	Mat v_unit[69];				// picture collection of a column
	Mat h_unit[30];				// collection of multiple columns
	pix_val cur_pix;			// pixel color value of pixel at pos

	index = (int *)malloc(k * sizeof(int));						// allocate memory to store indices

	cout << "loading data...\n......\n";						// load data
	npix_data = load_pix_data(pix_data_path, pix_data);
	nimg_data = load_img_data(img_data_path, img_data);
	if (npix_data != nimg_data) {								// check if two dataset match
		cout << "the number of pixel data (" << npix_data << ") does not match "
			    "with the number of image data (" << nimg_data << ")\n";
		exit(-1);
	}

	target = imread(target_path);								// load target
	resize(target, tar_big, Size(160 * 30, 90 * 69), INTER_CUBIC);
//	imwrite("..\\..\\..\\Resources\\target_big.png", tar_big);

//	auto start = chrono::steady_clock::now();

	cout << "composing collage...\n......\n";
	for (x = 0; x < 30; x++) {									// for each position
		for (y = 0; y < 69; y++) {
			roi = Mat(tar_big, Rect(x * 160, y * 90, 160, 90));	// read the corresponding crop
			tar_cond = condense(roi, 2);						// condense target
			cur_pix.B = tar_cond.data[0];						// store in a pix_val type variable
			cur_pix.G = tar_cond.data[1];
			cur_pix.R = tar_cond.data[2];

			k_nn(cur_pix, pix_data, index, k);					// find k-nearest neighbor of pixel

			best_index = index[0];
			best_score = 1;
			for (i = 0; i < k; i++) {							// template matching to find best
				matchTemplate(roi, img_data[index[i]], cur_score, TM_SQDIFF_NORMED);
				if (cur_score.at<float>(0) < best_score) {		// current one is score is better
					best_index = index[i];
					best_score = cur_score.at<float>(0);
				}
			}

			v_unit[y] = img_data[best_index];					// put in current column
		}

		vconcat(v_unit, 69, h_unit[x]);							// compose a column
	}

//	auto end = chrono::steady_clock::now();
//	auto diff = end - start;
//	cout << chrono::duration<double, milli>(diff).count() << '\n';

	hconcat(h_unit, 30, collage);								// concatenate composed columns
	cout << "saving collage...\n......\n";
	imwrite("..\\..\\..\\Resources\\collage.png", collage);		// save collage

	return 0;
}

// this function will load the data from the given text file
//  - path: the path to the text file containing data
//  - data: datastructure to store whole the data
//  - returned value: the total number of data
int load_pix_data(string path, vector<pix_val>& data)
{
	ifstream datafile;			// file stream of the datafile
	int b;						// intensity of blue of the input pixel
	int g;						// intensity of green of the input pixel
	int r;						// intensity of red of the input pixel
	pix_val bgr;				// current read pixel color value
	int ndata = 0;				// total number of data

	datafile.open(path);
	if (!datafile.is_open()) {
		cout << "fail to open the datafile\n";
		exit(-1);
	}

	datafile >> b;
	datafile >> g;
	datafile >> r;
	while (!datafile.eof()) {	// read until datafile is empty
		bgr.B = (uchar)b;		// store in a pix_val type variable
		bgr.G = (uchar)g;
		bgr.R = (uchar)r;
		data.push_back(bgr);
		ndata++;

		datafile >> b;
		datafile >> g;
		datafile >> r;
	}

	return ndata;
}

// this function will load the imgages fromm the given folder
//  - path: the path to the folder containing images
//  - data: datastructure to store all the image
//  - returned value: the total number of data
int load_img_data(string path, vector<Mat>& data)
{
	string cpath;			// complete path to each image
	Mat img;				// temporarily stored current input image
	int ndata = 0;			// the total number of data (the returned value)

	cpath = path + to_string(ndata) + ".png";	// produce first complete path
	img = imread(cpath);						// try to read a image
	while (!img.empty()) {						// loop as image is available
		data.push_back(img);					// store in dataset
		ndata++;
												// try to read next image
		cpath = path + to_string(ndata) + ".png";
		img = imread(cpath);
	}

	return ndata;
}

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

// this function will compute the distance between two pixel color value
//  - a, b: two pixel color value to compute the distance
//  - returned value:
double pix_dis(pix_val a, pix_val b)
{
	double distance;		// square of the distance
	double redmean;			// mean value of intensity of red of two pixel
	double delta_b;			// difference of intensity of blue of two pixel
	double delta_g;			// difference of intensity of green of two pixel
	double delta_r;			// difference of intensity of red of two pixel

	redmean = (a.R + b.R) / 2.0;
	delta_b = a.B - b.B;
	delta_g = a.G - b.G;
	delta_r = a.R - b.R;
							// compute distance
	distance = (2 + (redmean / 256)) * delta_r * delta_r +
                4 * delta_g * delta_g +
			   (2 + (255 - redmean) / 256) * delta_b * delta_b;

	return distance;
}

// this function will find k nearest neighbor of the given pixel color value
//  - target: the target pixel color value to find its nearest neighbor
//  - pix_val_data: the dataset where to search nearest neighbor
//  - index: array of the indices of the nearest neighbor in pix_val_data
//  - k: the number of the nearest neighbor (should be the length of index)
void k_nn(pix_val target, vector<pix_val>& pix_data, int *index, int k)
{
	double *distances;			// distances from target to pixels in pix_data
	int ndata;					// total number of data in pix_data
	int i, j, m;				// loop counter

	ndata = pix_data.size();
	distances = (double *)malloc(ndata * sizeof(double));

	for (i = 0; i < ndata; i++) {	// for each pixel in pix_data
		distances[i] = pix_dis(pix_data[i], target);

		j = 0;						// test whether is k-nearest neighbor
		while (j < k && j < i && distances[index[j]] <= distances[i]) j++;

		if (j != k) {				// this pixel is now a k-nearest neighbor
			for (m = k - 1; m > j; m--)
				index[m] = index[m - 1];
			index[j] = i;
		}
	}

	return;
}