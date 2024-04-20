# Principle Component Analysis on MNIST dataset

This is an implementation of PCA algorithm on MNIST dataset from scratch in C++.  

If you are interested in the eigen vector QR decomposition code. Refer to: `code/incude/eigenQR.h` & `code/build/eigenQR.cpp`  

# Installation 
- g++ or clang compiler
- opencv c++
- Python
- Python Numpy
- For visualization Matplotlobc++ is used: https://github.com/lava/matplotlib-cpp

# Build and Run
```
cd code
mkdir build && cd build && cmake ..
make
```
Then inside your `build` folder:
```
./pca
```
## Refrences:
+ https://en.wikipedia.org/wiki/List_of_numerical_analysis_topics#Eigenvalue_algorithms
+ http://www.oranlooney.com/post/ml-from-scratch-part-6-pca/
+ https://rosettacode.org/wiki/QR_decomposition#C.2B.2B

