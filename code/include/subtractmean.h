#ifndef SUBTRACTMEAN_H
#define SUBTRACTMEAN_H
#include <iostream>
#include "opencv4/opencv2/opencv.hpp"
#include "opencv4/opencv2/core/core_c.h"
#include "mnistheader.h"

using namespace cv;
using namespace std;

class SubtractMean{
	private:
		void subtractMean();
		Mat flatMatrix;

	public:
		Mat &returnResult();
		SubtractMean(vector<Image> &image);
};
#endif
