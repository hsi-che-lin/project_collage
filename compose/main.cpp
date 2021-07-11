#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

typedef unsigned char uchar;
typedef struct PIX_VAL {
	uchar G;
	uchar B;
	uchar R;
} pix_val;

// this function will load the data from the text file containing data
//  - path: the path to the text file containing data
//  - data: datastructure to store whole the data
//  - returned value: the total number of data
int load_data(string path, vector<pix_val>& data);

// this function will examine whether two pixel value is close enough
//  - a, b: two pixel value to be examined
//  - eps: threhold to define what is "close enough"
//  - returned value: 1 for close enough; 0 otherwise
int is_close(pix_val a, pix_val b, double eps);

int main(void)
{
	string target_path = "..\\..\\..\\Resources\\target.jpg";
	string datafile_path = "..\\..\\..\\Resources\\data.txt";	// path to the datafile
	string unit_ppath = "..\\..\\..\\Resources\\screenshots\\";
	string unit_cpath;
	vector<pix_val> data;			// datastructure to store whole the data
	int ndata;						// the total number o data
	int x;
	int y;
	int pos;
	int i = 0;
	int j;
	double eps = 500;
	Mat target;						// the target image
	Mat tar_res;					// resized target image
	Mat collage;
	Mat v_unit[69];
	Mat h_unit[30];
	pix_val cur_pix;

	ndata = load_data(datafile_path, data);

	target = imread(target_path);
	resize(target, tar_res, Size(30, 69), INTER_AREA);
	imwrite("..\\..\\..\\Resources\\smol.png", tar_res);

	for (x = 0; x < 30; x++) {
		for (y = 0; y < 69; y++) {
			pos = y * tar_res.step[0] + x * tar_res.step[1];
			cur_pix.B = tar_res.data[pos];
			cur_pix.G = tar_res.data[pos + 1];
			cur_pix.R = tar_res.data[pos + 2];

			j = (i + ndata - 1) % ndata;
			while (!is_close(cur_pix, data[i], eps)) {
				if (j == i)
					eps += 300;
				i = (i + 1) % ndata;
			}

			unit_cpath = unit_ppath + to_string(i) + ".png";
			v_unit[y] = imread(unit_cpath);

			i = (i + 300) % ndata;
			eps = 500;
		}

		vconcat(v_unit, 69, h_unit[x]);
	}

	hconcat(h_unit, 30, collage);
	imwrite("..\\..\\..\\Resources\\collage.png", collage);

	return 0;
}

// this function will load the data from the text file containing data
//  - path: the path to the text file containing data
//  - data: datastructure to store whole the data
//  - returned value: the total number of data
int load_data(string path, vector<pix_val>& data)
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

// this function will examine whether two pixel value is close enough
//  - a, b: two pixel value to be examined
//  - eps: threhold to define what is "close enough"
//  - returned value: 1 for close enough; 0 otherwise
int is_close(pix_val a, pix_val b, double eps)
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

	return (distance <= eps ? 1 : 0);
}
