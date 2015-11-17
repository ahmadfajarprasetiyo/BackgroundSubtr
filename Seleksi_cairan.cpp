#include <cv.h>
#include <highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;
using namespace cv;

typedef pair<int,int> ii;

const int dy[] = {-1,0,1,0};
const int dx[] = {0,1,0,-1};

int H_low,S_low,V_low,H_high,S_high,V_high;

void CallBackFunc(int event, int x,int y, int flags, void* userdata);

Mat img;

int xmin, xmax, ymin, ymax;

int main(int argc, char* argv[]){
	cout<<"Masukkan batas bawah(H S V)"<<endl;
	cin>>H_low>>S_low>>V_low;
	cout<<"Masukkan batas atas(H S V)"<<endl;
	cin>>H_high>>S_high>>V_high;
	img = imread(argv[1],1);
	imshow("image",img);
	setMouseCallback("image",CallBackFunc,NULL);
	waitKey(0);
	return 0;
}

void CallBackFunc(int event, int x,int y, int flags, void* userdata){
	if(event==EVENT_LBUTTONDOWN){
		Mat image = img.clone();
		//cvtColor(image,image,CV_BGR2HSV);
		inRange(image,Scalar(H_low,S_low,V_low),Scalar(H_high,S_high,V_high),image);
			
		bool visit[image.rows+1][image.cols+1];
		memset(visit,false,sizeof(visit));
		
		xmin=image.cols; xmax=0;
		ymin=image.rows; ymax=0;
		
		uchar pl;
		
	
				pl = image.at<uchar>(y,x);
				if((pl>0)&&(!visit[y][x])){
					queue<ii> q;
					q.push(ii(y,x));
					visit[y][x]=true;
					
					xmin=image.cols; xmax=0;
					ymin=image.rows; ymax=0;
					
					while(!q.empty()){
						ii u = q.front(); q.pop();
						xmin = min(xmin,u.second);
						xmax = max(xmax,u.second);
						ymin = min(ymin,u.first);
						ymax = max(ymax,u.first);
						for(int k =0; k<4;++k){
							int ny = u.first+dy[k];
							int nx = u.second+dx[k];
							if((ny>=0) && (ny<=image.rows) && (nx>=0) && (nx<=image.cols) && (!visit[ny][nx])){
								uchar p = image.at<uchar>(ny,nx);								
								if(p > 0){
									
									q.push(ii(ny,nx));
									visit[ny][nx] = true;
								}
							}
							
						}
					
					}
		
				
				}
			
			
		
		if ((xmin < xmax) && (ymin < ymax))
			rectangle(img,Point(xmin,ymin),Point(xmax,ymax),Scalar(0,255,0),4,8,0);
		cout<<xmin<<" "<<ymin<<endl;
		cout<<xmax<<" "<<ymax<<endl;
		imshow("image",img);
		imshow("Hasil",image);     
		
		
		waitKey(0);
	}
}
