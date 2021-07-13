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
	string target_path = "..\\..\\..\\Resources\\target.jpg";
	string pix_data_path = "..\\..\\..\\Resources\\data.txt";	// path to the datafile
	string img_data_path = "..\\..\\..\\Resources\\screenshots\\";
	vector<pix_val> pix_data;	// datastructure to store whole the data
	vector<Mat> img_data;
	int npix_data;					// the total number o data
	int nimg_data;
	int x;
	int y;
	int pos;
	int k = 20;
	int *index;
	int best_index;
	int i;
	double best_score;
	Mat target;						// the target image
	Mat tar_smol;					// resized target image
	Mat tar_big;
	Mat roi;
	Mat cur_score;
	Mat collage;
	Mat v_unit[69];
	Mat h_unit[30];
	pix_val cur_pix;

	index = (int *)malloc(k * sizeof(int));

	cout << "loading data...\n......\n";
	npix_data = load_pix_data(pix_data_path, pix_data);
	nimg_data = load_img_data(img_data_path, img_data);
	if (npix_data != nimg_data) {
		cout << "the number of pixel data (" << npix_data << ") does not match "
			    "with the number of image data (" << nimg_data << ")\n";
		exit(-1);
	}

	target = imread(target_path);
	resize(target, tar_smol, Size(30, 69), INTER_AREA);
	resize(target, tar_big, Size(160 * 30, 90 * 69), INTER_CUBIC);
//	imwrite("..\\..\\..\\Resources\\target_big.png", tar_big);
//	imwrite("..\\..\\..\\Resources\\target_smol.png", tar_smol);

//	auto start = chrono::steady_clock::now();

	cout << "composing collage...\n......\n";
	for (x = 0; x < 30; x++) {
		for (y = 0; y < 69; y++) {
			pos = y * tar_smol.step[0] + x * tar_smol.step[1];
			cur_pix.B = tar_smol.data[pos];
			cur_pix.G = tar_smol.data[pos + 1];
			cur_pix.R = tar_smol.data[pos + 2];

			k_nn(cur_pix, pix_data, index, k);

			roi = Mat(tar_big, Rect(x * 160, y * 90, 160, 90));
			best_index = index[0];
			best_score = 1;
			for (i = 0; i < k; i++) {
				matchTemplate(roi, img_data[index[i]], cur_score, TM_SQDIFF_NORMED);
				if (cur_score.at<float>(0) < best_score) {
					best_index = index[i];
					best_score = cur_score.at<float>(0);
				}
			}

			v_unit[y] = img_data[best_index];
		}

		vconcat(v_unit, 69, h_unit[x]);
	}

//	auto end = chrono::steady_clock::now();
//	auto diff = end - start;
//	cout << chrono::duration<double, milli>(diff).count() << '\n';

	hconcat(h_unit, 30, collage);
	cout << "saving collage...\n......\n";
	imwrite("..\\..\\..\\Resources\\collage.png", collage);

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
		bgr.B = (uchar)b;
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
	string cpath;
	Mat img;
	int ndata = 0;

	cpath = path + to_string(ndata) + ".png";
	img = imread(cpath);
	while (!img.empty()) {
		data.push_back(img);
		ndata++;

		cpath = path + to_string(ndata) + ".png";
		img = imread(cpath);
	}

	return ndata;
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
	double *distances;
	int ndata;
	int i, j, m;

	ndata = pix_data.size();
	distances = (double *)malloc(ndata * sizeof(double));

	for (i = 0; i < ndata; i++) {
		distances[i] = pix_dis(pix_data[i], target);

		j = 0;
		while (j < k && j < i && distances[index[j]] <= distances[i]) j++;

		if (j != k) {
			for (m = k - 1; m > j; m--)
				index[m] = index[m - 1];
			index[j] = i;
		}
	}

	return;
}