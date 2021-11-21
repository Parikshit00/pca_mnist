#include "mnistheader.h"

MNIST ::MNIST(string train_image, string train_label, string test_image, string test_label)
{
    trainImg = train_image;
    trainLabel = train_label;
    testImg = test_image;
    testLabel = test_label;
}

// Method to read data based on endian
uint32_t MNIST ::reverse_int(uint32_t i)
{
    unsigned char c1, c2, c3, c4;
    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;

}

// MNIST dataset reader
void MNIST ::mnist_reader(const char *image_filename, const char *label_filename, vector<Image> &container)
{
    std::ifstream image_file(image_filename, std::ios::in | std::ios::binary);
    std::ifstream label_file(label_filename, std::ios::in | std::ios::binary);
    uint32_t magic, num_items, num_labels, rows, cols;
    image_file.read(reinterpret_cast<char *>(&magic), 4);
    magic = reverse_int(magic);
    label_file.read(reinterpret_cast<char *>(&magic), 4);
    magic = reverse_int(magic);
    image_file.read(reinterpret_cast<char *>(&num_items), 4);
    num_items = reverse_int(num_items);
    label_file.read(reinterpret_cast<char *>(&num_labels), 4);
    num_labels = reverse_int(num_labels);
    image_file.read(reinterpret_cast<char *>(&rows), 4);
    rows = reverse_int(rows);
    image_file.read(reinterpret_cast<char *>(&cols), 4);
    cols = reverse_int(cols);
    n_cols = cols;
    n_rows = rows;
    char label;
    char *pixels = new char[rows * cols];
    struct Image tempImage;
    for (int item_id = 0; item_id < num_items; ++item_id)
    {
        image_file.read(pixels, rows * cols);
        label_file.read(&label, 1);
        string sLabel = std::to_string(int(label));
        cv::Mat image_tmp(rows, cols, CV_8UC1, pixels);
        tempImage.label = sLabel;
        tempImage.image = image_tmp.clone();
        container.push_back(tempImage);
    }

    delete[] pixels;
    image_file.close();
    label_file.close();
}

//Driver function
void MNIST ::run()
{
    mnist_reader(trainImg.c_str(), trainLabel.c_str(), train_set); 
    mnist_reader(testImg.c_str(), testLabel.c_str(), test_set);

 
}

//Returns test set
vector<Image> &MNIST::returnTest()
{
    cout<<test_set.size()<<" test data imported."<<endl;
    cout<<"Image heightxwidth = "<<test_set[0].image.rows<<"x"<<test_set[0].image.cols<<endl;
    return test_set;
}

//Returns train set
vector<Image> &MNIST ::returnTrain()
{
    cout<<train_set.size()<<" train data imported."<<endl;
    cout<<"Image heightxwidth = "<<train_set[0].image.rows<<"x"<<train_set[0].image.cols<<endl;
    return train_set;
}


