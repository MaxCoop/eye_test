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
void getThresh	 (Mat frame, Mat Frame2);
void getHist ();
Mat Image;
Mat Temp;
double RedTime = 0;
double EqualTime = 0;
double BlurTime = 0;
double ThreshTime = 0;

int main(int argc, char** argv){

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
    int nCount = 50;

	
    //Capturing Frames
    cout<<"Capturing frames"<<endl;
    //namedWindow("DisplayImage", WINDOW_NORMAL);
    //namedWindow("RedImage", WINDOW_NORMAL);
    //namedWindow("EqualizeImage", WINDOW_NORMAL);
    //namedWindow("BlurImage", WINDOW_NORMAL);
    namedWindow("ThreshImage",WINDOW_NORMAL);

    int count = 0;
    //int count2 = 0;
    int x;
    int j;
    int count2 =0;


    ofstream myfile ("BlackPixels.txt");

    for(int i = 0; i<=nCount; i++){
	Camera.grab(); 
	Camera.retrieve (Image);
	if(i >= 6){
	    getRedColor(Image);

	    getEqualize(Image);

	    Temp = Image.clone();
	    
	    getBlur(Image);
	
	    getThresh(Temp,Temp);
	    getThresh(Image,Image);
	  
	    	    
	    if(i == 10){
			imwrite("WithoutMedian.png", Temp);
			imwrite("WithMedian.png", Image);
			}
	
	    //for (x = 0; x<Temp.cols;x++){
		//for(j = 0;j<Temp.rows;j++){
		    //int k=Temp.at<uchar>(j,x);
		    //if(k==0){ count2++;}      
		//}
	    //}
	    cout << count2 <<'\n';

	    imshow("ThreshImage",Image);
	    waitKey(1);

	    cout<<"frame "<<i<<endl;
	    for (x = 0; x<Image.cols;x++){
		for(j = 0;j<Image.rows;j++){
		    int k=Image.at<uchar>(j,x);
		    if(k==0){ count++;}      
		}
	    } 
	    if (myfile.is_open()){
		//myfile<<i<<" "<<count<<" "<<count2<<'\n';		 
		myfile<<i<<" "<<count<<'\n';	
	    }
	    cout<<"Black Pixels : "<<count<<" in frame "<<i<<endl;
	    count = 0;
	    count2 = 0;
	    
	}
    }

    myfile.close();

    //cout<<"Red Process Time "<<RedTime<<'\n';
    //cout<<"Equal Process Time "<<EqualTime<<'\n';
    //cout<<"Blur Process Time "<<BlurTime<<'\n';
    //cout<<"Thresh Process Time "<<ThreshTime<<'\n';
    //cout<<"Total "<<(RedTime+EqualTime+BlurTime+ThreshTime)<<'\n';
    //double Subtotal = RedTime+EqualTime+BlurTime+ThreshTime;
    //cout<<"Total Process Time "<<setprecision(3)<<(Subtotal)<<endl;
    //cout<<"Stop Camera..."<<endl;
    Camera.release();
    getHist();        
  	
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

void getBlur (Mat Frame){
    clock_t start3;
    start3 = clock();
    medianBlur(Frame,Image,13);
    double s3 = ((clock()-start3)/(double)CLOCKS_PER_SEC);
    BlurTime += s3;
}

void getThresh (Mat Frame, Mat Frame2 ){
    clock_t start4;
    start4 = clock();
    threshold(Frame,Frame2,15,255, THRESH_BINARY);
    double s4 = ((clock()-start4)/(double)CLOCKS_PER_SEC);
    ThreshTime += s4;
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






