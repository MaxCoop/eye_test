#include <string>
#include <iostream>
#include <vector>

#include <ctime>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <raspicam/raspicam_cv.h>

//Prevents naming collisions
using namespace cv;
using namespace std;

void getRedColor(Mat Frame);
void getBlur (Mat Frame);


Mat Image;
double BlurTime;

int main(int argc, char** argv){


raspicam::RaspiCam_Cv Camera; //Camera Object
//Open Camera
//Camera.set(CV_CAP_PROP_FORMAT, CV_8UC1);

cout<<"Opening up the camera"<<endl;
if(!Camera.open()){
cout<<"Error opening the camera"<<endl;
return -1;
}
	int nCount = 51;
	
//Capturing Frames
cout<<"Capturing frames"<<endl;

namedWindow("BlurImage", WINDOW_NORMAL);

for (int u = 3; u <= 15; u += 2){ 
for(int i =0; i<=nCount; i++){

	Camera.grab();
	Camera.retrieve (Image);

	getRedColor(Image);
	
	getBlur(Image);
	imshow("BlurImage",Image);
	waitKey(10);

	//if (i%3==0){cout<<"\r Captured "<<i<<" Images \n"<<endl;}
 cout<<i<<endl;
}

cout<<"Blur Process Time for "<<u<<": "<<BlurTime<<'\n';
BlurTime = 0;
}
cout<<"Stop Camera..."<<endl;
Camera.release(); 
    return 0;
}


void getRedColor(Mat Frame){
clock_t start;
start = clock();
Mat BRG[3];
split(Frame,BRG);
Image = BRG[2];
//cout<<"GET RED PROCESS "<<((clock()-start)/(double)CLOCKS_PER_SEC)<<'\n';
//RedTime = RedTime + ((clock() - start)/(double)CLOCKS_PER_SEC);

}

void getBlur (Mat Frame){
clock_t start3;
start3 = clock();
medianBlur(Frame,Image,13);
BlurTime = BlurTime + ((clock() - start3)/(double)CLOCKS_PER_SEC);

}
