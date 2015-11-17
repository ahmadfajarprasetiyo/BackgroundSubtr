#include <iostream>
#include <string> 
#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;

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
		Nama = i;
		Nama = Nama + argv[1];
		Nama = Nama + ".jpg";
		imwrite(Nama,frame);
		i++;
		}	
	
	}

	return 0;
}
