/*
** argv[1] background
** argv[2] video
*/

#include <cmath>
#include <iostream>
#include <cv.h>
#include "opencv2/imgproc/imgproc.hpp"
#include <highgui.h>

using namespace cv;
using namespace std;

float jarak;
int GoalX,GoalY;
bool mulai = false;
int Pos_frame = 0;
long long int msec=0;
int total_frame, mm, ss, ms;
int xmin,ymin,xmax,ymax;
void CallBackFunc(int event, int x, int y, int flags, void* userdata);
void carims();

int main(int argc, char* argv[]){
	VideoCapture cap;
	cap.open(argv[2]);
	Mat back = imread(argv[1],1);
	Mat HSVgerak;
	Mat HSVdeteksi;
	

	int H_low,S_low,V_low;
	float jeda;
	
	cin>>xmin>>ymin;
	cin>>xmax>>ymax;
	cin>>mm>>ss>>ms;
	cin>>total_frame;
	total_frame--;
	carims();
	
	jeda = ((float)msec/(float)total_frame);
	
	
	int iLastX=-1;
	int iLastY=-1;
	
	Mat imgLines = Mat::zeros(back.size(),CV_8UC3);
	
	Mat imgOriginal,imgHSV,imgThreshold;
	bool bSuccess;
	
	
	cvtColor(back,back,CV_BGR2HSV);
	
	while(true){
	
		bSuccess = cap.read(imgOriginal);
		
		if(!bSuccess){
			break;
		}
		
		cvtColor(imgOriginal,imgHSV,CV_BGR2HSV);
        cvtColor(imgOriginal,HSVgerak,CV_BGR2HSV);


        for(int y=0; y<HSVgerak.rows; y++)
            for(int x=0; x<HSVgerak.cols; x++){
                if((x>=xmin)&&(x<=xmax)&&(y>=ymin)&&(y<=ymax)){
                HSVgerak.at<Vec3b>(y,x)[0]=abs((int)back.at<Vec3b>(y,x)[0]-(int)HSVgerak.at<Vec3b>(y,x)[0]);
                HSVgerak.at<Vec3b>(y,x)[1]=abs((int)back.at<Vec3b>(y,x)[1]-(int)HSVgerak.at<Vec3b>(y,x)[1]);
                HSVgerak.at<Vec3b>(y,x)[2]=abs((int)back.at<Vec3b>(y,x)[2]-(int)HSVgerak.at<Vec3b>(y,x)[2]);} else{
                    HSVgerak.at<Vec3b>(y,x)[0]=0;
                    HSVgerak.at<Vec3b>(y,x)[1]=0;
                    HSVgerak.at<Vec3b>(y,x)[2]=0;
                }

            }
        inRange(HSVgerak,Scalar(5,5,20),Scalar(255,255,255),HSVgerak);


        erode(HSVgerak,HSVgerak,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));
        dilate(HSVgerak,HSVgerak,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));

        dilate(HSVgerak,HSVgerak,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));
        erode(HSVgerak,HSVgerak,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));

        imshow("HSVgerak",HSVgerak);
		for(int y=0; y<imgHSV.rows; y++)
			for(int x=0; x<imgHSV.cols; x++){
				if((x>=xmin)&&(x<=xmax)&&(y>=ymin)&&(y<=ymax)){
				imgHSV.at<Vec3b>(y,x)[0]=abs((int)back.at<Vec3b>(y,x)[0]-(int)imgHSV.at<Vec3b>(y,x)[0]);
				imgHSV.at<Vec3b>(y,x)[1]=abs((int)back.at<Vec3b>(y,x)[1]-(int)imgHSV.at<Vec3b>(y,x)[1]);
				imgHSV.at<Vec3b>(y,x)[2]=abs((int)back.at<Vec3b>(y,x)[2]-(int)imgHSV.at<Vec3b>(y,x)[2]);} else{
					imgHSV.at<Vec3b>(y,x)[0]=0;
					imgHSV.at<Vec3b>(y,x)[1]=0;
					imgHSV.at<Vec3b>(y,x)[2]=0;
				}
			}
        imshow("Threshold",imgHSV);

		//erode(imgHSV,imgHSV,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));
		//dilate(imgHSV,imgHSV,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));	

		//dilate(imgHSV,imgHSV,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));
		//erode(imgHSV,imgHSV,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));
		
        if(mulai==true){
        Moments oMoments = moments(HSVgerak);

		double dM01=oMoments.m01;
		double dM10=oMoments.m10;
		double dArea=oMoments.m00;

		if(dArea > 10000){
			int posX = dM10/dArea;
			int posY = dM01/dArea;
			if(iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
				line(imgLines,Point(posX,posY),Point(iLastX,iLastY),Scalar(0,0,255),2);	

			iLastX = posX;
			iLastY = posY;
			rectangle(imgOriginal,Point(posX-5,posY-5),Point(posX+5,posY+5),Scalar(0,255,0),4,8,0);
			cout<<posX<<" "<<posY<<" "<<(float)Pos_frame*jeda<<endl;
		}
		
		
        }
		
    imgOriginal = imgOriginal+imgLines;
		imshow("Original",imgOriginal);
		imshow("BackHSV",back);

		
		setMouseCallback("Original",CallBackFunc,NULL);
		
		jarak=sqrt(((GoalX-iLastX)*(GoalX-iLastX))+((GoalY-iLastY)*(GoalY-iLastY)));
		if((jarak<15)&&(mulai))
			break;		

		Pos_frame++;
		waitKey(20);
	}

	return 0;
}

void CallBackFunc(int event, int x, int y, int flags, void* userdata){
	if((event==EVENT_LBUTTONDOWN)&&(mulai==false)){
		mulai = true;
		Pos_frame=0;
		GoalX=x;
		GoalY=y;
		cout<<GoalX<<" "<<GoalY<<endl;
		cout<<xmin<<" "<<ymin<<endl;
		cout<<xmax<<" "<<ymax<<endl;
	}
}

void carims(){
	msec = ms;
	msec = msec + (100*ss);
	msec = msec + (60*100*mm);

}
