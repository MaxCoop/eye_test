//compile command
//g++ CCodeVid5.cpp -o CCodeVid5 -lopencv_core -lopencv_highgui -lopencv_imgproc -lraspicam -lraspicam_cv -std=c++11

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
#include <sys/stat.h>
#include <cstdlib>


//Prevents naming collisions
using namespace cv;
using namespace std;

void getRedColor (Mat frame);
void getThresh	 (Mat frame);
void getCenter (Mat frame, int fnum);
string getTime();
Mat Image;
double RedTime = 0;
double ThreshTime = 0;

//TODO - nCount should be replaced by argument value
int nCount =340;

//Frame information
int Fx = -1;
int Fy = -1;
int FLen = -1;
int FWid = -1;
int BPixels = 0;


//Minimum rates for Threshold
int THoldRate = 5;

//Output Files/Directories
//Note this MUST be subdirectory strucutre where executable is run from
//TO DO - restrucutre this so code checks for and creates directories if they dont exist
//and makes new ones based on datetime of recording

const int dir_err = system("mkdir -p Data3/SecondHalf_Tests/Vid/Run");

string name = ("Data3/SecondHalf_Tests/Vid/Run/"+getTime()+to_string(nCount)+"Frames_"+to_string(THoldRate)+"Threshold.txt");

ofstream RawData (name);
ofstream BlackPixels ("Data3/SecondHalf_Tests/Vid/Run/BlackPixels.txt");

std::ofstream RowData ("Data3/SecondHalf_Tests/Vid/Run/RowCount.txt");
std::ofstream ColData ("Data3/SecondHalf_Tests/Vid/Run/ColCount.txt");  
std::ofstream EndsData ("Data3/SecondHalf_Tests/Vid/Run/ColEnds.txt"); 
//Capturing Frame
//TO DO need to update method to take argument for total number of frames
int main(int argc, char** argv){
    RawData<<"Frames,ThresholdValue,BlackPixels,PupilCenterX,PupilCenterY,PupilWid,PupilLen,Time"<<endl;
    clock_t Time;
    Time = clock();
    //cout << Time;
    //waitKey(1);
    //cout << clock();

    //check number of arguments given	
    //cout << argc << "arguments Entered" << "\n";
    //print all arguments	    
    //for (int p=0; p < argc; ++p){
	    //cout << argv[p] << "\n";
//	}
    //./CCodeVid5 350 - use argv[1] for frame input 
    nCount = std::stoi(argv[1]); //converts to integer 	    
	    
    
    //open camera and set resolution
    int w = 640;
    int h =480;
    raspicam::RaspiCam_Cv Camera; //Camera Object
    //Open Camera
    Camera.set(CV_CAP_PROP_FRAME_WIDTH,w);
    Camera.set(CV_CAP_PROP_FRAME_HEIGHT, h);
    //error handling
    if(!Camera.open()){
	cout<<"Error opening the camera"<<endl;
	return -1;
    }	
 
    //iterate through frames
    for(int i = 0; i<=nCount; i++){		  

	Camera.grab(); 
	Camera.retrieve (Image);

	//only take red channel
	getRedColor(Image);    

	//dynamically calculates theshold after first 40 frames to allow camer time to stabilize
	  if (i == 40){    
	  // calculates histogram of pixel intensities at frame 40
		int histSize = 256;    // bin size
		float range[] = { 0, 255 };
		const float *ranges[] = { range };
		MatND hist;
   
		calcHist( &Image, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false );
		
		//double total;
		//total = Image.rows * Image.cols;
		
		float binTotal = 0;
		//counts through all bins in histogram
		for( int h = 0; h < histSize; h++){    
			float binVal = hist.at<float>(h);
			binTotal = binTotal + binVal;
		        //magic number '6000' is we assume the 6000 darkest pixels are part of the pupil and nothing else is
		        //that pixels are used to calculate the threshold value of intensity
			if(binTotal < (6000)){
				THoldRate = h;
				//cout<<h<<" "<<binVal<<"\n";
				}
			//once we have counts the 6000th darkest pixel we set that as threshold
		}
	  }
	
	if(i >= 40){
		//Functions
		//step 1 threshold image based on dynamic calculation
		getThresh(Image);
		//step 2 esimtates centre, heigh and width of pupil an calculates number of black pixels
		getCenter(Image,i);
			
		//TO DO implement 2017 spiral function here
			
		//output calculated variables
		//cout<<BPixels<<endl;

		//writes data analysis to file
		if (RawData.is_open()){
			RawData<<i<<",";
			RawData<<THoldRate<<",";
			RawData<<BPixels<<",";
			RawData<<Fx<<",";
			RawData<<Fy<<",";
			RawData<<FWid<<",";
			RawData<<FLen<<",";
			double ProcessTime= (clock()-Time);
			RawData<<ProcessTime<<endl;
			if(BlackPixels.is_open()){
				BlackPixels<<ProcessTime<<" "<<BPixels;
			}	
		}   
	}
  
    }

    //double Total = (clock() - Time)/(double)CLOCKS_PER_SEC;
    //cout<<"Total Process Time "<<setprecision(3)<<(Total)<<endl;
    BlackPixels.close();
    RawData.close();
    Camera.release();
    std::cout<< name <<endl;
    return 0;
}

string getTime(){
	time_t currentTime;
	struct tm nowLocal;
	currentTime = time(NULL); //gets the time from the os 
	nowLocal=*localtime(&currentTime);
	int datetime = nowLocal.tm_mday+(nowLocal.tm_mon+1)+(nowLocal.tm_year+1900)+nowLocal.tm_hour+nowLocal.tm_min+nowLocal.tm_sec;
	return to_string(datetime);
}


void getRedColor(Mat Frame){
    Mat BRG[3];
    split(Frame,BRG);
    Image = BRG[2];
}

void getThresh (Mat Frame){
    threshold(Frame,Image,THoldRate,255, THRESH_BINARY);
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

    //Variable for counting black pixels
    BPixels = 0;
   // namedWindow("DISPLAY",WINDOW_NORMAL);
    int i;
    int j;
    int n;
    int m;
    int count=0; 

   //TO DO - code below cycles through image twice when it only needs to once
   //we should refactor this to reduce O
	
    for (i = 0; i<Frame.cols;i++){
	for(j = 0;j<Frame.rows;j++){
	    int k= Frame.at<uchar>(j,i);
	    //'count' variable is number of black pixels in column
	    if(k==0){ count++;}      
	}
	//estimates centre of pupil by histogramming    
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
    
    //pupil width
    int FWid = Col2-Col1;
    //pupil x location
    int Fx = Col1 + (FWid/2);
    //std::cout<<"Width "<<FWid<<'\n';
    //std::cout<<"X "<<(Fx)<<'\n';

    //same as above but for heigh of pupil and upil y location
    for (n = 0; n<Frame.rows;n++){
	for(m = 0;m<Frame.cols;m++){
	    int k=Frame.at<uchar>(n,m);
	    //counts number of black pixels that is output	
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
    //outputs to 'EndsData' file - not sure why	
    EndsData<<Col1<<" "<<CEnd1<<endl;
    EndsData<<Col2<<" "<<CEnd2<<endl;
    EndsData<<Row1<<" "<<REnd1<<endl;
    EndsData<<Row2<<" "<<REnd2<<endl;

    //pupil height
    int FLen = Row2-Row1;
    //pupil y position
    int Fy = Row1 + (FLen/2);
    //std::cout<<"Length "<<FLen<<'\n';
    //std::cout<<"Y "<<(Fy)<<'\n';

    waitKey(1);
}
