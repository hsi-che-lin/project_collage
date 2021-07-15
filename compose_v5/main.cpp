#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

// #include <chrono>

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

// this function will load the imgages fromm the given folder and convert it
// into CIE format
//  - path: the path to the folder containing images
//  - data: datastructure to store all the image
//  - returned value: the total number of data
int load_img_data(string path, vector<Mat>& data);

// this function return a 1-pixel image which represents the input img
//  - img: the image to condense
//  - factor: factor to shrink the image
Mat condense(Mat img, int factor);

// this function will compute the distance between two pixel color value
//  - a, b: two pixel color value to compute the distance
//  - returned value: distance between a, b
double pix_dis(pix_val a, pix_val b);

// this function will find k nearest neighbor of given pixel color value using
// distance between two pixel values produced by condense method as metrics
//  - target: the target pixel color value to find its nearest neighbor
//  - pix_data: the dataset where to search nearest neighbor
//  - k: the number of the nearest neighbor to find (length of nn_idx)
//  - nn_idx: array of the indices of the nearest neighbor in pix_data
void cond_k_nn(pix_val target, vector<pix_val>& pix_data, int k, int *nn_idx);

// this function will find k nearest neighbor of give image using the function
// compareHist() with HISTCMP_INTERSEcT as metrics
//  - target: the target image to find its nearest neighbor
//  - img_data: the dataset where to search nearest neighbor
//  - in_idx: array of indices to specify the range in img_data to be search
//  - in_num: the number of images in img_data to be search (length of in_idx)
//  - k: the number of the nearest neighbor to find (length of nn_idx)
//  - nn_idx: array of the indices of the nearest neighbor in img_data
void hist_k_nn(Mat& target, vector<Mat>& img_data, int *in_idx, int in_num, int k, int *nn_idx);

// this function will find best-matched image using the function matchTemplate()
//  - target: the target image to find the best-match
//  - img_data: the dataset where to search nearest neighbor
//  - in_idx: array of indices to specify the range in img_data to be matched
//  - in_num: the number of images in img_data to be matched (length of in_idx)
//  - returned value: the index of the best-matched image in img_data
int best_match(Mat& target, vector<Mat>& img_data, int *in_idx, int in_num);

