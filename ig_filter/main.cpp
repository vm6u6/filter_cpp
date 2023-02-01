#include "filter.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void img_filter_test(){
    const char* imagename = "../test.png";
 
    Mat img = imread(imagename, 1);

    if (img.empty()) {
        fprintf(stderr, "Can not load image %s\n", imagename);
    }

    imshow("Original image", img);
    waitKey();

    general_filter filter_test;

    filter_test.ghost_filter(img);
    filter_test.dark_img(img);
    filter_test.nice_skin(img);
}

int main(int argc, char* argv[]) {
    // img_filter_test();
    VideoCapture cap(0); 
    if (!cap.isOpened()) {
        cout << "Check your webcam" << endl;
        return -1;
    }

    CascadeClassifier face_cascade;
    if (!face_cascade.load("../weight/haarcascade_frontalface_alt.xml")) {
        cout << "Please reload your face detection model" << endl;
        return -1;
    }
    Mat frame;
    Mat copy_frame;
    Mat gray_frame;
    vector<Rect> faces;
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            cout << "Check your webcam" << endl;
            break;
        }

        cvtColor(frame, gray_frame, COLOR_BGR2GRAY);
        equalizeHist(gray_frame, gray_frame);
        face_cascade.detectMultiScale(gray_frame, faces, 1.1, 3, 0, Size(30, 30));


        for (size_t i = 0; i < faces.size(); i++) {
            rectangle(frame, faces[i], Scalar(255, 0, 0), 2);
        }

        cvtColor(frame, copy_frame, COLOR_BGR2RGB);
        imshow("webcam", copy_frame);
        if (waitKey(1) == 27) { 
            break;
        }
    }

    return 0;
}


