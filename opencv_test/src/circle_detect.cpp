#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using std::vector;
int main(int argc, char** argv)
{
    Mat src = imread("../image_raw_screenshot3_14_07_2021.png",IMREAD_COLOR);
    //imshow("image",src);

    Mat gray;
    cvtColor(src,gray,COLOR_BGR2GRAY);
    imshow("circle",gray);

    medianBlur(gray, gray, 5);
    vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                 gray.rows/16,  // change this value to detect circles with different distances to each other
                 100, 30, 50, 200 // change the last two parameters
            // (min_radius & max_radius) to detect larger circles
    );

    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        // circle center
        circle( src, center, 1, Scalar(0,100,100), 3, LINE_AA);
        // circle outline
        int radius = c[2];
        circle( src, center, radius, Scalar(255,0,255), 3, LINE_AA);

        printf("x : %d y : %d r : %d\n",c[0],c[1],c[2]);
    }

    imshow("detected_circles",src);



    waitKey(0);
}