#ifndef EIGEN_QR_H
#define EIGEN_QR_H

#include <iostream>
#include "opencv4/opencv2/opencv.hpp"

using namespace cv;
using namespace std;

class EigenQR{
public:
	void eigen_decomposition(Mat A, int max_iter = 1);
	Mat returnEigenVectors();
	vector<double> returnEigenValues();

private:
	void householder_qr(Mat A, Mat &Q, Mat &R);
	Mat compute_minor(const Mat &mat, int d);
	vector<double> extract_column(const Mat &v, int c);
	Mat EigenVectors;
	vector<double> EigenValues;
	Mat Q_orth;
	Mat R_upper;
	double norm(const vector<double> &v);
	void rescale(double factor, vector<double> &v);
	void rescale_unit(vector<double> &v);
	void vmadd(const vector<double> &a, vector<double> &e, double s);
	Mat compute_householder_factor(int row, int col, const vector<double> &v);

};
#endif