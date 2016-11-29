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


int main(int argc, char** argv){


raspicam::RaspiCam_Cv Camera; //Camera Object
//Open Camera
//Camera.set(CV_CAP_PROP_FORMAT, CV_8UC1);

cout<<"Opening up the camera"<<endl;
if(!Camera.open()){
cout<<"Error opening the camera"<<endl;
return -1;
}

	Mat Image;
	int nCount = 300;
	
//Capturing Frames
cout<<"Capturing frames"<<endl;
namedWindow("Display Window", WINDOW_NORMAL);

for(int i =0; i<=nCount; i++){

	Camera.grab();
	Camera.retrieve (Image);
	imshow("Display Window", Image);
        waitKey(30);	
	if (i%3==0){cout<<"\r Captured "<<i<<" Images \n"<<endl;}
}
//waitKey();	
cout<<"Stop Camera..."<<endl;
Camera.release();        


   
    return 0;
}

