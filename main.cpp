#include <cmath>
#include <iostream>
#include <cv.h>
#include "imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <stdio.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    VideoCapture cap(1);
    Mat img,th;
    bool bSuccess;
    Mat back;
    cap >> back;
    cvtColor(back,back,CV_BGR2HSV);
    int temp;
    while(1) {
        cap >> img;
	cvtColor(img,img,CV_BGR2HSV);
	inRange(img,Scalar(9,110,150),Scalar(25,210,250),th);
	GaussianBlur( th, th, Size(9, 9), 2, 2 );
	vector<Vec3f> circles;
        HoughCircles(th, circles, CV_HOUGH_GRADIENT,1, th.rows/4, 100, 50,10,400);
        for( size_t i = 0; i < circles.size(); i++ ) {
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            //draw the circle center
            circle( img, center, 3, Scalar(0,255,0), -1, 8, 0 );
            //draw the circle outline
            circle( img, center, radius, Scalar(0,0,255), 3, 8, 0 );
        }
	imshow( "circles1", th );
        imshow( "circles", img );
	waitKey(20);
    }
}
