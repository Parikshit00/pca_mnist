#include "mnistheader.h"
#include "subtractmean.h"
#include "covariance.h"
#include "pca.h"
#include "matplotlibcpp.h"

#include <cmath>
#include <iostream>
#include "opencv4/opencv2/opencv.hpp"

using namespace std;
using namespace cv;

namespace plt = matplotlibcpp;
#define totalDataPoints 500

int main()
{
    // location to dataset
    string HOME_DIR = "../../mnistdataset/";
    string train_image = HOME_DIR + "train-images-idx3-ubyte";
    string train_label = HOME_DIR + "train-labels-idx1-ubyte";
    string test_image = HOME_DIR + "t10k-images-idx3-ubyte";
    string test_label = HOME_DIR + "t10k-labels-idx1-ubyte";


    MNIST callMnist(train_image, train_label, test_image, test_label);
    callMnist.run();
    // reading test and train data
    vector<Image> train = callMnist.returnTrain();
    vector<Image> test = callMnist.returnTest();

    // Subtracting mean
    Mat meanSubtracted;
    SubtractMean callSubtraction(train);
    meanSubtracted = callSubtraction.returnResult();

    //calculating covariance matrix
    Mat covariance;
    Covariance callCovariance(meanSubtracted);
    covariance = callCovariance.returnCovariance();

    // Performing PrincipleComponentAnalysis
    Mat final;
    PrincipleComponentAnalysis callPrincipleComponentAnalysis(meanSubtracted, covariance);
    final = callPrincipleComponentAnalysis.run();

    //visualization
    std::map<std::string, std::string> keywords;
    keywords.insert(std::pair<std::string, std::string>("c", mapcolor(trainingImage[0].label)));
    std::vector<double> x = {final.at<double>(0, 0)};
    std::vector<double> y = {final.at<double>(0, 1)};
    std::vector<double> z = {final.at<double>(0, 2)};
    plt::plot3(x, y, z, 1, keywords);

    for (int i = 1; i < final.rows; i++)
    {
        x[0] = final.at<double>(i, 0);
        y[0] = final.at<double>(i, 1);
        z[0] = final.at<double>(i, 2);
        keywords.erase("c");
        keywords.insert(std::pair<std::string, std::string>("c", mapcolor(trainingImage[i].label)));
        plt::plot3(x, y, z, 1, keywords);
    }

    plt::show();
    return 0;
}

string mapcolor(string digit)
{
    string color[10] = {"r", "b", "g", "c", "m", "y", "k", "#2dccc9", "#1025e6", "#e610d4"};
    int index = stoi(digit);
    return color[index];
}

