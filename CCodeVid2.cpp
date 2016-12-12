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
void getBlur     (Mat frame, int R);
void getThresh	 (Mat frame, Mat Frame2, int R);
void getHist ();
Mat Image;
Mat Temp;
double RedTime = 0;
double EqualTime = 0;
double BlurTime = 0;
double ThreshTime = 0;

//Rates for MedianBlur & Threshold


int main(int argc, char** argv){

int MBlurRate = 31;
int THoldRate = 5;

    clock_t Time;
    Time = clock();

    raspicam::RaspiCam_Cv Camera; //Camera Object
    //Open Camera
    Camera.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    Camera.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
 
    if(!Camera.open()){
	cout<<"Error opening the camera"<<endl;
	return -1;
    }
    int nCount = 100;

	
    //Capturing Frames
    cout<<"Capturing frames"<<endl;
    //namedWindow("DisplayImage", WINDOW_NORMAL);
    //namedWindow("RedImage", WINDOW_NORMAL);
    //namedWindow("EqualizeImage", WINDOW_NORMAL);
    //namedWindow("BlurImage", WINDOW_NORMAL);
    namedWindow("DISPLAY",WINDOW_NORMAL);

    int count = 0;
    int count2 = 0;
    int x;
    int j;
    
    ofstream RawData ("Data/Test_Mon_12Dec_Median"+to_string(MBlurRate)+"_Thresh"+to_string(THoldRate)+"BlackPixels.txt");
    ofstream BlackPixels ("BlackPixels.txt");
	clock_t Time2;

    for(int i = 0; i<=nCount; i++){		  
    Time2 = clock();
	Camera.grab(); 
	Camera.retrieve (Image);
	if(i >= 6){
	    getRedColor(Image);

	    getEqualize(Image);

	    Temp = Image.clone();
	    
	    getBlur(Image, MBlurRate);
	
	    getThresh(Temp,Temp, THoldRate);
	    getThresh(Image,Image, THoldRate);
	  
		imshow("DISPLAY",Image);
	    waitKey(1);
		
	    for (x = 0; x<Temp.cols;x++){
		for(j = 0;j<Temp.rows;j++){
		    int k=Temp.at<uchar>(j,x);
		    if(k==0){ count2++;}      
		}
	    }

	    for (x = 0; x<Image.cols;x++){
		for(j = 0;j<Image.rows;j++){
		    int k=Image.at<uchar>(j,x);
		    if(k==0){ count++;}      
		}
	    } 



	    if (RawData.is_open()){
		RawData<<"Frame "<<i<<endl;
		RawData<<"MedianBlur OFF : NOBP = "<<count2<<endl;
		RawData<<"MedianBlur ON : NOBP = "<<count<<endl;
		RawData<<"Time :"<<(clock()-Time2)<<endl;
		RawData<<'\n';	
	    }
	    
	    if(BlackPixels.is_open()){
			BlackPixels<<i<<" "<<count<<" "<<count2<<endl;
		}
	    
	    	        
		cout<<"IMAGE: "<<count<<" in frame "<<i<<endl;
		cout<<"TEMP: "<<count2<<" in frame "<<i<<'\n';
		cout<<'\n';
	    count = 0;
	    count2 = 0;
	    
	}
    }

    BlackPixels.close();
    RawData.close();
    Camera.release();
    getHist();   

    //cout<<"Red Process Time "<<RedTime<<'\n';
    //cout<<"Equal Process Time "<<EqualTime<<'\n';
    //cout<<"Blur Process Time "<<BlurTime<<'\n';
    //cout<<"Thresh Process Time "<<ThreshTime<<'\n';
    //cout<<"Total "<<(RedTime+EqualTime+BlurTime+ThreshTime)<<'\n';
    //double Subtotal = RedTime+EqualTime+BlurTime+ThreshTime;
    //cout<<"Total Process Time "<<setprecision(3)<<(Subtotal)<<endl;
    //cout<<"Stop Camera..."<<endl;
     
  	
    double Total = (clock() - Time)/(double)CLOCKS_PER_SEC;
    cout<<"Total Process Time "<<setprecision(3)<<(Total)<<endl;
    return 0;
}

void getRedColor(Mat Frame){
    clock_t start;
    start = clock();
    Mat BRG[3];
    split(Frame,BRG);
    Image = BRG[2];
    double s = ((clock()-start)/(double)CLOCKS_PER_SEC);
    RedTime += s;
}

void getEqualize (Mat Frame){
    clock_t start2;
    start2 = clock();
    equalizeHist(Frame,Image);
    double s2 = ((clock()-start2)/(double)CLOCKS_PER_SEC);
    EqualTime += s2;
}

void getBlur (Mat Frame, int rate){
    clock_t start3;
    start3 = clock();
    medianBlur(Frame,Image,rate);
    double s3 = ((clock()-start3)/(double)CLOCKS_PER_SEC);
    BlurTime += s3;
}

void getThresh (Mat Frame, Mat Frame2, int rate ){
    clock_t start4;
    start4 = clock();
    threshold(Frame,Frame2,rate,255, THRESH_BINARY);
    double s4 = ((clock()-start4)/(double)CLOCKS_PER_SEC);
    ThreshTime += s4;
}

void getHist(){	
    FILE *gnuplotPipe = popen ("gnuplot -persistent", "w");
    if(gnuplotPipe){	
	fprintf(gnuplotPipe, "plot 'BlackPixels.txt' using 1:2 with lines, 'BlackPixels.txt' using 1:3 with lines \n");
	//fprintf(gnuplotPipe, "plot 'BlackPixels.txt' using 1:2 with lines \n");
	fflush(gnuplotPipe);
    }
    printf("Displaying graph \n");		
}




