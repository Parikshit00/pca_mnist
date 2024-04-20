#ifndef COVARIANCE_H
#define COVARIANCE_H
#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core_c.h"

using namespace std;
using namespace cv;

class Covariance{
private:
	Mat subtracted;
	Mat covarianceMatrix;
	void calculateCovariance();
	
public:
	Covariance(Mat meanSubtracted);
	Mat &returnCovariance();

};
#endif