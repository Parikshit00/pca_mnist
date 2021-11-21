#include "pca.h"

PrincipleComponentAnalysis ::PrincipleComponentAnalysis(Mat meanSubtracted, Mat covariance)
{
	mean_subtracted = meanSubtracted;
	covariance_matrix = covariance;
}

void PrincipleComponentAnalysis ::getEigen()
{
	EigenQR callEigen;
	callEigen.eigen_decomposition(covariance_matrix);
	eigenVectors = callEigen.returnEigenVectors();
	eigenValues = callEigen.returnEigenValues();	
}

Mat PrincipleComponentAnalysis ::run()
{
	getEigen();
	return returnData();
}


Mat PrincipleComponentAnalysis ::performPrincipleComponentAnalysis()
{

  std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> q;
  int k = 3; 
  for (int i = 0; i < eigenValues.size(); ++i)
  {
    if (q.size() < k) q.push(std::pair<double, int>(eigenValues[i], i));
    else if (q.top().first < eigenValues[i])
    {
      q.pop();
      q.push(std::pair<double, int>(eigenValues[i], i));
    }
  }
  k = q.size();
  std::vector<int> res(k);
  for (int i = 0; i < k; ++i)
  {
    res[k - i - 1] = q.top().second;
    q.pop();
  }
  Mat principleaxis = eigenVectors.col(res[0]);
  for (int i = 1; i < 3; i++)
  {
    hconcat(principleaxis, eigenVectors.col(res[i]), principleaxis);
  }
  return principleaxis;

}

Mat PrincipleComponentAnalysis ::returnData()
{
	Mat principalcomponent = performPrincipleComponentAnalysis();
  Mat final = mean_subtracted * principalcomponent;
  return final;
}

