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
int getBlackPixels(Mat frame);
void getCenter (Mat frame, int fnum);
void getHist ();
Mat Image;
Mat Image2;
double RedTime = 0;
double EqualTime = 0;
double BlurTime = 0;
double ThreshTime = 0;
int nCount =340;
int TestNo = 1; 


//Frame information
int Fx = -1;
int Fy = -1;
int FLen = -1;
int FWid = -1;
int BPixels = 0;

//Rates for MedianBlur & Threshold
int MBlurRate = 5;
int THoldRate = 50;

//Folders

ofstream RawData ("Data/SecondHalf_Tests/20_1_2017_Vid4/Run4/"+to_string(nCount)+"Frames_"+to_string(MBlurRate)+"MedianBlur_"+to_string(THoldRate)+"Threshold.txt");
ofstream BlackPixels ("Data/SecondHalf_Tests/20_1_2017_Vid4/Run4/BlackPixels.txt");

std::ofstream RowData ("Data/SecondHalf_Tests/20_1_2017_Vid4/Run4/RowCount.txt");
std::ofstream ColData ("Data/SecondHalf_Tests/20_1_2017_Vid4/Run4/ColCount.txt");  
std::ofstream EndsData ("Data/SecondHalf_Tests/20_1_2017_Vid4/Run4/ColEnds.txt"); 

//Capturing Frame

  

