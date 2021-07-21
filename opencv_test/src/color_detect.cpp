#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

int main()
{
    Mat src = imread("../1.png",IMREAD_COLOR);

    imshow("original",src);
    Mat hsv;
    cvtColor(src,hsv,COLOR_BGR2HSV);

    imshow("HSV",hsv);
    waitKey(0);    

}