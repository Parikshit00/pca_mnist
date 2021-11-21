#include "eigenQR.h"


Mat EigenQR ::compute_minor(const Mat &mat, int d)
{
  Mat temp = Mat::zeros(mat.rows, mat.cols, CV_64F);
  for (int i = 0; i < d; i++) temp.at<double>(i, i) = 1.0;
  for (int i = d; i < mat.rows; i++)
  {
    for (int j = d; j < mat.cols; j++) temp.at<double>(i, j) = mat.at<double>(i, j);        
  }
  return temp;    
}


Mat EigenQR ::returnEigenVectors()
{
	return EigenVectors;
}

vector<double> EigenQR ::returnEigenValues()
{
	return EigenValues;
}

void EigenQR ::eigen_decomposition(Mat A, int max_iter)
{
	Mat A_k = A.clone();
	Mat Q_k = Mat::eye(A.rows, A.cols, CV_64F);
	for(int i =0; i < max_iter; i++)
	{	
		Mat Q, R;
		// Calling algorithm for QR decomposition
		householder_qr(A_k, Q, R);
		Q_k  = Q_k * Q;
		A_k = R * Q;

	}
	// copying eigen vectors	
	EigenVectors = Q_k;
	// Implement np.diag
	for(int i = 0; i < A_k.rows; i++)
	{
		for(int j = 0; j < A_k.cols; j++)
		{
			//copying eigen values
			if(i == j) EigenValues.push_back(A_k.at<double>(i, j));
		}
	}

}


void EigenQR ::householder_qr(Mat A, Mat &Q, Mat &R)
{
	int m = A.rows;
	int n = A.cols;

	//array of factors Q1,Q2,..... Qm
	vector<Mat> qv;
	//temp matrix
	Mat z = A.clone();
	Mat z1 = Mat::zeros(m, n, CV_64F);
	for(int k = 0; k < n-1; k++)
	{
		vector<double> e, x;
    double a;

    //compute minor
    z1 = compute_minor(z, k);

    //extract kth column into x
    x = extract_column(z1, k);

    a = norm(x);
    if (A.at<double>(k, k) > 0) a = -a;
    for (int i = 0; i < x.size(); i++)
    {
      double num = (i == k) ? 1 : 0;
      e.push_back(num);
    }
    // e = x + a*e
    vmadd(x, e, a);

    // e = e / ||e||
    rescale_unit(e);
    
    // qv[k] = I - 2 *e*e^T
    Mat q = compute_householder_factor(m, n, e);
    qv.push_back(q.clone());

    // z = qv[k] * z1
    z = q * z1;
  }

  Q = qv[0];

  // after this loop, we will obtain Q (up to a transpose operation)
  for (int i = 1; i < n - 1; i++)
  {
    z1 = qv[i] * Q;
    Q = z1.clone();
  }

  R = Q * A;
  Q = Q.t();

	
}

vector<double> EigenQR ::extract_column(const Mat &v, int c)
{
  Mat column = v.col(c);
  vector<double> columns;
  for (int i = 0; i < column.rows; i++) columns.push_back(column.at<double>(i, 0));
  return columns;
}

  //   ||x||
double EigenQR ::norm(const vector<double> &v)
{
  double sum = 0;
  for (int i = 0; i < v.size(); i++) sum += v[i] * v[i];
  return sqrt(sum);

}

void EigenQR ::vmadd(const vector<double> &a, vector<double> &e, double s)
{
  for (int i = 0; i < e.size(); i++) e[i] = a[i] + s * e[i];
}


void EigenQR ::rescale(double factor, vector<double> &v)
{
	for (int i = 0; i < v.size(); i++) v[i] = v[i] / factor;
}


void EigenQR ::rescale_unit(vector<double> &v)
{
	double factor = norm(v);
  if (factor != 0) rescale(factor, v);
}


Mat EigenQR ::compute_householder_factor(int row, int col, const vector<double> &v)
{
  int n = v.size();
  Mat temp = Mat::zeros(row, col, CV_64F);

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++) temp.at<double>(i, j) = -2 * v[i] * v[j];
        
  }
  for (int i = 0; i < n; i++) temp.at<double>(i, i) = temp.at<double>(i, i) + 1;
  return temp;
}