int main(void)
{
	string target_path = "..\\..\\..\\Resources\\target.jpg";		// path to the target image
	string pix_data_path = "..\\..\\..\\Resources\\data.txt";		// path to the pixel data
	string img_data_path = "..\\..\\..\\Resources\\screenshots\\";	// path to the image data
	string best_unit_path;		// path to the best-matched unit
	string collage_name;		// the name of the result image file
	vector<pix_val> pix_data;	// datastructure to store all the pixel data
	vector<Mat> img_data;		// datastructure to store all the image data
	int npix_data;				// the total number of pixel data
	int nimg_data;				// the total number of image data
	int x;						// x-coordinate of grids to fill in units
	int y;						// y-coordinate of grids to fill in units
	int cond_k = 100;			// k for cond_k_nn()
	int *cond_idx;				// nn_idx for cond_k_nn()
	int hist_k = 20;			// k for hist_k_nn()
	int *hist_idx;				// nn_idx for hist_k_nn()
	int best_idx;				// img_data index of best nearest neighbor to put in collage
	Mat target;					// the target image
	Mat tar_big;				// enlarged target to produce roi to do template match
	Mat roi;					// to match the templates
	Mat roi_cond;				// condensed roi
	Mat roi_lab;				// roi in CIELAB format
	Mat collage;				// result image
	Mat v_unit[69];				// picture collection of a column
	Mat h_unit[30];				// collection of multiple columns
	pix_val cur_pix;			// pixel color value of condensed roi

	cond_idx = (int *)malloc(cond_k * sizeof(int));
	hist_idx = (int *)malloc(hist_k * sizeof(int));

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

	auto start = chrono::steady_clock::now();

	cout << "composing collage...\n......\n";
	for (x = 0; x < 30; x++) {									// for each position
		for (y = 0; y < 69; y++) {
			roi = Mat(tar_big, Rect(x * 160, y * 90, 160, 90));	// read the corresponding crop
			roi_cond = condense(roi, 2);						// condense target
			cur_pix.B = roi_cond.data[0];						// store in a pix_val type variable
			cur_pix.G = roi_cond.data[1];
			cur_pix.R = roi_cond.data[2];
			cond_k_nn(cur_pix, pix_data, cond_k, cond_idx);

			cvtColor(roi, roi_lab, COLOR_BGR2Lab);
			hist_k_nn(roi_lab, img_data, cond_idx, cond_k, hist_k, hist_idx);
			best_idx = best_match(roi_lab, img_data, hist_idx, hist_k);

			best_unit_path = img_data_path + to_string(best_idx) + ".png";
			v_unit[y] = imread(best_unit_path);
		}

		vconcat(v_unit, 69, h_unit[x]);							// compose a column
	}

	auto end = chrono::steady_clock::now();
	auto diff = end - start;
	cout << chrono::duration<double>(diff).count() << '\n';

	hconcat(h_unit, 30, collage);								// concatenate composed columns
	cout << "saving collage...\n......\n";
	collage_name = "..\\..\\..\\Resources\\30_69_v5_k" + to_string(cond_k) + 
				   "_k" + to_string(hist_k) + ".png";
	imwrite(collage_name, collage);		// save collage

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
	Mat img_lab;			// img in CIELAB form
	int ndata = 0;			// the total number of data (the returned value)

	cpath = path + to_string(ndata) + ".png";	// produce first complete path
	img = imread(cpath);						// try to read a image
	while (!img.empty()) {						// loop as image is available
		cvtColor(img, img_lab, COLOR_BGR2Lab);
		data.push_back(img_lab);				// store in dataset
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

// this function will find k nearest neighbor of given pixel color value using
// distance between two pixel values produced by condense method as metrics
//  - target: the target pixel color value to find its nearest neighbor
//  - pix_data: the dataset where to search nearest neighbor
//  - k: the number of the nearest neighbor (should be the length of nn_idx)
//  - nn_idx: array of the indices of the nearest neighbor in pix_data
void cond_k_nn(pix_val target, vector<pix_val>& pix_data, int k, int *nn_idx)
{
	double *distances;			// distances from target to pixels in pix_data
	int ndata;					// total number of data in pix_data
	int i, j, m;				// loop counter

	ndata = pix_data.size();
	distances = (double *)malloc(ndata * sizeof(double));

	for (i = 0; i < ndata; i++) {	// for each pixel in pix_data
		distances[i] = pix_dis(pix_data[i], target);

		j = 0;						// test whether is k-nearest neighbor
		while (j < k && j < i && distances[nn_idx[j]] <= distances[i]) j++;

		if (j != k) {				// this pixel is k-nearest neighbor for now
			for (m = k - 1; m > j; m--)
				nn_idx[m] = nn_idx[m - 1];
			nn_idx[j] = i;
		}
	}

	return;
}

// this function will find k nearest neighbor of give image using the function
// compareHist with HISTCMP_INTERSEcT as metrics
//  - target: the target image to match
//  - img_data: the dataset where to search nearest neighbor
//  - in_idx: array of indices to specify the range in img_data to be search
//  - in_num: the number of images in img_data to be search (length of in_idx)
//  - k: the number of the nearest neighbor (should be the length of nn_idx)
//  - nn_idx: array of the indices of the nearest neighbor in img_data
void hist_k_nn(Mat& target, vector<Mat>& img_data, int *in_idx, int in_num, int k, int *nn_idx)
{
	double *scores;	// scores of compareHist() for image with indicex in in_idx
	int *tmp;		// nearest neighnors represented by indices of in_dix
	int i, j, m;	// loop counter
	Mat hist_tar;	// histogram of target
	Mat hist_unit;	// histogram of current image in img_data
	int channels[3] = {0, 1, 2};	// below are set-up arguments of calcHist()
	int b_bins = 64;
	int g_bins = 64;
	int r_bins = 64;
	int hist_sizes[3] = {b_bins, g_bins, r_bins};
	float b_range[2] = {0, 255};
	float g_range[2] = {0, 255};
	float r_range[2] = {0, 255};
	const float *hist_ranges[3] = {b_range, g_range, r_range};

	scores = (double *)malloc(in_num * sizeof(double));
	tmp = (int *)malloc(k * sizeof(int));

	calcHist(&target, 1, channels, noArray(), hist_tar, 3, hist_sizes, hist_ranges);

	for (i = 0; i < in_num; i++) {	// for each image with index in in_index
		calcHist(&img_data[in_idx[i]], 1, channels, noArray(), hist_unit, 3, hist_sizes, hist_ranges);
		scores[i] = compareHist(hist_tar, hist_unit, HISTCMP_INTERSECT);

		j = 0;						// test whether is k-nearest neighbor
		while (j < k && j < i && scores[tmp[j]] >= scores[i]) j++;

		if (j != k) {				// this image is k-nearest neighbor for now
			for (m = k - 1; m > j; m--)
				tmp[m] = tmp[m - 1];
			tmp[j] = i;
		}
	}

	for (i = 0; i < k; i++)			// find indices of nearest neighbor in img_data
		nn_idx[i] = in_idx[tmp[i]];

	return;
}

// this function will find best-matched image using the function matchTemplate()
//  - target: the target image to find the best-match
//  - img_data: the dataset where to search nearest neighbor
//  - in_idx: array of indices to specify the range in img_data to be matched
//  - in_num: the number of images in img_data to be matched (length of in_idx)
//  - returned value: the index of the best-matched image in img_data
int best_match(Mat& target, vector<Mat>& img_data, int *in_idx, int in_num)
{
	Mat cur_score;		// current score of templatematching
	double best_score;	// best score of templatematching
	int best_idx;		// the index of the best-matched imgage
	int i;				// loop counter

	best_idx = in_idx[0];
	best_score = 1;

	for (i = 0; i < in_num; i++) {		// for each image with index in in_idx
		matchTemplate(target, img_data[in_idx[i]], cur_score, TM_SQDIFF_NORMED);
										// current image is better-matched
		if (cur_score.at<float>(0) < best_score) {
			best_score = cur_score.at<float>(0);
			best_idx = in_idx[i];
		}
	}

	return best_idx;
}