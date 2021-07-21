#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using std::vector;
int main()
{
    Mat src = imread("../image_raw_screenshot2_14_07_2021.png",IMREAD_GRAYSCALE);

    imshow("src",src);

    SimpleBlobDetector::Params params;
    params.filterByArea = true;
    params.minArea = 100;
    params.maxArea = 1000;
    params.filterByColor = true;
    params.blobColor = 50;
    params.filterByCircularity = 1;
    
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

    vector<KeyPoint> keypoints;
    detector->detect(src,keypoints);

    Mat img_with_keypoints;
    drawKeypoints(src,keypoints,img_with_keypoints,Scalar(255,0,0),
    DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    imshow("keypoints",img_with_keypoints);
    waitKey(0);
    
}