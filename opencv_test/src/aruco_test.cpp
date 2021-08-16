#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/aruco.hpp>

int main(){

    cv::Mat camera_matrix;
    cv::Mat distortionCoeffs;

    cv::Mat rvec;
    cv::Mat tvec;

    camera_matrix = (cv::Mat1d(3,3) << 448.06375, 0, 276.77853, 0, 446.82352, 222.37746, 0, 0, 1);
    distortionCoeffs = (cv::Mat1d(1,5) << 0.0587196, -0.0542081, -0.000444068, -0.00850087, 0.098648);

    cv::Mat src = cv::imread("../image/aruco_id0.png",cv::IMREAD_COLOR);

    std::vector<int> markerIds;
    std::vector<std::vector<cv::Point2f> > markerCorners, rejectedCandidates;

    cv::Ptr<cv::aruco::DetectorParameters> parameters = cv::aruco::DetectorParameters::create();
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_7X7_100);
    cv::aruco::detectMarkers(src,dictionary,markerCorners,markerIds,parameters,rejectedCandidates);

    cv::Mat outputImage = src.clone();
    cv::aruco::drawDetectedMarkers(outputImage,markerCorners,markerIds);
    
    cv::aruco::estimatePoseSingleMarkers(markerCorners,0.115,camera_matrix,distortionCoeffs,rvec,tvec);

    cv::aruco::drawAxis(src,camera_matrix,distortionCoeffs,rvec,tvec,0.1);
    cv::imshow("output",src);

    std::cout<<tvec<<std::endl;
    cv::waitKey(0);
    
}