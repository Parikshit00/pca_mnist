#ifndef PrincipleComponentAnalysis_H
#define PrincipleComponentAnalysis_H

#include <iostream>
#include "opencv4/opencv2/opencv.hpp"
#include "opencv4/opencv2/core/core_c.h"

#include "mnistheader.h"
#include "eigenQR.h"

using namespace cv;
using namespace std;

class PrincipleComponentAnalysis{
private:
	Mat mean_subtracted;
	Mat covariance_matrix;
	Mat eigenVectors;
	vector<double> eigenValues;
	Mat principleMatrix;
	void getEigen();
	Mat performPrincipleComponentAnalysis();
	Mat returnData();

public:
	PrincipleComponentAnalysis(Mat meanSubtracted, Mat covariance);
	Mat run();

};
#endif
