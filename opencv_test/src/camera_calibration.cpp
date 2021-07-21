#include <iostream>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc,char** argv)
{

    std::vector<cv::String> fileNames;
    cv::glob("/home/kay/Documents/practice/cpp/opencv_test/image/calib_*.png",fileNames,false);
    cv::Size patternSize;
    patternSize.width = 9;
    patternSize.height = 6;
    //std::vector<std::vector<cv::Point2f> > q;
    std::vector<std::vector<cv::Point2f> > q(fileNames.size());

    //q.clear();

    std::vector<std::vector<cv::Point3f> > Q;

    int chessBoard[2] = {9,6};
    float fieldSize = 0.022;

    std::vector<cv::Point3f> objp;

    for(int i = 0; i < patternSize.height; i++){
        for(int j = 0; j < patternSize.width;j++){
            objp.push_back(cv::Point3f(float(j*fieldSize),
                                        float(i*fieldSize),0));
        }
    }

    std::vector<cv::Point2f> imgPoint;
    
    std::cout<<"The number of filenames:";
    std::cout<<fileNames.size()<<std::endl;
    
    for(int i = 0; i < fileNames.size(); i++)
    {
        std::cout<<std::string(fileNames.at(i))<<std::endl;

        cv::Mat img = cv::imread(fileNames.at(i));
        cv::Mat gray;

        cv::cvtColor(img,gray,cv::COLOR_BGR2GRAY);

        //bool patternFound = cv::findChessboardCorners(gray,patternSize,q[i],cv::CALIB_CB_ADAPTIVE_THRESH+cv::CALIB_CB_NORMALIZE_IMAGE+cv::CALIB_CB_FAST_CHECK);
        bool patternFound = cv::findChessboardCorners(gray,patternSize,q[i]);

        std::vector<cv::Point2f> detected_corners;
        bool found = cv::findChessboardCorners(img,patternSize,detected_corners);

        //std::cout<<q[i]<<std::endl;
        //std::cout<<detected_corners<<std::endl;
        if(patternFound){
            cv::cornerSubPix(gray,q[i],cv::Size(5,5),cv::Size(-1,-1),cv::TermCriteria(cv::TermCriteria::EPS|cv::TermCriteria::MAX_ITER,30,0.1));
            Q.push_back(objp);
        }

    cv::drawChessboardCorners(img,patternSize,q[i],patternFound);
    cv::imshow(fileNames.at(i),img);

    cv::waitKey(0);

    }
    
    cv::Matx33f K(cv::Matx33f::eye());
    cv::Vec<float, 5> k(0, 0, 0, 0, 0);

    std::vector<cv::Mat> rvecs, tvecs;
    std::vector<float> stdIntrinsics, stdExtrinsics, preViewErrors;

    //int flags = cv::CALIB_FIX_ASPECT_RATIO + cv::CALIB_FIX_K3
    //            + cv::CALIB_ZERO_TANGENT_DIST + cv::CALIB_FIX_PRINCIPAL_POINT;
    
    int flags = 0;
    flags |= cv::CALIB_FIX_K4;
    flags |= cv::CALIB_FIX_K5;

    cv::Size frameSize(640,480);

    std::cout<<"Calibrating..."<<std::endl;

    float error = cv::calibrateCamera(Q,q,frameSize,K,k,rvecs,tvecs,flags);

    std::cout<<"Reprojection error = " <<error<<std::endl;
    std::cout<<K<<std::endl;
    std::cout<<k<<std::endl;
}
