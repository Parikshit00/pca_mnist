#ifndef MNIST_HEADER_H
#define MNIST_HEADER_H
#include <iostream>
#include "opencv4/opencv2/opencv.hpp"

using namespace std;
using namespace cv;

struct Image
{
    Mat image;
    string label;
};

class MNIST
{
public:
    MNIST(string train_image,string train_label,string test_image,string test_label );
    void run();
    vector<Image> &returnTest();
    vector<Image> &returnTrain();
private:
    vector<Image> train_set;
    vector<Image> test_set;
    string trainImg,trainLabel,testImg,testLabel;
    int n_rows,n_cols;
    uint32_t reverse_int(uint32_t val);
    void mnist_reader(const char* image_filename, const char* label_filename,vector<Image> &dataset);
};
#endif
