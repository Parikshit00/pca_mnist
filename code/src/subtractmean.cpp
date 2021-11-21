#include "subtractmean.h"

SubtractMean ::SubtractMean(vector<Image> &Data)
{
  for (int i = 0; i < 1000; i++)
  {
      Mat flat = Data[i].image.reshape(1, 1);
      flat.convertTo(flat, CV_64F);
      flatMatrix.push_back(flat.clone());
    }
}

void SubtractMean ::subtractMean()
{
    Mat height_mean;
    reduce(flatMatrix, height_mean, 0, CV_REDUCE_AVG);
    Mat flatMean;
    repeat(height_mean, 10, 1, flatMean);
    flatMatrix = flatMatrix - flatMean;
}


Mat &SubtractMean ::returnResult()
{
	subtractMean();
	cout<<"Mean Substraction done. Rows = "<<flatMatrix.rows<<", Cols = "<<flatMatrix.cols<<endl;
	return flatMatrix;
}