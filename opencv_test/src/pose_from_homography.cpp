#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>


int main(int argc, char *argv[])
{
    cv::Size boardSize;
    
    boardSize.width = 9;
    boardSize.height = 6;

    cv::Mat camera_matrix;
    cv::Mat distortionCoeffs;

    cv::Mat rvec;
    cv::Mat tvec;


    float cm[10] = {1,0,0,0,1,0,0,0,1};
    float dc[4] = {0,0,0,0};

    camera_matrix = camera_matrix.eye(3,3,CV_32F);
    distortionCoeffs = distortionCoeffs.zeros(1,5,CV_32F);

    camera_matrix = (cv::Mat1d(3,3) << 448.06375, 0, 276.77853, 0, 446.82352, 222.37746, 0, 0, 1);

    std::cout<<camera_matrix<<std::endl;
    distortionCoeffs = (cv::Mat1d(1,5) << 0.0587196, -0.0542081, -0.000444068, -0.00850087, 0.098648);
    std::cout<<distortionCoeffs<<std::endl;
    double squareSize = 0.022;

    cv::Mat src = cv::imread("../image/calib_01.png",cv::IMREAD_COLOR);
    
    std::vector<cv::Point3d> corners;

//    std::cout<<boardSize.width;

    for(int i = 0; i < boardSize.height; i++)
        for(int j = 0; j < boardSize.width; j++)
            corners.push_back(cv::Point3d(double(j*squareSize),
                                            double(i*squareSize),0));

    std::vector<cv::Point2f> detected_corners;
    bool found = cv::findChessboardCorners(src,boardSize,detected_corners);

    cv::drawChessboardCorners(src,boardSize,detected_corners,found);

    cv::solvePnP(corners,detected_corners,
    camera_matrix,distortionCoeffs,rvec,tvec);

    std::cout<<rvec;
    std::cout<<"\n";
    std::cout<<tvec;
    std::cout<<"\n";

    std::vector<cv::Point3f> obj_pts;
    obj_pts.push_back(cv::Point3f(0,0,0));
    obj_pts.push_back(cv::Point3f(0.022,0,0));
    obj_pts.push_back(cv::Point3f(0,0.022,0));    
    obj_pts.push_back(cv::Point3f(0,0,0.022));

    cv::projectPoints(obj_pts,rvec,tvec,
    camera_matrix,distortionCoeffs,detected_corners);

    cv::line(src,detected_corners.at(0),detected_corners.at(1),cv::Scalar(0,0,255),5,8,0);
    cv::line(src,detected_corners.at(0),detected_corners.at(2),cv::Scalar(0,255,0),5,8,0);
    cv::line(src,detected_corners.at(0),detected_corners.at(3),cv::Scalar(255,0,0),5,8,0);

    cv::imshow("image",src);

    cv::waitKey(0);

    return 0;
}
