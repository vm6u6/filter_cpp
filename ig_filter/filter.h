#ifndef  _FILTER_H_
#define _FILTER_H_

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class general_filter{
    
    public:
        void ghost_filter(Mat& img);
        void dark_img(Mat& img);

};

#endif  //_FILTER_H_