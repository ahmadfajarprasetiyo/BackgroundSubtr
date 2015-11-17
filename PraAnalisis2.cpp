#include <iostream>
#include <string> 
#include <cv.h>
#include <highgui.h>
#include <algorithm>

using namespace std;
using namespace cv;
Mat img;
void CallBackFunc(int event, int x,int y, int flags, void* userdata);
int k=4;
int xmin=99999; 
int xmax=0;
int ymin=99999; 
int ymax=0;
int main (int argc, char* argv[]){
	VideoCapture cap;
	cap.open(argv[1]);
	Mat frame;
	string Nama;
	char* temp;
	bool bSuccess;
	int i=65;
	
	while(true){
	bSuccess = cap.read(frame);
	if(!bSuccess){
		cout<<"Habis";
		break;
	}
	
	imshow("Window",frame);
	if(waitKey(33)==' '){
		Nama = Nama + argv[1];
		Nama = Nama + ".jpg";
		imwrite(Nama,frame);
		i++;
		break;
		}	
	
	}
	img = frame.clone();
	imshow("image",img);
	setMouseCallback("image",CallBackFunc,NULL);
	waitKey(0);
	return 0;
}

void CallBackFunc(int event, int x,int y, int flags, void* userdata){
	if(event==EVENT_LBUTTONDOWN){
		xmin = min(xmin,x);
		xmax = max(xmax,x);
		ymin = min(ymin,y);
		ymax = max(ymax,y);
		k--;
		if (k==0){
		rectangle(img,Point(xmin,ymin),Point(xmax,ymax),Scalar(0,255,0),4,8,0);
		cout<<xmin<<" "<<ymin<<endl;
		cout<<xmax<<" "<<ymax<<endl;
		imshow("image",img);
	}
	}
	
}
