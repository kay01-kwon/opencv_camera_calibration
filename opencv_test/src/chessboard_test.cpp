#include <iostream>
#include <opencv2/opencv.hpp>

using std::vector;

struct CameraParameter
{
    cv::Mat cameraMatrix;
    cv::Mat distCoeffs;
};

class CameraPose{

    public:

    CameraPose();

    bool poseEstimationImage();

    void drawAxis(cv::Mat &img, cv::Mat &dst, 
                vector<cv::Point2d> &imgPts,
                vector<cv::Point2f> &cornersSP_);


    ~CameraPose();

    private:

    cv::Mat cameraMatrix_ = cv::Mat_<float> (3,3);
    vector<double> distCoeffs_;
    cv::Size_<int> patternSize_;
  
    double chessboardEdge;
};

CameraPose::CameraPose()
{
    chessboardEdge = 0.022;
    patternSize_ = cvSize(10,7);
}

bool CameraPose::poseEstimationImage()
{

}

void CameraPose::drawAxis(cv::Mat &img, cv::Mat &dst, 
                vector<cv::Point2d> &imgPts,
                vector<cv::Point2f> &cornersSP_)
{

}

CameraPose::~CameraPose(){}