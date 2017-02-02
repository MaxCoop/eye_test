#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <raspicam/raspicam_cv.h>
#include <iomanip>


//Prevents naming collisions
using namespace cv;
using namespace std;

void getRedColor (Mat frame);
void getEqualize (Mat frame);
void getBlur     (Mat frame);
void getThresh	 (Mat frame);
void getHist ();
Mat Image;
Mat Temp;
double RedTime = 0;
double EqualTime = 0;
double BlurTime = 0;
double ThreshTime = 0;

//Rates for MedianBlur & Threshold
int MBlurRate = 5;
int THoldRate = 10;

int main(int argc, char** argv){


    clock_t Time;
    Time = clock();

    raspicam::RaspiCam_Cv Camera; //Camera Object
    //Open Camera
    Camera.set(CV_CAP_PROP_FRAME_WIDTH,640);
    Camera.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    
    //Camera.set(CV_CAP_PROP_FRAME_WIDTH,1280);
    //Camera.set(CV_CAP_PROP_FRAME_HEIGHT, 720);
    
    //Camera.set(CV_CAP_PROP_FRAME_WIDTH,1920);
    //Camera.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
 
    if(!Camera.open()){
	cout<<"Error opening the camera"<<endl;
	return -1;
    }
    
    //elfs edits to default capture values
    //Camera.set(CV_CAP_PROP_GAIN, 50) // values range fropm 0 to 100
    //Camera.set(CV_CAP_PROP_EXPOSURE, 50) //-1 is auto, values range from 0 to 100
    //Camera.set(CV_CAP_PROP_WHITE_BALANCE_RED_V, 50) //values from 1-100 with -1 meaning autobalance
    //not currently implemented yet in library
    
    //back to Kaps' original code
    
    
    int nCount = 300;

	
    //Capturing Frame
    namedWindow("DISPLAY",WINDOW_NORMAL);

    int count = 0;
    int x;
    int j;
    
    ofstream RawData ("Data/Test_Tue_14Dec/Median"+to_string(MBlurRate)+"_Thresh"+to_string(THoldRate)+"BlackPixels.txt");
    ofstream BlackPixels ("BlackPixels.txt");

    for(int i = 0; i<=nCount; i++){		  

	Camera.grab(); 
	Camera.retrieve (Image);
	
	if(i >= 5){
	    getRedColor(Image);

	    getEqualize(Image);
	    
	    getBlur(Image);

	    getThresh(Image);
	  
	    for (x = 0; x<Image.cols;x++){
		for(j = 0;j<Image.rows;j++){
		    int k=Image.at<uchar>(j,x);
		    if(k == 0){ count++ ;}    
      		}
	    } 

        if (RawData.is_open()){
		RawData<<"Frame "<<i<<endl;
		//RawData<<"MedianBlur OFF : NOBP = "<<count2<<endl;
		RawData<<"Black Pixels = "<<count<<endl;
		double ProcessTime= (clock()-Time);
		RawData<<"Time :"<<ProcessTime<<endl;
				   if(BlackPixels.is_open()){
					    	BlackPixels<<ProcessTime<<" "<<count<<endl;
					    	//cout<<"in"<<'\n';
		            }
		RawData<<'\n';	
	    }
	              
		//cout<<"IMAGE: "<<count<<" in frame "<<i<<endl;
		//cout<<'\n';
	    count = 0;
    
	}
	
		imshow("DISPLAY",Image);
	    waitKey(1);
	
    }
    double Total = (clock() - Time)/(double)CLOCKS_PER_SEC;
    cout<<"Total Process Time "<<setprecision(3)<<(Total)<<endl;

    BlackPixels.close();
    RawData.close();
    Camera.release();
  	
  

    //cout<<"Red Process Time "<<RedTime<<'\n';
    //cout<<"Equal Process Time "<<EqualTime<<'\n';
    //cout<<"Blur Process Time "<<BlurTime<<'\n';
    //cout<<"Thresh Process Time "<<ThreshTime<<'\n';
    //cout<<"Total "<<(RedTime+EqualTime+BlurTime+ThreshTime)<<'\n';
    //double Subtotal = RedTime+EqualTime+BlurTime+ThreshTime;
    //cout<<"Total Process Time "<<setprecision(3)<<(Subtotal)<<endl;
    //cout<<"Stop Camera..."<<endl;
    getHist();   
    return 0;
}

void getRedColor(Mat Frame){
    //clock_t start;
    //start = clock();
    Mat BRG[3];
    split(Frame,BRG);
    Image = BRG[2];
    //double s = ((clock()-start)/(double)CLOCKS_PER_SEC);
    //RedTime += s;
}

void getEqualize (Mat Frame){
    //clock_t start2;
    //start2 = clock();
    equalizeHist(Frame,Image);
    //double s2 = ((clock()-start2)/(double)CLOCKS_PER_SEC);
    //EqualTime += s2;
}

void getBlur (Mat Frame){
    //clock_t start3;
    //start3 = clock();
    medianBlur(Frame,Image,MBlurRate);
    //double s3 = ((clock()-start3)/(double)CLOCKS_PER_SEC);
    //BlurTime += s3;
}

void getThresh (Mat Frame){
    //clock_t start4;
    //start4 = clock();
    threshold(Frame,Image,THoldRate,255, THRESH_BINARY);
    //double s4 = ((clock()-start4)/(double)CLOCKS_PER_SEC);
    //ThreshTime += s4;
}

void getHist(){	
    FILE *gnuplotPipe = popen ("gnuplot -persistent", "w");
    if(gnuplotPipe){	
	//fprintf(gnuplotPipe, "plot 'BlackPixels.txt' using 1:2 with lines, 'BlackPixels.txt' using 1:3 with lines \n");
	fprintf(gnuplotPipe, "plot 'BlackPixels.txt' using 1:2 with lines \n");
	fflush(gnuplotPipe);
    }
    printf("Displaying graph \n");		
}




