#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <raspicam/raspicam_cv.
#include <iomanip>



//Prevents naming collisions
using namespace cv;
using namespace std;

void getRedColor (Mat frame);
void getEqualize (Mat frame);
void getBlur     (Mat frame);
void getThresh	 (Mat frame);
int getBlackPixels(Mat frame);
void getHist ();
Mat Image;
Mat Temp;
Mat canny;
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
    
    
    int nCount = 200;

	
    //Capturing Frame
    namedWindow("DISPLAY",WINDOW_NORMAL);
    namedWindow("DISPLAY2",WINDOW_NORMAL);
    namedWindow("DISPLAY3",WINDOW_NORMAL);

    int x;
    int j;
    
    ofstream RawData ("Data/Test_Fri_16Dec/Median"+to_string(MBlurRate)+"_Thresh"+to_string(THoldRate)+"BlackPixels.txt");
    ofstream BlackPixels ("Data/Test_Fri_16Dec/BlackPixels.txt");

    for(int i = 0; i<=nCount; i++){		  

		Camera.grab(); 
		Camera.retrieve (Image);
	    Temp = Image.clone();
		if(i >= 0){
			getRedColor(Image);

			//getEqualize(Image);
	    
			getBlur(Image);

			getThresh(Image);  
	  
			//imshow("DISPLAY2",Image);
	  
			int BlackPix = getBlackPixels(Image);
			cout<<BlackPix<<endl;
        
			if (RawData.is_open()){
				RawData<<"Frame "<<i<<endl;
				RawData<<"Black Pixels = "<<BlackPix<<endl;
				double ProcessTime= (clock()-Time)/CLOCKS_PER_SEC;
				RawData<<"Time :"<<ProcessTime<<endl;
				   if(BlackPixels.is_open()){
					  BlackPixels<<ProcessTime<<" "<<BlackPix<<endl;
					}
			RawData<<'\n';	
			}  
			
		Canny(Image, canny, 150, 300);	
		imshow("DISPLAY3",canny);
		vector<Vec3f>circles;
		HoughCircles(canny, circles, CV_HOUGH_GRADIENT,1.0, 1000, 100, 10, 15,200);
		
		for (size_t i = 0; i < circles.size(); i++){
			
			Point center(cvRound(circles[i][0]),cvRound(circles[i][1]));
			int radius = cvRound(circles[i][2]);
			circle(Temp,center,3, Scalar(0,255,0), -1, 8,0);	
			circle(Temp,center, radius, Scalar(0,0,225), 3, 8, 0);	
			}	
			
			imwrite("Data/Test_Fri_16Dec/frames/image"+to_string(i)+".png",Temp);
				
		}
	
	imshow("DISPLAY",Temp);
	waitKey(1);
	
    }
    
    double Total = (clock() - Time)/(double)CLOCKS_PER_SEC;
    cout<<"Total Process Time "<<setprecision(3)<<(Total)<<endl;

    BlackPixels.close();
    RawData.close();
    Camera.release();

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
    threshold(Frame,Image,THoldRate,255, THRESH_BINARY_INV);
    //double s4 = ((clock()-start4)/(double)CLOCKS_PER_SEC);
    //ThreshTime += s4;
}

int getBlackPixels (Mat Frame){
	int count = 0;
	  for (int x = 0; x<Frame.cols;x++){
		for(int j = 0;j<Frame.rows;j++){
		    int k=Frame.at<uchar>(j,x);
		    if(k == 0){ count++ ;}    
      		}
	    } 
return count;
	}


void getHist(){	
    FILE *gnuplotPipe = popen ("gnuplot -persistent", "w");
    if(gnuplotPipe){	
	//fprintf(gnuplotPipe, "plot 'BlackPixels.txt' using 1:2 with lines, 'BlackPixels.txt' using 1:3 with lines \n");
	fprintf(gnuplotPipe, "plot 'Data/Test_Fri_16Dec/BlackPixels.txt' using 1:2 with lines \n");
	fflush(gnuplotPipe);
    }
    printf("Displaying graph \n");		
}




