#include "covariance.h"

Covariance ::Covariance(Mat meanSubtracted)
{
	subtracted = meanSubtracted;
}

void Covariance ::calculateCovariance()
{
	covarianceMatrix = subtracted.t() * subtracted;
}

Mat &Covariance ::returnCovariance()
{
	calculateCovariance();
	cout<<"Covariance matrix calculated.  Rows = "<<covarianceMatrix.rows<<", Cols = "<<covarianceMatrix.cols<<endl;
	return covarianceMatrix;
}