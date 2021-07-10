#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <chrono>

// #define PRINT_RESULT
// #define TEST_SPEED

using namespace std;

typedef unsigned char uchar;
typedef struct PIX_VAL {		// datastructure to store a 3-channel pixel
	uchar B;					// intensity of blue
	uchar G;					// intensity of green
	uchar R;					// intensity of red
} pix_val;

// this fucntion will read the pixel color information from the specified file
//  - path: path to the text file that contains the pixel color information
//  - data: datastructure to store the pixel color information
//  - returned value: the number of data (pixel color information)
int read_data(string path, vector<pix_val>& data);

// this function will compute the square of distance of two color
//  - a, b: pixel color to compute the distance
//  - returned value: square of the distance
double pix_dis(pix_val a, pix_val b);

#if !defined(TEST_SPEED) && !defined(PRINT_RESULT)
int main(void)
{
	string path = "..\\..\\Resources\\data.txt";
	vector<pix_val> data;
	pix_val test_pix = {123, 111, 131};
	double distance;
	int num;
	int i;

	num = read_data(path, data);

	for (i = 0; i < num; i++) {
		distance = pix_dis(test_pix, data[i]);
	}

	return 0;
}
#endif

// this fucntion will read the pixel color information from the specified file
//  - path: path to the text file that contains the pixel color information
//  - data: datastructure to store the pixel color information
//  - returned value: the number of data (pixel color information)
int read_data(string path, vector<pix_val>& data)
{
	ifstream database;			// file stream of the database
	int b;						// intensity of blue of the input pixel
	int g;						// intensity of green of the input pixel
	int r;						// intensity of red of the input pixel
	pix_val bgr;				// current read pixel color value
	int num = 0;				// total number of data

	database.open(path);
	if (!database.is_open()) {
		cout << "fail to open the database\n";
		exit(-1);
	}

	database >> b;
	database >> g;
	database >> r;
	while (!database.eof()) {	// read until database is empty
		bgr.B = (uchar)b;
		bgr.G = (uchar)g;
		bgr.R = (uchar)r;
		data.push_back(bgr);
		num++;

		database >> b;
		database >> g;
		database >> r;
	}

	return num;
}

// this function will compute the square of distance of two color
//  - a, b: pixel color to compute the distance
//  - returned value: square of the distance
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

	distance = (2 + (redmean / 256)) * delta_r * delta_r +
                4 * delta_g * delta_g +
			   (2 + (255 - redmean) / 256) * delta_b * delta_b;

	return distance;
}

#if defined(PRINT_RESULT)
int main(void)
{
	string path = "..\\..\\Resources\\data.txt";
	vector<pix_val> data;
	pix_val test_pix = {123, 111, 131};
	double distance;
	int num;
	int i;

	num = read_data(path, data);

	for (i = 0; i < num; i++) {
		distance = pix_dis(test_pix, data[i]);
		cout << i << ": " << distance << '\n';
	}

	return 0;
}
#endif

#if defined(TEST_SPEED)
int main(void)
{
	string path = "..\\..\\Resources\\data.txt";
	vector<pix_val> data;
	pix_val test_pix = {123, 111, 131};
	double distance;
	int num;
	int i;

	num = read_data(path, data);

	auto start = chrono::steady_clock::now();

	for (i = 0; i < num; i++) {
		distance = pix_dis(test_pix, data[i]);
	}

	auto end = chrono::steady_clock::now();
	auto diff = end - start;
	cout << chrono::duration <double, milli> (diff).count() << endl;

	return 0;
}
#endif
