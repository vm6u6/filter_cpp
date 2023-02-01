#include "filter.h"
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
    const char* imagename = "../test.png";
 
    Mat img = imread(imagename, 1);

    if (img.empty()) {
        fprintf(stderr, "Can not load image %s\n", imagename);
        return -1;
    }

    imshow("image", img);
    waitKey();

    general_filter filter_test;
    filter_test.ghost_filter(img);
    filter_test.dark_img(img);

    return 0;
}


