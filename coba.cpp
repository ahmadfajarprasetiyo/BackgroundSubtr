#include <cmath>
#include <iostream>
#include <cv.h>
#include "opencv2/imgproc/imgproc.hpp"
#include <highgui.h>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]){
	VideoCapture cap;
	cap.open(1);
	Mat img;
	bool bSuccess;
	Mat back;
	cap.read(back);
	//cvtColor(back,back,CV_BGR2HSV);
	int temp;
	while(true){
		bSuccess = cap.read(img);
		
		if(!bSuccess){
			break;
		}

		//cvtColor(img,img,CV_BGR2HSV);
		for(int y=0; y<back.rows; y++)
            for(int x=0; x<back.cols; x++){
								temp=0;                
                temp=abs((int)back.at<Vec3b>(y,x)[0]-(int)img.at<Vec3b>(y,x)[0])+temp;
                temp=abs((int)back.at<Vec3b>(y,x)[1]-(int)img.at<Vec3b>(y,x)[1])+temp;
                temp=abs((int)back.at<Vec3b>(y,x)[2]-(int)img.at<Vec3b>(y,x)[2])+temp;
								if(temp<40){
									img.at<Vec3b>(y,x)[0]=0;
									img.at<Vec3b>(y,x)[1]=0;
									img.at<Vec3b>(y,x)[2]=0;
								}
            }

		
		
		imshow("Camera",img);
		waitKey(20);
	}
	
	return 0;
}