int main(int argc, char** argv){

    clock_t Time;
    Time = clock();

    int w = 640;
    int h =480;
    raspicam::RaspiCam_Cv Camera; //Camera Object
    //Open Camera
    Camera.set(CV_CAP_PROP_FRAME_WIDTH,w);
    Camera.set(CV_CAP_PROP_FRAME_HEIGHT, h);

    if(!Camera.open()){
	cout<<"Error opening the camera"<<endl;
	return -1;
    }	
 
    int x;
    int j;
    for(int i = 0; i<=nCount; i++){		  

	Camera.grab(); 
	Camera.retrieve (Image);
	Image2 = Image.clone();
	getRedColor(Image);    

	  if (i == 40){    
	  // Initialize parameters
		int histSize = 256;    // bin size
		float range[] = { 0, 255 };
		const float *ranges[] = { range };
		MatND hist;
   
		calcHist( &Image, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false );
		
		double total;
		total = Image.rows * Image.cols;
		float binTotal = 0;
		for( int h = 0; h < histSize; h++){    
		float binVal = hist.at<float>(h);
		binTotal = binTotal + binVal;
	  //			cout<<h<<" "<<binVal<<'\n';
		if(binTotal < (6000)){THoldRate = h;}				
		
		}
	  }
	
	if(i >= 40){
	//Functions
	//Mat Temp = Image.clone();
	//getEqualize(Image);
	//getBlur(Image);
	getThresh(Image);
	getCenter(Image,i);
	cout<<BPixels<<endl;
	}    
   
	          
	 if(i >= 40){
		if (RawData.is_open()){
			RawData<<"Frame "<<i<<endl;
			RawData<<"ThresholdValue "<<THoldRate<<endl;
			RawData<<"Black Pixels = "<<BPixels<<endl;
			RawData<<"PupilCenterX = "<<Fx<<endl;
			RawData<<"PupilCenterY = "<<Fy<<endl;
			RawData<<"PupilWid = "<<FWid<<endl;
			RawData<<"PupilLen = "<<FLen<<endl;
			double ProcessTime= (clock()-Time);
			RawData<<"Time :"<<ProcessTime<<endl;
			if(BlackPixels.is_open()){
				BlackPixels<<ProcessTime<<" "<<BPixels<<endl;
			}
			RawData<<'\n';	
		}   
	}
  
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
    Mat BRG[3];
    split(Frame,BRG);
    Image = BRG[2];
}

void getEqualize (Mat Frame){
    equalizeHist(Frame,Image);
}

void getBlur (Mat Frame){
    medianBlur(Frame,Image,MBlurRate);
}

void getThresh (Mat Frame){
    threshold(Frame,Image,THoldRate,255, THRESH_BINARY);
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
    FILE *gnuplotPipf = popen ("gnuplot -persistent", "w");
    if(gnuplotPipe){	
	//fprintf(gnuplotPipe, "plot 'BlackPixels.txt' using 1:2 with lines, 'BlackPixels.txt' using 1:3 with lines \n");
	fprintf(gnuplotPipe, "plot 'Data/SecondHalf_Tests/20_1_2017_Vid4/Run4/ColCount.txt' using 1:2 with lines,'Data/SecondHalf_Tests/20_1_2017_Vid4/Run4/RowCount.txt' using 1:2 with lines,'Data/SecondHalf_Tests/20_1_2017_Vid4/Run4/ColEnds.txt' using 1:2 with points \n");
	fflush(gnuplotPipe);
    }
    
    if(gnuplotPipf){
		fprintf(gnuplotPipf, "plot 'Data/SecondHalf_Tests/20_1_2017_Vid4/Run4/BlackPixels.txt' using 1:2 with lines \n");
		fflush(gnuplotPipf);		
		}
    
    printf("Displaying graphs \n");		
}

void getCenter(Mat Frame,int fnum){
    int CEnd1 = -1;
    int CEnd2 = -1;
    int Col1 = -1;
    int Col2 = -1;
	
    int REnd1 = -1;
    int REnd2 = -1;
    int Row1 = -1;
    int Row2 = -1;

    //Variables for counting black pixels
    BPixels = 0;
   // namedWindow("DISPLAY",WINDOW_NORMAL);
    int i;
    int j;
    int n;
    int m;
    int count=0; 
	
    for (i = 0; i<Frame.cols;i++){
	for(j = 0;j<Frame.rows;j++){
	    int k= Frame.at<uchar>(j,i);
	    if(k==0){ count++;}      
	}
	if (ColData.is_open()){
		ColData<<i<<" "<<count<<endl;
	    int temp = abs(count-30); 
	    if(temp >= 0 && temp <= 20){
			if(Col1 == -1){
		    Col1 = i;
		    CEnd1 = count;
			}else{ Col2 = i; CEnd2 = count;}
	    }
	}
	count=0;
    } 

    int FWid = Col2-Col1;
    int Fx = Col1 + (FWid/2);
    std::cout<<"Width "<<FWid<<'\n';
    std::cout<<"X "<<(Fx)<<'\n';

    for (n = 0; n<Frame.rows;n++){
	for(m = 0;m<Frame.cols;m++){
	    int k=Frame.at<uchar>(n,m);
	    if(k==0){ count++; BPixels++;}      
	}
	if (RowData.is_open()){
		RowData<<n<<" "<<count<<endl;
	    int temp2 = abs(count-30); 
	    if(temp2 >= 0 && temp2 <= 20){
		if(Row1 == -1){
		    Row1 = n;
		    REnd1 = count;
		}else{ Row2 = n; REnd2 = count;}
	    }
	}
			
	count=0;
    } 
		EndsData<<Col1<<" "<<CEnd1<<endl;
		EndsData<<Col2<<" "<<CEnd2<<endl;
		EndsData<<Row1<<" "<<REnd1<<endl;
		EndsData<<Row2<<" "<<REnd2<<endl;
	
    int FLen = Row2-Row1;
    int Fy = Row1 + (FLen/2);
    std::cout<<"Length "<<FLen<<'\n';
    std::cout<<"Y "<<(Fy)<<'\n';

    //circle(Image2,Point(Fx,Fy), 3, Scalar(0,255,0),2,0);
    //circle(Image2,Point(Fx,Fy),(FWid/2), cv::Scalar(0,0,255),2,0);
	//imwrite("Data/SecondHalf_Tests/17_1_2017_Vid4/Run1/CFrames/Image"+to_string(fnum)+".png",Image2);
    //imwrite("Data/SecondHalf_Tests/17_1_2017_Vid4/Run1/NFrames/Image"+to_string(fnum)+".png",Frame);
    //imshow("DISPLAY", Frame);
    waitKey(1);

}
